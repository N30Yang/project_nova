#include <Arduino.h>
#include <ESP32Servo.h>
Servo servos[8];
const int servoPins[8] = {15, 2, 23, 19, 4, 16, 17, 18};
const int MIN_PULSE = 544;
const int MAX_PULSE = 2400;
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("-----------------------------------");
  Serial.println("      Motor Tester Interface       ");
  Serial.println("-----------------------------------");
  Serial.println("Commands:");
  Serial.println("1. id,angle   -> e.g. '0,90'");
  Serial.println("2. all,angle  -> e.g. 'all,90'");
  Serial.println("3. stop       -> Detaches/Powers down motors");
  Serial.println("-----------------------------------");
  Serial.println("Status: Motors are currently OFF (Limp).");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
}
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() == 0) return;
    if (input.equalsIgnoreCase("stop")) {
      stopMotors();
      return;
    }
    int commaIndex = input.indexOf(',');
    if (commaIndex != -1) {
      String cmd = input.substring(0, commaIndex);
      String valStr = input.substring(commaIndex + 1);
      int angle = valStr.toInt();
      if (angle < 0) angle = 0;
      if (angle > 180) angle = 180;
      if (cmd.equalsIgnoreCase("all")) {
        moveAll(angle);
      } else {
        int motorId = cmd.toInt();
        if (motorId == 0 && cmd.charAt(0) != '0') {
           Serial.println("Error: Invalid Motor ID");
        } else {
           moveMotor(motorId, angle);
        }
      }
    } else {
      Serial.println("Error: Invalid format. Use 'id,angle', 'all,angle', or 'stop'.");
    }
  }
}
void moveMotor(int id, int angle) {
  if (id < 0 || id > 7) {
    Serial.println("Error: Motor ID must be 0-7");
    return;
  }
  if (!servos[id].attached()) {
    servos[id].setPeriodHertz(50);
    servos[id].attach(servoPins[id], MIN_PULSE, MAX_PULSE);
  }
  servos[id].write(angle);
  Serial.print("OK: Motor ");
  Serial.print(id);
  Serial.print(" -> ");
  Serial.println(angle);
}
void moveAll(int angle) {
  Serial.print("Moving ALL to ");
  Serial.println(angle);
  for (int i = 0; i < 8; i++) {
    moveMotor(i, angle);
  }
}
void stopMotors() {
  Serial.println("Stopping (Detaching) all motors...");
  for (int i = 0; i < 8; i++) {
    if (servos[i].attached()) {
      servos[i].detach();
    }
  }
  Serial.println("Motors are now OFF.");
}