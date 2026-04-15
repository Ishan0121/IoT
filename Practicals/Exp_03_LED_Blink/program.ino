/*
 * ============================================================
 * Experiment 03 — Blinking LED Sketch with Arduino
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Demonstrates:
 *   - External LED with 220Ω resistor on Digital Pin 9 (PWM)
 *   - Delay-based blink with Serial logging
 *   - Non-blocking blink using millis()
 *   - PWM fade-in / fade-out
 *   - Blink counter with configurable timing
 * ============================================================
 * Circuit:
 *   Pin 9 → 220Ω → LED(+) → LED(−) → GND
 * ============================================================
 */

// ── Constants ─────────────────────────────────────────────
const int LED_PIN  = 9;     // PWM-capable pin for fade support
const int ON_TIME  = 700;   // ms LED stays ON
const int OFF_TIME = 300;   // ms LED stays OFF

// ── Globals ───────────────────────────────────────────────
int           blinkCount  = 0;
bool          ledState    = false;
unsigned long lastToggle  = 0;

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  delay(200);
  Serial.println(F("=== Experiment 03: LED Blink ==="));
  Serial.print(F("LED Pin  : ")); Serial.println(LED_PIN);
  Serial.print(F("ON  Time : ")); Serial.print(ON_TIME); Serial.println(F(" ms"));
  Serial.print(F("OFF Time : ")); Serial.print(OFF_TIME); Serial.println(F(" ms"));
  Serial.println(F("Mode     : Non-blocking (millis)"));
  Serial.println();
}

// ── Non-blocking blink using millis() ─────────────────────
void updateBlink() {
  unsigned long now       = millis();
  unsigned long interval  = ledState ? ON_TIME : OFF_TIME;

  if (now - lastToggle >= interval) {
    lastToggle = now;
    ledState   = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    if (ledState) {
      blinkCount++;
      Serial.print(F("Blink #"));
      Serial.print(blinkCount);
      Serial.print(F(": ON for "));
      Serial.print(ON_TIME);
      Serial.println(F(" ms"));
    } else {
      Serial.print(F("Blink #"));
      Serial.print(blinkCount);
      Serial.print(F(": OFF for "));
      Serial.print(OFF_TIME);
      Serial.println(F(" ms"));
    }
  }
}

// ── PWM Fade (called every 10 blinks) ─────────────────────
void fadeLED(int fromBrightness, int toBrightness, int stepDelay) {
  int step = (fromBrightness < toBrightness) ? 1 : -1;
  for (int b = fromBrightness; b != toBrightness + step; b += step) {
    analogWrite(LED_PIN, b);
    delay(stepDelay);
  }
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  updateBlink();

  // ── Every 10 blinks, do a PWM fade sequence ───────────────
  if (blinkCount > 0 && blinkCount % 10 == 0) {
    static int lastFade = 0;
    if (blinkCount != lastFade) {
      lastFade = blinkCount;
      Serial.println(F("--- PWM Fade Sequence ---"));
      Serial.println(F("  Fading IN..."));
      fadeLED(0, 255, 5);    // Fade in over ~1.3s
      Serial.println(F("  Fading OUT..."));
      fadeLED(255, 0, 5);    // Fade out over ~1.3s
      lastToggle = millis(); // Re-sync non-blocking timer
    }
  }
}
