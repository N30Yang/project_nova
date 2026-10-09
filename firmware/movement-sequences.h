#pragma once
#include <Arduino.h>
enum ServoName : uint8_t {
  R1 = 0,
  R2 = 1,
  L1 = 2,
  L2 = 3,
  R4 = 4,
  R3 = 5,
  L3 = 6,
  L4 = 7
};
const String ServoNames[]={"R1","R2","L1","L2","R4","R3","L3","L4"};
inline int servoNameToIndex(const String& servo) {
  if (servo == "L1") return L1;
  if (servo == "L2") return L2;
  if (servo == "L3") return L3;
  if (servo == "L4") return L4;
  if (servo == "R1") return R1;
  if (servo == "R2") return R2;
  if (servo == "R3") return R3;
  if (servo == "R4") return R4;
  return -1;
}
enum FaceAnimMode : uint8_t {
  FACE_ANIM_LOOP = 0,
  FACE_ANIM_ONCE = 1,
  FACE_ANIM_BOOMERANG = 2
};
extern int frameDelay;
extern int walkCycles;
extern String currentCommand;
extern int motorCurrentDelay;
extern void setServoAngle(uint8_t channel, int angle);
extern void setFace(const String& faceName);
extern void setFaceMode(FaceAnimMode mode);
extern void setFaceWithMode(const String& faceName, FaceAnimMode mode);
extern void delayWithFace(unsigned long ms);
extern void enterIdle();
extern bool planetDisplayStart(const char* name);
extern void planetDisplayStop();
extern bool pressingCheck(String cmd, int ms);
void runRestPose();
void runStandPose(int face = 1);
void runWavePose();
void runDancePose();
void runSwimPose();
void runPointPose();
void runPushupPose();
void runBowPose();
void runCutePose();
void runFreakyPose();
void runWormPose();
void runShakePose();
void runShrugPose();
void runDeadPose();
void runCrabPose();
void runWalkPose();
void runWalkBackward();
void runTurnLeft();
void runTurnRight();
void runMoonPose();
void runMarsPose();
void runEarthPose();
void runJupiterPose();
inline void runRestPose() {
  Serial.println(F("REST"));
  setFaceWithMode("rest", FACE_ANIM_BOOMERANG);
  for (int i = 0; i < 8; i++) setServoAngle(i, 90);
}
inline void runStandPose(int face) {
  Serial.println(F("STAND"));
  if (face == 1) setFaceWithMode("stand", FACE_ANIM_ONCE);
  setServoAngle(R1, 135);
  setServoAngle(R2, 45);
  setServoAngle(L1, 45);
  setServoAngle(L2, 135);
  setServoAngle(R4, 0);
  setServoAngle(R3, 180);
  setServoAngle(L3, 0);
  setServoAngle(L4, 180);
  if (face == 1) enterIdle();
}
inline void runWavePose() {
  Serial.println(F("WAVE"));
  setFaceWithMode("wave", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R4, 80); setServoAngle(L3, 180);
  setServoAngle(L2, 90); setServoAngle(R1, 100);
  delayWithFace(200);
  setServoAngle(L3, 180);
  delayWithFace(300);
  for (int i = 0; i < 4; i++) {
    setServoAngle(L3, 180); delayWithFace(300);
    setServoAngle(L3, 100); delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "wave") currentCommand = "";
}
inline void runDancePose() {
  Serial.println(F("DANCE"));
  setFaceWithMode("dance", FACE_ANIM_LOOP);
  setServoAngle(R1, 90); setServoAngle(R2, 90);
  setServoAngle(L1, 90); setServoAngle(L2, 90);
  setServoAngle(R4, 160); setServoAngle(R3, 160);
  setServoAngle(L3, 10); setServoAngle(L4, 10);
  delayWithFace(300);
  for (int i = 0; i < 5; i++) {
    setServoAngle(R4, 115); setServoAngle(R3, 115);
    setServoAngle(L3, 10); setServoAngle(L4, 10);
    delayWithFace(300);
    setServoAngle(R4, 160); setServoAngle(R3, 160);
    setServoAngle(L3, 65); setServoAngle(L4, 65);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "dance") currentCommand = "";
}
inline void runSwimPose() {
  Serial.println(F("SWIM"));
  setFaceWithMode("swim", FACE_ANIM_ONCE);
  for (int i = 0; i < 8; i++) setServoAngle(i, 90);
  for (int i = 0; i < 4; i++) {
    setServoAngle(R1, 135); setServoAngle(R2, 45);
    setServoAngle(L1, 45); setServoAngle(L2, 135);
    delayWithFace(400);
    setServoAngle(R1, 90); setServoAngle(R2, 90);
    setServoAngle(L1, 90); setServoAngle(L2, 90);
    delayWithFace(400);
  }
  runStandPose(1);
  if (currentCommand == "swim") currentCommand = "";
}
inline void runPointPose() {
  Serial.println(F("POINT"));
  setFaceWithMode("point", FACE_ANIM_BOOMERANG);
  setServoAngle(L2, 90); setServoAngle(R1, 135);
  setServoAngle(R2, 100); setServoAngle(L4, 180);
  setServoAngle(L1, 25); setServoAngle(L3, 145);
  setServoAngle(R4, 80); setServoAngle(R3, 170);
  delayWithFace(2000);
  runStandPose(1);
  if (currentCommand == "point") currentCommand = "";
}
inline void runPushupPose() {
  Serial.println(F("PUSHUP"));
  setFaceWithMode("pushup", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delayWithFace(500);
  for (int i = 0; i < 4; i++) {
    setServoAngle(L3, 0);
    setServoAngle(R3, 180);
    delayWithFace(600);
    setServoAngle(L3, 90);
    setServoAngle(R3, 90);
    delayWithFace(500);
  }
  runStandPose(1);
  if (currentCommand == "pushup") currentCommand = "";
}
inline void runBowPose() {
  Serial.println(F("BOW"));
  setFaceWithMode("bow", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 0);
  setServoAngle(R3, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 0);
  setServoAngle(L4, 180);
  delayWithFace(600);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delayWithFace(3000);
  runStandPose(1);
  if (currentCommand == "bow") currentCommand = "";
}
inline void runCutePose() {
  Serial.println(F("CUTE"));
  setFaceWithMode("cute", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(L2, 160);
  setServoAngle(R2, 20);
  setServoAngle(R4, 180);
  setServoAngle(L4, 0);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 180);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 5; i++) {
    setServoAngle(R4, 180);
    setServoAngle(L4, 45);
    delayWithFace(300);
    setServoAngle(R4, 135);
    setServoAngle(L4, 0);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "cute") currentCommand = "";
}
inline void runFreakyPose() {
  Serial.println(F("FREAKY"));
  setFaceWithMode("freaky", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 90);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 3; i++) {
    setServoAngle(R3, 25);
    delayWithFace(400);
    setServoAngle(R3, 0);
    delayWithFace(400);
  }
  runStandPose(1);
  if (currentCommand == "freaky") currentCommand = "";
}
inline void runWormPose() {
  Serial.println(F("WORM"));
  setFaceWithMode("worm", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 180); setServoAngle(R2, 0); setServoAngle(L1, 0); setServoAngle(L2, 180);
  setServoAngle(R4, 90); setServoAngle(R3, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delayWithFace(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R3, 45); setServoAngle(L3, 135); setServoAngle(R4, 45); setServoAngle(L4, 135);
    delayWithFace(300);
    setServoAngle(R3, 135); setServoAngle(L3, 45); setServoAngle(R4, 135); setServoAngle(L4, 45);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "worm") currentCommand = "";
}
inline void runShakePose() {
  Serial.println(F("SHAKE"));
  setFaceWithMode("shake", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 135); setServoAngle(L1, 45); setServoAngle(L3, 90); setServoAngle(R3, 90);
  setServoAngle(L2, 90); setServoAngle(R2, 90);
  delayWithFace(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(L4, 135);
    delayWithFace(300);
    setServoAngle(R4, 0); setServoAngle(L4, 180);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "shake") currentCommand = "";
}
inline void runShrugPose() {
  Serial.println(F("SHRUG"));
  runStandPose(0);
  setFaceWithMode("dead", FACE_ANIM_ONCE);
  delayWithFace(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delayWithFace(1000);
  setFaceWithMode("shrug", FACE_ANIM_ONCE);
  setServoAngle(R3, 0); setServoAngle(R4, 180); setServoAngle(L3, 180); setServoAngle(L4, 0);
  delayWithFace(1500);
  runStandPose(1);
  if (currentCommand == "shrug") currentCommand = "";
}
inline void runDeadPose() {
  Serial.println(F("DEAD"));
  runStandPose(0);
  setFaceWithMode("dead", FACE_ANIM_BOOMERANG);
  delayWithFace(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  if (currentCommand == "dead") currentCommand = "";
}
inline void runCrabPose() {
  Serial.println(F("CRAB"));
  setFaceWithMode("crab", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 90); setServoAngle(R2, 90); setServoAngle(L1, 90); setServoAngle(L2, 90);
  setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(R3, 135); setServoAngle(L3, 0); setServoAngle(L4, 180);
    delayWithFace(300);
    setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "crab") currentCommand = "";
}
inline void runWalkPose() {
  Serial.println(F("WALK FWD"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  setServoAngle(R3, 135); setServoAngle(L3, 45);
  setServoAngle(R2, 100); setServoAngle(L1, 25);
  if (!pressingCheck("forward", frameDelay)) return;
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(L4, 135); setServoAngle(L2, 90);
    setServoAngle(R4, 0); setServoAngle(R1, 180);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(L2, 135); setServoAngle(R1, 90);
    if (!pressingCheck("forward", frameDelay)) return;
  }
  runStandPose(1);
}
inline void runWalkBackward() {
  Serial.println(F("WALK BACK"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  if (!pressingCheck("backward", frameDelay)) return;
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(L4, 135); setServoAngle(L2, 135);
    setServoAngle(R4, 0); setServoAngle(R1, 90);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(L2, 90); setServoAngle(R1, 180);
    if (!pressingCheck("backward", frameDelay)) return;
  }
  runStandPose(1);
}
inline void runTurnLeft() {
  Serial.println(F("TURN LEFT"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L4, 135);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R1, 180); setServoAngle(L2, 180);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L4, 180);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L3, 45);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R2, 90); setServoAngle(L1, 90);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R4, 0); setServoAngle(L3, 0);
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    if (!pressingCheck("left", frameDelay)) return;
  }
  runStandPose(1);
}
inline void runTurnRight() {
  Serial.println(F("TURN RIGHT"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R4, 45); setServoAngle(L3, 45);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R2, 0); setServoAngle(L1, 0);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R4, 0); setServoAngle(L3, 0);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R3, 135); setServoAngle(L4, 135);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R1, 90); setServoAngle(L2, 90);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L4, 180);
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    if (!pressingCheck("right", frameDelay)) return;
  }
  runStandPose(1);
}
const float   PLANET_INTENSITY       = 0.5f;
const float   PLANET_MAX_DEPTH       = 0.35f;
const int     PLANET_BASE_FRAME_MS   = 100;
const int     PLANET_MIN_FRAME_MS    = 50;
const int     PLANET_SETTLE_MS       = 200;
const int     PLANET_BOUNCE_MS       = 250;
const int     PLANET_STRAIN_HOLD_MS  = 250;
const int     PLANET_STRAIN_PAUSE_MS = 150;
const int     PLANET_SHIVER_MS       = 60;
const float   PLANET_SHIVER_DEPTH    = 0.09f;
const float   PLANET_SWAY_DEPTH      = 0.10f;
const int     PLANET_WAVE_MS         = 300;
const uint8_t PLANET_EASE_STEPS      = 3;
const bool    PLANET_CROUCH_WALK     = false;
const bool    PLANET_STORM_SWAY      = false;
enum PlanetExtra : uint8_t { PLANET_EXTRA_NONE, PLANET_EXTRA_SHIVER, PLANET_EXTRA_WAVE, PLANET_EXTRA_SWAY };
struct PlanetProfile {
  const char* cmd;
  const char* face;
  const char* face2;
  float gravity;
  float tempo;
  int   motorDelay;
  float crouch;
  float bounceDepth;
  uint8_t bounceCount;
  float hang;
  uint8_t strainCount;
  float strainDepth;
  PlanetExtra extra;
  uint8_t extraCount;
  uint8_t walkCycles;
};
const PlanetProfile PLANET_PROFILES[] = {
  { "moon",    "excited",   "excited", 0.165f, 0.41f, 20,   0.0f,   0.25f,  6, 2.5f, 0,     0.0f,   PLANET_EXTRA_NONE,   0, 10 },
  { "mars",    "surprised", "sad",     0.378f, 0.61f, 20,   0.0f,   0.19f,  3, 1.0f, 0,     0.0f,   PLANET_EXTRA_SHIVER, 4,  8 },
  { "earth",   "happy",     "happy",   1.000f, 1.00f, 20,   0.0f,   0.10f,  1, 1.0f, 0,     0.0f,   PLANET_EXTRA_WAVE,   2,  6 },
  { "jupiter", "angry",     "sleepy",  2.527f, 1.59f, 51,   0.305f, 0.0f,   0, 1.0f, 2,     0.455f, PLANET_EXTRA_SWAY,   2,  2 },
};
struct PlanetWalkFrame { uint8_t count; uint8_t ch[4]; uint8_t angle[4]; };
const PlanetWalkFrame PLANET_WALK_START = { 4, {R3, L3, R2, L1}, {135, 45, 100, 25} };
const PlanetWalkFrame PLANET_WALK_CYCLE[] = {
  { 2, {R3, L3},         {135, 0} },
  { 4, {L4, L2, R4, R1}, {135, 90, 0, 180} },
  { 2, {R2, L1},         {45, 90} },
  { 2, {R4, L4},         {45, 180} },
  { 4, {R3, L3, R2, L1}, {180, 45, 90, 0} },
  { 2, {L2, R1},         {135, 90} },
};
inline float planetDepth(float d) {
  d *= PLANET_INTENSITY;
  return constrain(d, 0.0f, PLANET_MAX_DEPTH);
}
inline int planetMs(const PlanetProfile& p, float baseMs) {
  return (int)(baseMs * p.tempo + 0.5f);
}
inline bool planetIsKnee(uint8_t ch) {
  return ch == R3 || ch == R4 || ch == L3 || ch == L4;
}
inline int planetKneeAngle(uint8_t ch, float depth) {
  depth = constrain(depth, 0.0f, PLANET_MAX_DEPTH);
  int delta = (int)(depth * 90.0f + 0.5f);
  return (ch == R4 || ch == L3) ? delta : 180 - delta;
}
inline void planetKnees(float left, float right) {
  setServoAngle(R4, planetKneeAngle(R4, right));
  setServoAngle(R3, planetKneeAngle(R3, right));
  setServoAngle(L3, planetKneeAngle(L3, left));
  setServoAngle(L4, planetKneeAngle(L4, left));
}
inline bool planetEase(const PlanetProfile& p, float from, float to, int ms) {
  for (uint8_t i = 1; i <= PLANET_EASE_STEPS; i++) {
    float d = from + (to - from) * i / PLANET_EASE_STEPS;
    planetKnees(d, d);
    if (!pressingCheck(p.cmd, ms / PLANET_EASE_STEPS)) return false;
  }
  return true;
}
inline void planetWalkFrame(const PlanetWalkFrame& f, float depth) {
  for (uint8_t i = 0; i < f.count; i++) {
    int angle = f.angle[i];
    if (planetIsKnee(f.ch[i])) angle += planetKneeAngle(f.ch[i], depth) - planetKneeAngle(f.ch[i], 0);
    setServoAngle(f.ch[i], constrain(angle, 0, 180));
  }
}
inline bool planetWalk(const PlanetProfile& p, float depth) {
  int dwell = max(planetMs(p, PLANET_BASE_FRAME_MS), PLANET_MIN_FRAME_MS);
  planetWalkFrame(PLANET_WALK_START, depth);
  if (!pressingCheck(p.cmd, dwell)) return false;
  for (uint8_t c = 0; c < p.walkCycles; c++) {
    for (const PlanetWalkFrame& f : PLANET_WALK_CYCLE) {
      planetWalkFrame(f, depth);
      if (!pressingCheck(p.cmd, dwell)) return false;
    }
  }
  return true;
}
inline bool runPlanetSequence(const PlanetProfile& p) {
  setFaceWithMode(p.face, FACE_ANIM_ONCE);
  runStandPose(0);
  if (!pressingCheck(p.cmd, planetMs(p, PLANET_SETTLE_MS))) return false;
  float bounce = planetDepth(p.bounceDepth);
  for (uint8_t i = 0; i < p.bounceCount; i++) {
    planetKnees(bounce, bounce);
    if (!pressingCheck(p.cmd, planetMs(p, PLANET_BOUNCE_MS))) return false;
    planetKnees(0, 0);
    if (!pressingCheck(p.cmd, planetMs(p, PLANET_BOUNCE_MS * p.hang))) return false;
  }
  float crouch = planetDepth(p.crouch);
  float depth = 0;
  if (p.strainCount > 0) {
    float strain = planetDepth(p.strainDepth);
    if (!planetEase(p, 0, crouch, planetMs(p, PLANET_SETTLE_MS))) return false;
    for (uint8_t i = 0; i < p.strainCount; i++) {
      if (!planetEase(p, crouch, strain, planetMs(p, PLANET_STRAIN_HOLD_MS))) return false;
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_STRAIN_HOLD_MS))) return false;
      if (!planetEase(p, strain, crouch, planetMs(p, PLANET_STRAIN_PAUSE_MS))) return false;
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_STRAIN_PAUSE_MS))) return false;
    }
    depth = crouch;
  }
  setFaceWithMode(p.face2, FACE_ANIM_ONCE);
  if (p.extra == PLANET_EXTRA_SHIVER) {
    float s = planetDepth(PLANET_SHIVER_DEPTH);
    for (uint8_t i = 0; i < p.extraCount; i++) {
      planetKnees(depth + s, depth + s);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_SHIVER_MS))) return false;
      planetKnees(depth, depth);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_SHIVER_MS))) return false;
    }
  } else if (p.extra == PLANET_EXTRA_SWAY && PLANET_STORM_SWAY) {
    float s = planetDepth(PLANET_SWAY_DEPTH);
    for (uint8_t i = 0; i < p.extraCount; i++) {
      planetKnees(depth + s, depth - s);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_STRAIN_HOLD_MS))) return false;
      planetKnees(depth - s, depth + s);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_STRAIN_HOLD_MS))) return false;
    }
    planetKnees(depth, depth);
  }
  float walkDepth = PLANET_CROUCH_WALK ? crouch : 0;
  if (depth != walkDepth) {
    if (!planetEase(p, depth, walkDepth, planetMs(p, PLANET_SETTLE_MS))) return false;
  }
  if (!planetWalk(p, walkDepth)) return false;
  if (p.extra == PLANET_EXTRA_WAVE) {
    runStandPose(0);
    if (!pressingCheck(p.cmd, planetMs(p, PLANET_SETTLE_MS))) return false;
    setServoAngle(R4, 80); setServoAngle(L3, 180);
    setServoAngle(L2, 90); setServoAngle(R1, 100);
    if (!pressingCheck(p.cmd, planetMs(p, PLANET_SETTLE_MS))) return false;
    for (uint8_t i = 0; i < p.extraCount; i++) {
      setServoAngle(L3, 100);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_WAVE_MS))) return false;
      setServoAngle(L3, 180);
      if (!pressingCheck(p.cmd, planetMs(p, PLANET_WAVE_MS))) return false;
    }
  }
  return true;
}
inline void runPlanetPose(const PlanetProfile& p) {
  Serial.print(F("PLANET ")); Serial.println(p.cmd);
  int savedMotorDelay = motorCurrentDelay;
  if (motorCurrentDelay < p.motorDelay) motorCurrentDelay = p.motorDelay;
  planetDisplayStart(p.cmd);
  if (runPlanetSequence(p)) runStandPose(1);
  planetDisplayStop();
  motorCurrentDelay = savedMotorDelay;
  if (currentCommand == p.cmd) currentCommand = "";
}
inline void runMoonPose()    { runPlanetPose(PLANET_PROFILES[0]); }
inline void runMarsPose()    { runPlanetPose(PLANET_PROFILES[1]); }
inline void runEarthPose()   { runPlanetPose(PLANET_PROFILES[2]); }
inline void runJupiterPose() { runPlanetPose(PLANET_PROFILES[3]); }