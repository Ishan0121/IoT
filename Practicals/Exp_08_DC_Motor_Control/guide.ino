/*
 * ============================================================
 * Experiment 08 — DC Motor Speed and Direction Control
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Define L298N Driver Pins
// ─────────────────────────────────────────────────────────────
// The L298N has 3 control pins for ONE motor channel:
//   IN1 — direction bit 1 (digital)
//   IN2 — direction bit 2 (digital)
//   ENA — enable / speed via PWM (must be a ~ PWM pin!)
//
// YOUR TASK:
//   const int IN1_PIN = 5;   // Direction
//   const int IN2_PIN = 6;   // Direction
//   const int ENA_PIN = 9;   // PWM speed (pin 9 is PWM-capable)
//
// Also define:
//   const int POT_PIN = A0;   // Potentiometer wiper for speed
//   const int BTN_PIN = 2;    // Direction toggle button


// ─────────────────────────────────────────────────────────────
// STEP 2: Declare Direction and State Variables
// ─────────────────────────────────────────────────────────────
// You need variables to TRACK current state between loops:
//
//   bool motorForward = true;   // true = CW, false = CCW
//   bool lastBtnState = HIGH;   // Tracks previous button state
//                               // HIGH because INPUT_PULLUP
//
// Why track lastBtnState?
// → To detect the EDGE (HIGH→LOW transition = button press)
// → This prevents one press from registering as many presses


// ─────────────────────────────────────────────────────────────
// STEP 3: setup() Function
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Set motor driver pins as OUTPUT
//   → pinMode(IN1_PIN, OUTPUT);
//   → pinMode(IN2_PIN, OUTPUT);
//   → pinMode(ENA_PIN, OUTPUT);
//
//   Task B: Set button as INPUT_PULLUP
//   → pinMode(BTN_PIN, INPUT_PULLUP);
//   → INPUT_PULLUP enables Arduino's internal pull-up resistor
//   → Pin reads HIGH normally, LOW when button pressed
//   → No external resistor needed!
//
//   Task C: Motor starts STOPPED
//   → analogWrite(ENA_PIN, 0);
//
//   Task D: Serial begin and print header
//   → "DC Motor Control Ready"
//   → "Potentiometer: A0 | Button: Pin 2"
//   → "Turn POT for speed, press button for direction"
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 4: Create setDirection() Function
// ─────────────────────────────────────────────────────────────
// This function sets IN1 and IN2 based on direction flag.
//
// void setDirection(bool forward) {
//   if (forward) {
//     → digitalWrite(IN1_PIN, HIGH);
//     → digitalWrite(IN2_PIN, LOW);
//     // L298N truth table: IN1=H, IN2=L → Motor rotates CW
//   } else {
//     → digitalWrite(IN1_PIN, LOW);
//     → digitalWrite(IN2_PIN, HIGH);
//     // IN1=L, IN2=H → Motor rotates CCW
//   }
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: Create setSpeed() Function
// ─────────────────────────────────────────────────────────────
// Speed is controlled by PWM on the ENA pin.
// analogWrite() takes values 0–255.
// 0 = stopped, 255 = full speed.
//
// void setSpeed(int pwmValue) {
//   → analogWrite(ENA_PIN, pwmValue);
//   → int percent = map(pwmValue, 0, 255, 0, 100);
//   → Serial.print("Speed: "); Serial.print(percent); Serial.println("%");
// }
//
// THINK ABOUT: What does map() do here?
// map(value, fromLow, fromHigh, toLow, toHigh)
// Converts 0–255 to 0–100 for human-readable display.


// ─────────────────────────────────────────────────────────────
// STEP 6: Button Debounce Logic
// ─────────────────────────────────────────────────────────────
// A button press must be detected ONCE, not 10–20 times from bounce.
//
// void checkButton() {
//   bool currentState = digitalRead(BTN_PIN);
//
//   // Detect FALLING EDGE (HIGH → LOW means button just pressed)
//   if (lastBtnState == HIGH && currentState == LOW) {
//     → delay(50);  ← debounce: wait 50ms for contacts to settle
//     → re-read the button: if still LOW, it's a real press
//     →   motorForward = !motorForward;  ← FLIP direction
//     →   setDirection(motorForward);
//     →   Print: "Direction: FORWARD" or "REVERSE"
//   }
//
//   lastBtnState = currentState; ← update for next iteration
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: loop() Function
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Task A: Read potentiometer
//   → int potVal = analogRead(POT_PIN);  ← 0 to 1023
//   → int pwm = map(potVal, 0, 1023, 0, 255);  ← scale to PWM
//
//   Task B: Apply speed
//   → setSpeed(pwm);
//
//   Task C: Apply current direction
//   → setDirection(motorForward);
//
//   Task D: Check button for direction change
//   → checkButton();
//
//   Task E: Print status
//   → Serial.print("Dir: "); Serial.print(motorForward ? "FWD" : "REV");
//   → Serial.print(" | PWM: "); Serial.println(pwm);
//
//   Task F: Small delay
//   → delay(50);
//
// }


// ─────────────────────────────────────────────────────────────
// CHALLENGE: Soft Start (Speed Ramping)
// ─────────────────────────────────────────────────────────────
// Sudden full-speed start stresses the motor and causes spikes.
// Ramp from 0 to target speed gradually.
//
// void rampTo(int targetPWM) {
//   static int currentPWM = 0;
//   if (currentPWM < targetPWM) currentPWM++;
//   else if (currentPWM > targetPWM) currentPWM--;
//   analogWrite(ENA_PIN, currentPWM);
// }
//
// Call rampTo(pwm) in loop() instead of setSpeed(pwm)
// The motor will smoothly accelerate and decelerate!
