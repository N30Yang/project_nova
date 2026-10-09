#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP32Servo.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Servo myServo;
const int SERVO_PIN = 18;   
const unsigned char worldMap[] PROGMEM = {
};
const char* names[] = {"EARTH", "MARS", "MOON", "SATURN", "JUPITER"};
const int NUM = 5;
int planet = 0;
unsigned long lastSwitch = 0;
float rot = 0;
struct Rock { float x, y, vx, vy; int s; };
Rock rocks[4];
void respawn(Rock &r) {
  r.x = 130 + random(0, 80);
  r.y = random(4, 60);
  r.vx = -random(20, 50) / 10.0;
  r.vy = random(-10, 11) / 10.0;
  r.s = random(1, 4);
}
void drawRock(int cx, int cy, int s) {
  for (int dy = -s; dy <= s; dy++) {
    for (int dx = -s; dx <= s; dx++) {
      float d2 = dx * dx + dy * dy;
      if (d2 > (s + 0.5) * (s + 0.5)) continue;
      int x = cx + dx, y = cy + dy;
      if (x < 0 || x > 127 || y < 0 || y > 63) continue;
      u8g2.setDrawColor(d2 >= (s - 0.5) * (s - 0.5) ? 1 : 0);  
      u8g2.drawPixel(x, y);
    }
  }
  u8g2.setDrawColor(1);
}
void px(int x, int y) {
  if (x >= 0 && x < 128 && y >= 0 && y < 64) u8g2.drawPixel(x, y);
}
const float craters[8][3] = {
  {0.0, 0.3, 0.35}, {1.5, -0.4, 0.30}, {-1.2, 0.5, 0.25}, {2.6, 0.1, 0.40},
  {-2.4, -0.3, 0.30}, {0.8, 0.9, 0.20}, {-0.5, -0.7, 0.28}, {3.0, -0.8, 0.22}
};
float wrapPi(float a) {
  while (a > PI) a -= 2 * PI;
  while (a < -PI) a += 2 * PI;
  return a;
}
bool texel(int type, int sx, int sy, float lat, float lon) {
  bool checker = ((sx + sy) & 1) == 0;
  if (type == 0) {                       
    int col = (int)((lon / (2 * PI) + 0.5) * 128);
    col = ((col % 128) + 128) % 128;
    int row = (int)((0.5 - lat / PI) * 64);
    if (row < 0) row = 0;
    if (row > 63) row = 63;
    uint8_t b = pgm_read_byte(&worldMap[row * 16 + col / 8]);
    return b & (0x80 >> (col % 8));
  }
  if (type == 1) {                       
    if (fabs(lat) > 1.25) return true;   
    float t = sin(lon * 2.0 + 1.0) * cos(lat * 3.0) + 0.4 * sin(lon * 5.0 + lat * 4.0);
    if (t > 0.35) return false;          
    if (t < -0.3) return true;
    return checker;
  }
  if (type == 2) {                       
    float cl = cos(lat);
    for (int i = 0; i < 8; i++) {
      float dl = wrapPi(lon - craters[i][0]) * cl;
      float dt = lat - craters[i][1];
      float d = sqrt(dl * dl + dt * dt);
      if (fabs(d - craters[i][2]) < 0.035) return true;   
    }
    float t = sin(lon * 3.0) * sin(lat * 4.0 + 1.0);
    if (t > 0.5) return checker;         
    return false;
  }
  if (type == 4) {                       
    float dl = wrapPi(lon - 1.0);
    float dt = lat + 0.35;
    float e = (dl * dl) / 0.2 + (dt * dt) / 0.05;
    if (e < 1.0) return e > 0.45;
  }
  float v = sin(lat * (type == 4 ? 9.0 : 7.0) + 0.5 * sin(lon * 3.0));
  if (v > 0.5) return true;
  if (v > -0.2) return checker;
  return false;
}
void drawSphere(int cx, int cy, int r, int type, float spin) {
  u8g2.drawCircle(cx, cy, r + 1);
  for (int py = -r; py <= r; py++) {
    for (int pxl = -r; pxl <= r; pxl++) {
      float x = pxl / (float)r;
      float y = py / (float)r;
      float d2 = x * x + y * y;
      if (d2 > 1.0) continue;
      float z = sqrt(1.0 - d2);
      float lat = asin(-y);
      float lon = atan2(x, z) - spin;
      if (texel(type, cx + pxl, cy + py, lat, lon)) u8g2.drawPixel(cx + pxl, cy + py);
    }
  }
}
void drawRing(int cx, int cy, int rx, int ry, int planetR, bool front) {
  const float tilt = -0.35;
  float ct = cos(tilt), st = sin(tilt);
  for (float a = 0; a < 2 * PI; a += 0.02) {
    bool isFront = sin(a) > 0;
    if (isFront != front) continue;
    float ex = rx * cos(a), ey = ry * sin(a);
    int x = cx + ex * ct - ey * st;
    int y = cy + ex * st + ey * ct;
    if (!front) {
      int dx = x - cx, dy = y - cy;
      if (dx * dx + dy * dy < planetR * planetR) continue;
    }
    px(x, y);
  }
}
void setup() {
  u8g2.begin();
  myServo.setPeriodHertz(50);              
  myServo.attach(SERVO_PIN, 500, 2400);    
  for (int i = 0; i < 4; i++) respawn(rocks[i]);
}
void loop() {
  if (millis() - lastSwitch > 6000) {
    planet = (planet + 1) % NUM;
    lastSwitch = millis();
    myServo.write(planet * 45);            
  }
  u8g2.clearBuffer();
  if (planet == 3) {                       
    drawSphere(64, 32, 17, 3, rot);
    drawRing(64, 32, 30, 8, 17, false);
    drawRing(64, 32, 30, 8, 17, true);
    drawRing(64, 32, 25, 6, 17, false);
    drawRing(64, 32, 25, 6, 17, true);
  } else {
    drawSphere(64, 32, 30, planet, rot);
  }
  for (int i = 0; i < 4; i++) {
    Rock &r = rocks[i];
    r.x += r.vx;
    r.y += r.vy;
    if (r.x < -10 || r.y < -10 || r.y > 74) respawn(r);
    int ix = (int)r.x, iy = (int)r.y;
    for (int k = 2; k <= 8; k += 2) px(ix - r.vx * k, iy - r.vy * k);   
    drawRock(ix, iy, r.s);
  }
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawStr(0, 7, names[planet]);
  u8g2.sendBuffer();
  rot += 0.08;
  if (rot > 2 * PI) rot -= 2 * PI;
}