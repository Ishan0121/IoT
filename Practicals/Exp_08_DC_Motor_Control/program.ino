/*
 * ============================================================
 * Experiment 08 — DC Motor Speed and Direction Control
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Circuit:
 *   L298N IN1 → Pin 5 | IN2 → Pin 6 | ENA → Pin 9 (PWM)
 *   Potentiometer wiper → A0
 *   Direction button    → Pin 2 (INPUT_PULLUP)
 *   Motor to OUT1/OUT2 of L298N
 *   External 9–12V → L298N 12V & GND (link GND to Arduino GND!)
 * ============================================================
 */

// ── Pin Constants ─────────────────────────────────────────
const int IN1_PIN = 5;
const int IN2_PIN = 6;
const int ENA_PIN = 9;   // Must be PWM-capable!
const int POT_PIN = A0;
const int BTN_PIN = 2;

// ── State Variables ───────────────────────────────────────
bool motorForward  = true;
bool lastBtnState  = HIGH;
int  currentPWM    = 0;    // For soft-start ramping

// ── Apply motor direction ─────────────────────────────────
void setDirection(bool forward) {
  if (forward) {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
  } else {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
  }
}

// ── Soft ramp to target PWM ───────────────────────────────
void rampTo(int target) {
  if (currentPWM < target) currentPWM = min(currentPWM + 3, target);
  else if (currentPWM > target) currentPWM = max(currentPWM - 3, target);
  analogWrite(ENA_PIN, currentPWM);
}

// ── Brake motor (short both terminals) ───────────────────
void brakeMotor() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, 0);
  currentPWM = 0;
}

// ── Button debounce + direction toggle ────────────────────
void checkButton() {
  bool btnNow = digitalRead(BTN_PIN);
  if (lastBtnState == HIGH && btnNow == LOW) {
    delay(50); // debounce wait
    if (digitalRead(BTN_PIN) == LOW) {
      // Brief brake to protect motor during direction switch
      brakeMotor();
      delay(200);

      motorForward = !motorForward;
      setDirection(motorForward);
      Serial.print(F("Direction changed → "));
      Serial.println(motorForward ? F("FORWARD (CW)") : F("REVERSE (CCW)"));
    }
  }
  lastBtnState = btnNow;
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  brakeMotor();
  setDirection(true);

  Serial.println(F("=== DC Motor Speed & Direction Control ==="));
  Serial.println(F("Pot (A0) → Speed | Button (Pin 2) → Toggle Direction"));
  Serial.println(F("PWM soft-start ramping enabled."));
  Serial.println();
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  // ── Read potentiometer ────────────────────────────────────
  int potVal  = analogRead(POT_PIN);           // 0–1023
  int target  = map(potVal, 0, 1023, 0, 255);  // Scale to PWM

  // ── Dead-band: ignore very low speeds (< 10%) ─────────────
  if (target < 25) target = 0; // Below 10% → stop motor cleanly

  // ── Soft-ramp to target speed ─────────────────────────────
  rampTo(target);

  // ── Apply direction ───────────────────────────────────────
  if (target > 0) setDirection(motorForward);

  // ── Check direction button ────────────────────────────────
  checkButton();

  // ── Print status ──────────────────────────────────────────
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 300) {
    lastPrint = millis();
    int percent = (currentPWM * 100) / 255;
    Serial.print(F("Dir: "));
    Serial.print(motorForward ? F("FWD") : F("REV"));
    Serial.print(F(" | PWM: "));
    Serial.print(currentPWM);
    Serial.print(F("/255 ("));
    Serial.print(percent);
    Serial.print(F("%) | Pot: "));
    Serial.println(potVal);
  }

  delay(20);
}
