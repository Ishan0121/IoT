/*
 * ============================================================
 * Experiment 06 — Servo Motor and Stepper Motor Handling
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ═══════════════════════════════════════════════════════════
// PART A — SERVO MOTOR (SG90)
// ═══════════════════════════════════════════════════════════


// ─────────────────────────────────────────────────────────────
// STEP A1: Include the Servo Library
// ─────────────────────────────────────────────────────────────
// Arduino does NOT know how to control servos natively.
// We use the built-in Servo.h library.
//
// YOUR TASK: At the very top of your file, write:
//   #include <Servo.h>
//
// This is ALWAYS the first line for servo control.


// ─────────────────────────────────────────────────────────────
// STEP A2: Create a Servo Object
// ─────────────────────────────────────────────────────────────
// Think of a "Servo object" like a remote control for one servo.
// You can create multiple objects for multiple servos.
//
// YOUR TASK: After the include, declare:
//   Servo myServo;
//
// Why call it myServo? Because you will call:
//   myServo.attach(pin)    ← connect it to a pin
//   myServo.write(angle)   ← move to angle


// ─────────────────────────────────────────────────────────────
// STEP A3: setup() for Servo
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Attach the servo to a PWM pin
//   → myServo.attach(9);   ← Pin 9 is PWM-capable
//   → The library handles all PWM signal generation automatically
//
//   Task B: Move servo to HOME position (centre = 90°)
//   → myServo.write(90);
//   → delay(500);  ← give servo time to reach position
//
//   Task C: Serial begin and print "Servo Ready at 90 degrees"
//
// }


// ─────────────────────────────────────────────────────────────
// STEP A4: Sweep Motion in loop()
// ─────────────────────────────────────────────────────────────
// A sweep moves the servo from 0° to 180° and back.
//
// void loop() {
//
//   Phase 1: Sweep from 0 to 180
//   → for (int angle = 0; angle <= 180; angle++) {
//       myServo.write(angle);
//       delay(15);   ← wait 15ms between each 1° step (smooth)
//       Serial.print("Angle: "); Serial.println(angle);
//     }
//
//   Phase 2: Sweep from 180 to 0
//   → for (int angle = 180; angle >= 0; angle--) {
//       myServo.write(angle);
//       delay(15);
//     }
//
// }
//
// QUESTION: Why delay(15) between steps?
// What happens if you use delay(0)?  (Jumps instantly)
// What if you use delay(50)?  (Very slow, visible single steps)


// ─────────────────────────────────────────────────────────────
// STEP A5: Potentiometer-Controlled Servo (Challenge)
// ─────────────────────────────────────────────────────────────
// Wire a potentiometer: 5V → [pot] → GND, middle pin → A0
// Read pot value: int potVal = analogRead(A0);  → gives 0-1023
// Map to angle:  int angle  = map(potVal, 0, 1023, 0, 180);
// Move servo:    myServo.write(angle);
//
// The map() function re-scales one range to another:
//   map(value, fromLow, fromHigh, toLow, toHigh)
//   Example: map(512, 0, 1023, 0, 180) = 90


// ═══════════════════════════════════════════════════════════
// PART B — STEPPER MOTOR (28BYJ-48 + ULN2003)
// ═══════════════════════════════════════════════════════════


// ─────────────────────────────────────────────────────────────
// STEP B1: Include Stepper Library
// ─────────────────────────────────────────────────────────────
// YOUR TASK:
//   #include <Stepper.h>
//
// The built-in Stepper.h library handles the 4-pin step sequence.


// ─────────────────────────────────────────────────────────────
// STEP B2: Define Steps Per Revolution
// ─────────────────────────────────────────────────────────────
// The 28BYJ-48 with ULN2003 in half-step mode:
//   2048 steps = 360° (one full revolution)
//
// YOUR TASK:
//   const int STEPS_PER_REV = 2048;
//
// THINK ABOUT:
//   How many steps to rotate exactly 90°?
//   Answer: 2048 / 4 = 512 steps


// ─────────────────────────────────────────────────────────────
// STEP B3: Create Stepper Object
// ─────────────────────────────────────────────────────────────
// YOUR TASK:
//   Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);
//
// Arguments: (total_steps, IN1_pin, IN3_pin, IN2_pin, IN4_pin)
//
// IMPORTANT: The pin order is NOT 8,9,10,11
// For 28BYJ-48 correct order is: 8, 10, 9, 11
// (This matches the internal coil wiring sequence)
// Wrong order = motor vibrates but doesn't rotate!


// ─────────────────────────────────────────────────────────────
// STEP B4: setup() for Stepper
// ─────────────────────────────────────────────────────────────
// void setup() {
//   Task A: Set motor speed in RPM
//   → myStepper.setSpeed(10);  ← 10 RPM, start slow!
//   → 28BYJ-48 max reliable speed is ~15 RPM
//
//   Task B: Serial.begin(9600) and print "Stepper Ready"
// }


// ─────────────────────────────────────────────────────────────
// STEP B5: loop() for Stepper
// ─────────────────────────────────────────────────────────────
// void loop() {
//   Phase 1: Rotate ONE full revolution CLOCKWISE
//   → myStepper.step(STEPS_PER_REV);  ← positive = CW
//   → delay(1000);
//   → Serial.println("Rotated 360° CW");
//
//   Phase 2: Rotate ONE full revolution COUNTER-CLOCKWISE
//   → myStepper.step(-STEPS_PER_REV); ← negative = CCW
//   → delay(1000);
//   → Serial.println("Rotated 360° CCW");
// }
//
// CHALLENGE: Rotate to specific angles:
//   int stepsFor90  = STEPS_PER_REV / 4;   // 512 steps
//   int stepsFor180 = STEPS_PER_REV / 2;   // 1024 steps
//   myStepper.step(stepsFor90);
//   delay(500);
//   myStepper.step(-stepsFor180);
