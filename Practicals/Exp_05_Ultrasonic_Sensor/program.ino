/*
 * ============================================================
 * Experiment 05 — HC-SR04 Ultrasonic Distance Sensor
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Circuit:
 *   TRIG     → Pin 9
 *   ECHO     → Pin 10
 *   Green LED → Pin 4 (safe)
 *   Yellow LED→ Pin 5 (caution)
 *   Red LED  → Pin 6 (danger)
 *   Buzzer   → Pin 7
 * ============================================================
 */

// ── Pin Constants ─────────────────────────────────────────
const int TRIG_PIN   = 9;
const int ECHO_PIN   = 10;
const int GREEN_LED  = 4;
const int YELLOW_LED = 5;
const int RED_LED    = 6;
const int BUZZ_PIN   = 7;

// ── Zone Thresholds (cm) ───────────────────────────────────
const int DANGER_CM  = 20;
const int CAUTION_CM = 40;

// ── State tracking for non-blocking buzzer ─────────────────
unsigned long lastBuzzToggle = 0;
bool          buzzState      = false;
int           buzzInterval   = 0; // ms between beeps (0 = off)

// ── Get raw distance ──────────────────────────────────────
long getRawDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000); // 25ms timeout
  if (duration == 0) return -1; // Timeout — out of range
  return (duration * 0.0343) / 2;
}

// ── Smoothed distance (average of 5) ──────────────────────
long getDistance() {
  long sum   = 0;
  int  valid = 0;
  for (int i = 0; i < 5; i++) {
    long d = getRawDistance();
    if (d > 0 && d <= 400) {
      sum += d;
      valid++;
    }
    delay(15);
  }
  return (valid > 0) ? (sum / valid) : -1;
}

// ── All LEDs off ──────────────────────────────────────────
void allLedsOff() {
  digitalWrite(GREEN_LED,  LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED,    LOW);
}

// ── Update zone alerts ────────────────────────────────────
void updateAlerts(long dist) {
  allLedsOff();

  if (dist < DANGER_CM) {
    digitalWrite(RED_LED, HIGH);
    buzzInterval = 100; // Fast beep
    Serial.print(F("[DANGER ] "));
  } else if (dist < CAUTION_CM) {
    digitalWrite(YELLOW_LED, HIGH);
    buzzInterval = 400; // Slow beep
    Serial.print(F("[CAUTION] "));
  } else {
    digitalWrite(GREEN_LED, HIGH);
    buzzInterval = 0;
    digitalWrite(BUZZ_PIN, LOW);
    Serial.print(F("[  SAFE ] "));
  }

  Serial.print(dist);
  Serial.println(F(" cm"));
}

// ── Non-blocking buzzer update ────────────────────────────
void updateBuzzer() {
  if (buzzInterval == 0) return;
  unsigned long now = millis();
  if (now - lastBuzzToggle >= (unsigned long)buzzInterval) {
    lastBuzzToggle = now;
    buzzState = !buzzState;
    digitalWrite(BUZZ_PIN, buzzState ? HIGH : LOW);
  }
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN,   OUTPUT);
  pinMode(ECHO_PIN,   INPUT);
  pinMode(GREEN_LED,  OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED,    OUTPUT);
  pinMode(BUZZ_PIN,   OUTPUT);

  allLedsOff();
  digitalWrite(BUZZ_PIN, LOW);

  delay(200);
  Serial.println(F("=== HC-SR04 Ultrasonic Distance Sensor ==="));
  Serial.println(F("Danger  : < 20 cm  | Red LED + Fast Beep"));
  Serial.println(F("Caution : 20-40 cm | Yellow LED + Slow Beep"));
  Serial.println(F("Safe    : > 40 cm  | Green LED | Silent"));
  Serial.println(F("Readings averaged over 5 samples."));
  Serial.println();
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  long dist = getDistance();

  if (dist < 0) {
    Serial.println(F("[------] Out of range or no echo"));
    allLedsOff();
    buzzInterval = 0;
  } else {
    updateAlerts(dist);
  }

  updateBuzzer();
  delay(50);
}
