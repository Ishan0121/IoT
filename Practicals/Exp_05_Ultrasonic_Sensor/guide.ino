/*
 * ============================================================
 * Experiment 05 — Ultrasonic Sensor Handling with Arduino
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Define Sensor and Alert Pins
// ─────────────────────────────────────────────────────────────
// You need four types of pins:
//   1. TRIG_PIN — sends the ultrasonic trigger pulse (OUTPUT)
//   2. ECHO_PIN — receives the echo back (INPUT)
//   3. LED pins — 3 LEDs for zone indication
//   4. BUZZ_PIN — buzzer for audio alert
//
// YOUR TASK:
//   const int TRIG_PIN   = 9;
//   const int ECHO_PIN   = 10;
//   const int GREEN_LED  = 4;   // Safe zone
//   const int YELLOW_LED = 5;   // Caution zone
//   const int RED_LED    = 6;   // Danger zone
//   const int BUZZ_PIN   = 7;
//
// Also define zone thresholds:
//   const int DANGER_CM  = 20;  // below this = DANGER
//   const int CAUTION_CM = 40;  // below this = CAUTION


// ─────────────────────────────────────────────────────────────
// STEP 2: Understanding pulseIn()
// ─────────────────────────────────────────────────────────────
// pulseIn(pin, HIGH) does three things:
//   a) Waits for the pin to go HIGH
//   b) Starts a microsecond timer
//   c) Waits for pin to go LOW again, then returns elapsed time
//
// It returns: duration in MICROSECONDS (µs)
//
// THINK ABOUT:
//   If the object is 17 cm away, what is the echo duration?
//   Use: time = (2 × distance) / speed_of_sound
//        = (2 × 17) / 0.0343 = 991 µs
//
// YOUR TASK: Trace through this with 30 cm and 5 cm manually.


// ─────────────────────────────────────────────────────────────
// STEP 3: Create getDistance() Function
// ─────────────────────────────────────────────────────────────
// This is the CORE of the experiment.
//
// long getDistance() {
//
//   Step A: Clear the TRIG pin first
//   → digitalWrite(TRIG_PIN, LOW);
//   → delayMicroseconds(2);   ← wait 2 µs (not ms!)
//
//   Step B: Send a 10-microsecond HIGH pulse on TRIG
//   → digitalWrite(TRIG_PIN, HIGH);
//   → delayMicroseconds(10);
//   → digitalWrite(TRIG_PIN, LOW);
//
//   Why exactly 10µs? The HC-SR04 datasheet requires a minimum
//   10µs trigger pulse to start the ultrasonic burst.
//
//   Step C: Measure echo duration
//   → long duration = pulseIn(ECHO_PIN, HIGH);
//   → This waits for echo and measures how long it stays HIGH
//
//   Step D: Convert to centimetres
//   → long distance = (duration * 0.0343) / 2;
//   → Return distance;
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 4: setup() Function
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Set pin modes
//   → TRIG_PIN: OUTPUT  (we send the pulse)
//   → ECHO_PIN: INPUT   (we receive the echo)
//   → GREEN_LED, YELLOW_LED, RED_LED: OUTPUT
//   → BUZZ_PIN: OUTPUT
//
//   Task B: Serial.begin(9600)
//
//   Task C: Turn all LEDs OFF initially
//   → digitalWrite(GREEN_LED, LOW);
//   → [same for yellow and red]
//
//   Task D: Print header
//   → "=== HC-SR04 Ultrasonic Distance Sensor ==="
//   → "Danger zone : < 20 cm"
//   → "Caution zone: 20-40 cm"
//   → "Safe zone   : > 40 cm"
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: Create updateAlerts() Function
// ─────────────────────────────────────────────────────────────
// void updateAlerts(long dist) {
//
//   First, turn ALL alerts off:
//   → digitalWrite(GREEN_LED, LOW);
//   → digitalWrite(YELLOW_LED, LOW);
//   → digitalWrite(RED_LED, LOW);
//   → digitalWrite(BUZZ_PIN, LOW);
//
//   Then check zone and activate appropriate alert:
//
//   if (dist < DANGER_CM) {
//     → RED LED ON
//     → Buzzer ON (rapid beep with tone() or digitalWrite pattern)
//     → Print "⚠ DANGER: X cm"
//   }
//   else if (dist < CAUTION_CM) {
//     → YELLOW LED ON
//     → Buzzer slow beep
//     → Print "! CAUTION: X cm"
//   }
//   else {
//     → GREEN LED ON
//     → Buzzer OFF
//     → Print "✓ SAFE: X cm"
//   }
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 6: loop() Function
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Task A: Get reading
//   → long dist = getDistance();
//
//   Task B: Validate reading
//   → if (dist <= 0 || dist > 400) { print "Out of range"; return; }
//
//   Task C: Update alerts
//   → updateAlerts(dist);
//
//   Task D: Delay for stability
//   → delay(100);  ← 10 readings per second
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: Smooth Readings with Averaging
// ─────────────────────────────────────────────────────────────
// Single readings can be noisy. Use an AVERAGE of 5 readings:
//
// long getSmoothedDistance() {
//   long sum = 0;
//   for (int i = 0; i < 5; i++) {
//     sum += getDistance();
//     delay(20);
//   }
//   return sum / 5;
// }
//
// YOUR CHALLENGE: Replace getDistance() with getSmoothedDistance()
// → Does the reading become more stable?


// ─────────────────────────────────────────────────────────────
// CHALLENGE: Serial Plotter Visualisation
// ─────────────────────────────────────────────────────────────
// The Serial Plotter can graph your distance in real-time!
//
// In loop(), instead of printing text, just print the number:
//   Serial.println(dist);
//
// Open Tools → Serial Plotter — watch live distance graph!
// Move your hand back and forth in front of sensor.
// What wave pattern do you see?
