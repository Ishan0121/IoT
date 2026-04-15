/*
 * ============================================================
 * Experiment 03 — Blinking LED Sketch with Arduino
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Define Timing Constants
// ─────────────────────────────────────────────────────────────
// Instead of writing 'delay(500)' everywhere with a magic number,
// define named constants for your timing values.
// This makes it easy to change timing from one place.
//
// YOUR TASK: Define two timing constants:
//   const int ON_TIME  = ???;   ← milliseconds LED is ON
//   const int OFF_TIME = ???;   ← milliseconds LED is OFF
//
// Start with: ON_TIME = 500, OFF_TIME = 500 (equal blink)
// Then experiment: try 100/900, 900/100, 250/250


// ─────────────────────────────────────────────────────────────
// STEP 2: Define LED Pin
// ─────────────────────────────────────────────────────────────
// Define which Arduino pin the LED is connected to.
//
// YOUR TASK:
//   const int LED_PIN = ???;   ← what pin did you wire to?
//
// Note: If you use pin 13, the BUILT-IN LED will also blink!
// This is a great way to verify your code without external wiring.


// ─────────────────────────────────────────────────────────────
// STEP 3: Declare a Counter Variable
// ─────────────────────────────────────────────────────────────
// We want to count how many times the LED has blinked.
// This counter lives OUTSIDE setup() and loop() so it persists.
//
// YOUR TASK:
//   int blinkCount = 0;   ← starts at 0, increases each blink


// ─────────────────────────────────────────────────────────────
// STEP 4: setup() Function
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Configure LED_PIN as OUTPUT
//   → Pins default to INPUT — you must explicitly set OUTPUT
//   → Hint: pinMode(LED_PIN, OUTPUT);
//
//   Task B: Start Serial communication
//   → Hint: Serial.begin(9600);
//
//   Task C: Print header message
//   → Serial.println("=== LED Blink Experiment ===");
//   → Serial.print("ON  time : "); Serial.print(ON_TIME); Serial.println(" ms");
//   → Serial.print("OFF time : "); Serial.print(OFF_TIME); Serial.println(" ms");
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: loop() Function — Core Blink Logic
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Task A: Increment the blink counter
//   → blinkCount++;
//
//   Task B: Turn LED ON
//   → Hint: digitalWrite(LED_PIN, HIGH);
//   → Print: "Blink #X: ON for Y ms"
//     Serial.print("Blink #"); Serial.print(blinkCount);
//     Serial.print(": ON for "); Serial.print(ON_TIME); Serial.println(" ms");
//
//   Task C: Wait for ON_TIME
//   → Hint: delay(ON_TIME);
//
//   Task D: Turn LED OFF
//   → Hint: digitalWrite(LED_PIN, LOW);
//   → Print: "Blink #X: OFF for Y ms"
//
//   Task E: Wait for OFF_TIME
//   → Hint: delay(OFF_TIME);
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 6: Understand delay() Limitations
// ─────────────────────────────────────────────────────────────
// delay() BLOCKS everything. The Arduino literally does nothing else.
// This is problem when:
//   - You want to read a button simultaneously
//   - You want multiple things happening at different rates
//
// NON-BLOCKING alternative using millis():
//
// unsigned long previousMs = 0;   ← stored outside loop()
// bool ledState = false;
//
// void loop() {
//   unsigned long currentMs = millis();   ← time since boot in ms
//
//   if (currentMs - previousMs >= INTERVAL) {
//     previousMs = currentMs;
//     ledState = !ledState;                ← toggle
//     digitalWrite(LED_PIN, ledState);
//   }
//   // ← Other code here runs WITHOUT waiting!
// }
//
// YOUR TASK (CHALLENGE):
//   Rewrite your loop() using millis() instead of delay()
//   Hint: You need TWO timers — one for ON interval, one for OFF


// ─────────────────────────────────────────────────────────────
// STEP 7: PWM Fade Challenge
// ─────────────────────────────────────────────────────────────
// PWM (Pulse Width Modulation) simulates analog output on digital pins.
// On PWM-capable pins (3,5,6,9,10,11 on UNO), use analogWrite():
//
//   analogWrite(pin, 0);     ← 0% duty cycle = LED fully OFF
//   analogWrite(pin, 127);   ← 50% duty cycle = LED half brightness
//   analogWrite(pin, 255);   ← 100% duty cycle = LED fully ON
//
// MOVE YOUR LED to a PWM pin (e.g., Pin 9 or Pin 6)
//
// Then in loop():
//   for (int brightness = 0; brightness <= 255; brightness++) {
//     analogWrite(LED_PIN, brightness);   ← fade in
//     delay(5);
//   }
//   for (int brightness = 255; brightness >= 0; brightness--) {
//     analogWrite(LED_PIN, brightness);   ← fade out
//     delay(5);
//   }
