/*
 * ============================================================
 * Experiment 06 — Servo Motor and Stepper Motor Handling
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * PART A: Servo SG90 — Sweep + Potentiometer control
 *   Circuit: Servo Orange → Pin 9, Pot wiper → A0
 *
 * PART B: Stepper 28BYJ-48 + ULN2003
 *   Circuit: IN1→8, IN2→9, IN3→10, IN4→11
 *
 * Run PART A and PART B SEPARATELY (comment one out at a time).
 * ============================================================
 */

// ── Choose which part to run ───────────────────────────────
// Comment ONE line out:
#define RUN_SERVO    // ← activate servo experiment
// #define RUN_STEPPER  // ← activate stepper experiment


// ══════════════════════════════════════════════════════════
// PART A: SERVO MOTOR
// ══════════════════════════════════════════════════════════
#ifdef RUN_SERVO

#include <Servo.h>

const int SERVO_PIN = 9;
const int POT_PIN   = A0;

Servo myServo;
int   currentAngle  = 90;

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(90);
  delay(500);
  Serial.println(F("=== Servo Motor Control ==="));
  Serial.println(F("Mode 1 (5s): Automatic sweep 0-180"));
  Serial.println(F("Mode 2     : Potentiometer control"));
  Serial.println();
}

// Smooth move to target angle
void moveTo(int target, int stepDelay = 15) {
  int step = (target > currentAngle) ? 1 : -1;
  while (currentAngle != target) {
    currentAngle += step;
    myServo.write(currentAngle);
    Serial.print(F("Angle: "));
    Serial.println(currentAngle);
    delay(stepDelay);
  }
}

void loop() {
  static unsigned long startTime = millis();
  static bool sweepDone = false;

  // ── Mode 1: Auto sweep for first 5 seconds ───────────────
  if (!sweepDone && (millis() - startTime < 5000)) {
    Serial.println(F("[Auto Sweep] 0 → 180"));
    moveTo(180, 10);
    Serial.println(F("[Auto Sweep] 180 → 0"));
    moveTo(0, 10);
    sweepDone = true;
    Serial.println(F("[Switching to Potentiometer control]"));
    return;
  }

  // ── Mode 2: Potentiometer-controlled angle ────────────────
  int potVal = analogRead(POT_PIN);
  int target = map(potVal, 0, 1023, 0, 180);

  if (abs(target - currentAngle) > 2) { // Only move if change > 2°
    myServo.write(target);
    currentAngle = target;
    Serial.print(F("Pot: "));
    Serial.print(potVal);
    Serial.print(F(" → Angle: "));
    Serial.println(target);
  }
  delay(50);
}

#endif // RUN_SERVO


// ══════════════════════════════════════════════════════════
// PART B: STEPPER MOTOR
// ══════════════════════════════════════════════════════════
#ifdef RUN_STEPPER

#include <Stepper.h>

const int STEPS_PER_REV = 2048;

// NOTE: Pin order for 28BYJ-48 is: IN1, IN3, IN2, IN4
Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10); // 10 RPM
  Serial.println(F("=== 28BYJ-48 Stepper Motor Control ==="));
  Serial.println(F("Speed: 10 RPM | Steps/rev: 2048"));
  Serial.println();
}

void rotateDeg(float degrees, bool clockwise) {
  long steps = (long)((degrees / 360.0) * STEPS_PER_REV);
  if (!clockwise) steps = -steps;
  Serial.print(clockwise ? F("CW  ") : F("CCW "));
  Serial.print(abs(degrees));
  Serial.print(F("° = "));
  Serial.print(abs(steps));
  Serial.println(F(" steps"));
  myStepper.step(steps);
}

void loop() {
  Serial.println(F("--- Full Rotation CW ---"));
  rotateDeg(360, true);
  delay(1000);

  Serial.println(F("--- 90° CCW ---"));
  rotateDeg(90, false);
  delay(500);

  Serial.println(F("--- 180° CW ---"));
  rotateDeg(180, true);
  delay(500);

  Serial.println(F("--- 90° CCW ---"));
  rotateDeg(90, false);
  delay(1000);
}

#endif // RUN_STEPPER
