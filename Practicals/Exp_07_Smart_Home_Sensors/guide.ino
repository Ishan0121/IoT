/*
 * ============================================================
 * Experiment 07 — Smart Home Sensors with Arduino
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Include Required Library
// ─────────────────────────────────────────────────────────────
// The DHT11 sensor uses a custom timing protocol.
// We use Adafruit's library — install it first!
//
// In Arduino IDE: Tools → Manage Libraries
// Search: "DHT sensor library" by Adafruit → Install
// Also install: "Adafruit Unified Sensor" (required dependency)
//
// YOUR TASK:
//   #include <DHT.h>
//
// Then define which type of sensor you have:
//   #define DHTTYPE DHT11
//
// Then create the DHT object:
//   DHT dht(DHT_PIN, DHTTYPE);
// This object will be used to read temperature and humidity.


// ─────────────────────────────────────────────────────────────
// STEP 2: Define All Pin Numbers and Thresholds
// ─────────────────────────────────────────────────────────────
// YOUR TASK: Define constants for:
//
//   const int PIR_PIN     = 2;   // Motion sensor output
//   const int DHT_PIN     = 3;   // DHT11 data pin
//   const int LDR_PIN     = A0;  // Analog light reading
//   const int GAS_PIN     = A1;  // Analog gas reading
//   const int RELAY_PIN   = 7;   // Controls lamp/fan via relay
//   const int BUZZER_PIN  = 8;   // Gas emergency alarm
//   const int LIGHT_LED   = 9;   // Auto-light indicator
//   const int GAS_LED     = 10;  // Gas alert indicator
//
// Define thresholds:
//   const int DARK_THRESHOLD = 600; // LDR above this = dark room
//   const int GAS_THRESHOLD  = 400; // MQ-2 above this = danger
//   const float HOT_TEMP     = 35.0; // Celsius
//   const float HIGH_HUMIDITY = 80.0; // Percent


// ─────────────────────────────────────────────────────────────
// STEP 3: setup() Function
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Serial.begin(9600)
//
//   Task B: Set pin modes
//   → PIR_PIN:    INPUT   (we READ from PIR)
//   → DHT_PIN:    handled by library, no pinMode needed
//   → RELAY_PIN:  OUTPUT
//   → BUZZER_PIN: OUTPUT
//   → LIGHT_LED:  OUTPUT
//   → GAS_LED:    OUTPUT
//
//   Task C: Initialize the DHT sensor
//   → dht.begin();
//
//   Task D: Print system banner
//   → "Smart Home System Initializing..."
//   → "Warming up sensors (30s)..."
//   → delay(30000);  ← MQ-2 MUST warm up 30 seconds!
//   → "System Ready."
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 4: Create checkMotion() Helper
// ─────────────────────────────────────────────────────────────
// The PIR sensor outputs HIGH when motion is detected.
// We want lights ON during motion and OFF 10 seconds after.
//
// void checkMotion() {
//
//   Read: bool motionDetected = digitalRead(PIR_PIN);
//
//   if (motionDetected) {
//     → Turn relay ON: digitalWrite(RELAY_PIN, HIGH)
//     → Save current time: lastMotionTime = millis();
//     → Print: "Motion detected — light ON"
//   }
//
//   // Auto-off after no motion for 10 seconds:
//   if (millis() - lastMotionTime > 10000 && !motionDetected) {
//     → Turn relay OFF
//     → Print: "No motion — light OFF"
//   }
//
// }
//
// Note: lastMotionTime must be declared OUTSIDE this function
// as a global variable (unsigned long lastMotionTime = 0;)


// ─────────────────────────────────────────────────────────────
// STEP 5: Create readClimate() Helper
// ─────────────────────────────────────────────────────────────
// void readClimate() {
//
//   Step A: Read from DHT sensor
//   → float temp = dht.readTemperature();
//   → float hum  = dht.readHumidity();
//
//   Step B: Always validate DHT readings!
//   → if (isnan(temp) || isnan(hum)) {
//       Serial.println("DHT read error!");
//       return;   ← skip this reading
//     }
//   Why isnan()? The library returns NaN (Not a Number) on error.
//
//   Step C: Print the readings
//   → Serial.print("Temp: "); Serial.print(temp); Serial.print("°C  ");
//   → Serial.print("Hum: "); Serial.print(hum); Serial.println("%");
//
//   Step D: Check thresholds
//   → if (temp > HOT_TEMP)     Serial.println("  ⚠ Temperature HIGH!");
//   → if (hum  > HIGH_HUMIDITY) Serial.println("  ⚠ Humidity HIGH!");
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 6: Create checkLight() Helper
// ─────────────────────────────────────────────────────────────
// void checkLight() {
//   int ldrVal = analogRead(LDR_PIN);  ← 0 to 1023
//
//   // High value = dark room (LDR has high resistance)
//   if (ldrVal > DARK_THRESHOLD) {
//     → Turn LIGHT_LED ON
//     → Print: "Dark room — auto light ON | LDR: X"
//   } else {
//     → Turn LIGHT_LED OFF
//     → Print: "Bright room — light OFF | LDR: X"
//   }
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: Create checkGas() Helper
// ─────────────────────────────────────────────────────────────
// void checkGas() {
//   int gasVal = analogRead(GAS_PIN);  ← 0 to 1023
//
//   if (gasVal > GAS_THRESHOLD) {
//     → digitalWrite(GAS_LED, HIGH);   // Red LED ON
//     → digitalWrite(BUZZER_PIN, HIGH); // Alarm!
//     → Print: "⚠ GAS DETECTED! Level: X"
//   } else {
//     → digitalWrite(GAS_LED, LOW);
//     → digitalWrite(BUZZER_PIN, LOW);
//     → Print: "Gas: OK | Level: X"
//   }
// }


// ─────────────────────────────────────────────────────────────
// STEP 8: loop() — Call All Helpers
// ─────────────────────────────────────────────────────────────
// void loop() {
//   Serial.println("─────────────────────");
//   checkMotion();
//   readClimate();    ← DHT only reads correctly once per 2s
//   checkLight();
//   checkGas();
//   delay(2000);     ← 2 second loop (DHT minimum interval)
// }


// ─────────────────────────────────────────────────────────────
// CHALLENGE: Non-blocking with millis()
// ─────────────────────────────────────────────────────────────
// Currently the 2s delay blocks everything.
// Try: call checkMotion() every 100ms, but readClimate() only every 2s.
//
// Use two separate unsigned long timers:
//   unsigned long lastMotionCheck = 0;
//   unsigned long lastDHTRead = 0;
//
// In loop():
//   if (millis() - lastMotionCheck > 100) { checkMotion(); lastMotionCheck = millis(); }
//   if (millis() - lastDHTRead >    2000) { readClimate(); lastDHTRead = millis(); }
//   checkLight();  // Can run every loop (analog read is fast)
//   checkGas();    // Can run every loop
