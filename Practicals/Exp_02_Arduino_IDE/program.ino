/*
 * ============================================================
 * Experiment 02 — Installing and Working with Arduino IDE
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Demonstrates:
 *   - Serial.begin(), Serial.print(), Serial.println()
 *   - Static counter variable
 *   - LED blink with state tracking
 *   - Serial Plotter-compatible output
 *   - Helper function (blinkPattern)
 *   - SOS challenge pattern
 * ============================================================
 */

// ── Constants ─────────────────────────────────────────────
const int LED_PIN   = 13;
const int BAUD_RATE = 9600;

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);

  delay(300);
  Serial.println(F("=== Arduino IDE First Sketch ==="));
  Serial.println(F("Author     : Student Name"));
  Serial.println(F("Experiment : 02 — IDE Familiarization"));
  Serial.println(F("Board      : Arduino UNO"));
  Serial.println(F("Setup complete. Entering main loop..."));
  Serial.println();
}

// ── Helper: blink LED n times ─────────────────────────────
void blinkNTimes(int n, int onMs, int offMs) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(onMs);
    digitalWrite(LED_PIN, LOW);
    delay(offMs);
  }
}

// ── Helper: SOS morse pattern ─────────────────────────────
void sosPattern() {
  Serial.println(F("[SOS Pattern]"));

  // S = three short
  Serial.println(F("  S ..."));
  blinkNTimes(3, 200, 200);
  delay(400);

  // O = three long
  Serial.println(F("  O ---"));
  blinkNTimes(3, 600, 200);
  delay(400);

  // S = three short
  Serial.println(F("  S ..."));
  blinkNTimes(3, 200, 200);
  delay(2000); // Pause before repeat
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  static int counter = 0;
  counter++;

  // ── Standard Blink ────────────────────────────────────────
  Serial.print("Loop ");
  Serial.print(counter);
  Serial.print(": LED is ON  → Plotter: ");
  Serial.println(1); // Serial Plotter value

  digitalWrite(LED_PIN, HIGH);
  delay(800);

  Serial.print("Loop ");
  Serial.print(counter);
  Serial.print(": LED is OFF → Plotter: ");
  Serial.println(0); // Serial Plotter value

  digitalWrite(LED_PIN, LOW);
  delay(800);

  // ── Run SOS every 5th loop ────────────────────────────────
  if (counter % 5 == 0) {
    sosPattern();
  }
}
