/*
 * ============================================================
 * Experiment 07 — Smart Home Multi-Sensor System
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Requires: "DHT sensor library" by Adafruit (Library Manager)
 *
 * Circuit:
 *   PIR      → Pin 2   (motion detection)
 *   DHT11    → Pin 3   (temperature + humidity)
 *   LDR      → A0      (voltage divider with 10kΩ to 5V)
 *   MQ-2     → A1      (gas — warm up 30s!)
 *   Relay    → Pin 7   (auto lamp control)
 *   Buzzer   → Pin 8   (gas alarm)
 *   LightLED → Pin 9   (auto-light indicator)
 *   GasLED   → Pin 10  (gas alert)
 * ============================================================
 */

#include <DHT.h>

// ── Pin Constants ─────────────────────────────────────────
const int PIR_PIN    = 2;
const int DHT_PIN    = 3;
const int LDR_PIN    = A0;
const int GAS_PIN    = A1;
const int RELAY_PIN  = 7;
const int BUZZ_PIN   = 8;
const int LIGHT_LED  = 9;
const int GAS_LED    = 10;

// ── Thresholds ────────────────────────────────────────────
const int   DARK_THRESHOLD  = 600;
const int   GAS_THRESHOLD   = 400;
const float HOT_TEMP        = 35.0;
const float HIGH_HUM        = 80.0;
const unsigned long NO_MOTION_MS = 10000UL;

// ── DHT Setup ─────────────────────────────────────────────
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// ── Timing ────────────────────────────────────────────────
unsigned long lastMotionTime = 0;
unsigned long lastDHTTime    = 0;
unsigned long lastPrintTime  = 0;
bool          relayState     = false;

// ── Motion Check ──────────────────────────────────────────
void checkMotion() {
  bool motion = digitalRead(PIR_PIN);
  if (motion) {
    lastMotionTime = millis();
    if (!relayState) {
      relayState = true;
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println(F("[PIR] Motion detected  → Relay ON"));
    }
  } else {
    if (relayState && (millis() - lastMotionTime > NO_MOTION_MS)) {
      relayState = false;
      digitalWrite(RELAY_PIN, LOW);
      Serial.println(F("[PIR] No motion 10s    → Relay OFF"));
    }
  }
}

// ── Climate Read ──────────────────────────────────────────
void readClimate() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println(F("[DHT] Read error — check wiring"));
    return;
  }

  Serial.print(F("[DHT] Temp: "));
  Serial.print(temp, 1);
  Serial.print(F("°C  Hum: "));
  Serial.print(hum, 1);
  Serial.print(F("%"));

  if (temp > HOT_TEMP)   Serial.print(F("  ⚠TEMP HIGH"));
  if (hum  > HIGH_HUM)   Serial.print(F("  ⚠HUMID HIGH"));
  Serial.println();
}

// ── Light Check ───────────────────────────────────────────
void checkLight() {
  int ldrVal = analogRead(LDR_PIN);
  bool isDark = (ldrVal > DARK_THRESHOLD);
  digitalWrite(LIGHT_LED, isDark ? HIGH : LOW);

  Serial.print(F("[LDR] Value: "));
  Serial.print(ldrVal);
  Serial.println(isDark ? F("  → DARK  (LED ON)") : F("  → BRIGHT (LED OFF)"));
}

// ── Gas Check ─────────────────────────────────────────────
void checkGas() {
  int gasVal = analogRead(GAS_PIN);
  bool danger = (gasVal > GAS_THRESHOLD);

  digitalWrite(GAS_LED,  danger ? HIGH : LOW);
  digitalWrite(BUZZ_PIN, danger ? HIGH : LOW);

  Serial.print(F("[GAS] Level: "));
  Serial.print(gasVal);
  Serial.println(danger ? F("  ⚠ DANGER — ALARM ON!") : F("  → Safe"));
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN,   INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZ_PIN,  OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(GAS_LED,   OUTPUT);

  dht.begin();

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZ_PIN,  LOW);
  digitalWrite(LIGHT_LED, LOW);
  digitalWrite(GAS_LED,   LOW);

  Serial.println(F("=== Smart Home System Initializing ==="));
  Serial.println(F("Warming up MQ-2 gas sensor (30 seconds)..."));
  for (int i = 30; i > 0; i--) {
    Serial.print(i); Serial.print(F("... "));
    delay(1000);
  }
  Serial.println();
  Serial.println(F("System Ready! Monitoring started."));
  Serial.println(F("Dark threshold: 600 | Gas threshold: 400 | Hot: 35°C"));
  Serial.println();
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // Motion: check every 100ms
  checkMotion();

  // Climate: check every 2 seconds (DHT minimum)
  if (now - lastDHTTime > 2000) {
    lastDHTTime = now;
    readClimate();
  }

  // Light + Gas: check every loop (fast analog reads)
  checkLight();
  checkGas();

  // Print divider every 5 seconds
  if (now - lastPrintTime > 5000) {
    lastPrintTime = now;
    Serial.println(F("─────────────────────────────────────────"));
  }

  delay(100);
}
