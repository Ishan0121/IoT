/*
 * ============================================================
 * Experiment 01 — Understanding Arduino UNO Board
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Demonstrates:
 *   - Serial communication and board info report
 *   - Digital output (built-in LED blink)
 *   - Analog input reading (floating pin observation)
 *   - millis() for non-blocking uptime tracking
 *   - EEPROM reset counter (challenge)
 * ============================================================
 */

#include <EEPROM.h>

// ── Constants ─────────────────────────────────────────────
const int LED_PIN    = 13;   // Built-in LED
const int BAUD_RATE  = 9600; // Serial communication speed

// ── Global Variables ───────────────────────────────────────
int          loopCounter  = 0;
unsigned long lastPrintMs = 0;  // Tracks last serial print time
bool         ledState     = false;
unsigned long lastBlinkMs = 0;
const int    BLINK_INTERVAL = 500; // ms

// ── Setup ──────────────────────────────────────────────────
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);

  // ── EEPROM Reset Counter ──────────────────────────────────
  int resetCount = EEPROM.read(0);
  if (resetCount == 255) resetCount = 0; // First boot: EEPROM is 0xFF
  resetCount++;
  EEPROM.write(0, resetCount);

  // ── Print Board Info Report ───────────────────────────────
  delay(200); // Give Serial Monitor time to open
  Serial.println(F("╔══════════════════════════════╗"));
  Serial.println(F("║   Arduino UNO Board Report   ║"));
  Serial.println(F("╚══════════════════════════════╝"));
  Serial.println(F("CPU      : ATmega328P @ 16 MHz"));
  Serial.println(F("Voltage  : 5V operating"));
  Serial.println(F("Digital  : 14 pins (D0–D13)"));
  Serial.println(F("PWM Pins : D3, D5, D6, D9, D10, D11"));
  Serial.println(F("Analog   : 6 pins (A0–A5), 10-bit ADC"));
  Serial.println(F("Flash    : 32 KB  |  SRAM : 2 KB  |  EEPROM : 1 KB"));
  Serial.print(F("Reset #  : "));
  Serial.println(resetCount);
  Serial.println(F("──────────────────────────────────"));
  Serial.println(F("Starting main loop..."));
  Serial.println();
}

// ── Main Loop ─────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // ── Non-blocking LED Blink ────────────────────────────────
  if (now - lastBlinkMs >= BLINK_INTERVAL) {
    lastBlinkMs = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  }

  // ── Print Status Every 1 Second ───────────────────────────
  if (now - lastPrintMs >= 1000) {
    lastPrintMs = now;
    loopCounter++;

    int a0 = analogRead(A0);
    int a1 = analogRead(A1);
    int a2 = analogRead(A2);

    unsigned long uptimeSec = now / 1000;

    Serial.print("Loop #");
    Serial.print(loopCounter);
    Serial.print(" | Uptime: ");
    Serial.print(uptimeSec);
    Serial.print("s | LED: ");
    Serial.print(ledState ? "ON " : "OFF");
    Serial.print(" | A0:");
    Serial.print(a0);
    Serial.print(" A1:");
    Serial.print(a1);
    Serial.print(" A2:");
    Serial.println(a2);
  }
}
