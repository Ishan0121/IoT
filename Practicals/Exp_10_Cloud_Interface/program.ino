/*
 * ============================================================
 * Experiment 10 — Interfacing Arduino with Cloud (ThingSpeak)
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Target Board : ESP8266 (NodeMCU 1.0 or Wemos D1 Mini)
 *
 * Install Board Support:
 *   File → Preferences → Additional Board Manager URLs:
 *   http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *   Tools → Boards Manager → search "esp8266" → Install
 *   Tools → Board → ESP8266 Boards → NodeMCU 1.0
 *
 * Required Libraries (Library Manager):
 *   - DHT sensor library (by Adafruit)
 *   - Adafruit Unified Sensor
 *
 * Circuit (NodeMCU):
 *   DHT11 DATA → D4 (GPIO2)
 *   LDR voltage divider → A0
 *
 * ✏ FILL IN your own WIFI_SSID, WIFI_PASS, and API_KEY before upload
 * ============================================================
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

// ── ✏ USER CONFIGURATION — CHANGE THESE ───────────────────
const char* WIFI_SSID  = "YOUR_WIFI_SSID";
const char* WIFI_PASS  = "YOUR_WIFI_PASSWORD";
const char* API_KEY    = "YOUR_THINGSPEAK_WRITE_API_KEY";
// ──────────────────────────────────────────────────────────

// ── ThingSpeak API endpoint ───────────────────────────────
const char* TS_URL = "http://api.thingspeak.com/update";

// ── Sensor Pins (NodeMCU GPIO) ────────────────────────────
#define DHT_PIN  D4    // GPIO2  — DHT11 data
#define LDR_PIN  A0    // Analog — LDR voltage divider
#define LED_PIN  D0    // GPIO16 — Onboard LED (active LOW on NodeMCU)

// ── DHT Setup ─────────────────────────────────────────────
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// ── WiFiClient instance ───────────────────────────────────
WiFiClient wifiClient;

// ── Upload interval: 15s minimum for ThingSpeak free tier ─
const unsigned long UPLOAD_INTERVAL = 15000UL;
unsigned long lastUpload = 0;
long          messageID  = 0;

// ── WiFi connection ───────────────────────────────────────
void connectWiFi() {
  Serial.print(F("Connecting to WiFi: "));
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(F("."));
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print(F("Connected! IP: "));
    Serial.println(WiFi.localIP());
    Serial.print(F("Signal strength (RSSI): "));
    Serial.print(WiFi.RSSI());
    Serial.println(F(" dBm"));
  } else {
    Serial.println(F("\nWiFi connection FAILED! Check credentials."));
    Serial.println(F("Restarting in 5 seconds..."));
    delay(5000);
    ESP.restart();
  }
}

// ── Upload data to ThingSpeak ─────────────────────────────
bool uploadToThingSpeak(float temp, float hum, int light, float heatIdx) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("WiFi lost — reconnecting..."));
    connectWiFi();
    return false;
  }

  // Build URL with all 4 field values
  String url  = String(TS_URL);
  url += "?api_key=" + String(API_KEY);
  url += "&field1=" + String(temp,  1);
  url += "&field2=" + String(hum,   1);
  url += "&field3=" + String(light);
  url += "&field4=" + String(heatIdx, 1);

  HTTPClient http;
  http.begin(wifiClient, url);
  http.setTimeout(10000); // 10 second timeout

  int httpCode = http.GET();
  bool success = false;

  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    response.trim();
    if (response != "0") {
      messageID++;
      Serial.print(F("✓ Upload OK — ThingSpeak msg #"));
      Serial.println(response);
      success = true;
    } else {
      Serial.println(F("✗ ThingSpeak returned 0 — rate limit or bad key"));
    }
  } else {
    Serial.print(F("✗ HTTP error: "));
    Serial.println(httpCode);
  }

  http.end();
  return success;
}

// ── format print ──────────────────────────────────────────
void printSensorData(float temp, float hum, int light, float heatIdx) {
  Serial.println(F("──────────────────────────────────────"));
  Serial.print(F("Temperature : ")); Serial.print(temp, 1); Serial.println(F(" °C"));
  Serial.print(F("Humidity    : ")); Serial.print(hum,  1); Serial.println(F(" %"));
  Serial.print(F("Light Level : ")); Serial.println(light);
  Serial.print(F("Heat Index  : ")); Serial.print(heatIdx, 1); Serial.println(F(" °C"));
  Serial.print(F("Uptime      : ")); Serial.print(millis() / 1000); Serial.println(F(" s"));
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);  // ESP8266 uses 115200 baud
  delay(200);

  Serial.println();
  Serial.println(F("╔══════════════════════════════════════╗"));
  Serial.println(F("║  Arduino → ThingSpeak Cloud Logger   ║"));
  Serial.println(F("╚══════════════════════════════════════╝"));

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // NodeMCU LED is active LOW — HIGH = off

  dht.begin();
  connectWiFi();

  Serial.println(F("System ready. Uploading every 15 seconds."));
  Serial.println(F("Visit https://thingspeak.com to view your data!"));
  Serial.println();
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  if (now - lastUpload >= UPLOAD_INTERVAL) {
    lastUpload = now;

    // ── Read sensors ────────────────────────────────────────
    float temp    = dht.readTemperature();
    float hum     = dht.readHumidity();
    int   light   = analogRead(LDR_PIN);

    // ── Validate DHT ────────────────────────────────────────
    if (isnan(temp) || isnan(hum)) {
      Serial.println(F("⚠ DHT read error — skipping this upload cycle."));
      return;
    }

    float heatIdx = dht.computeHeatIndex(temp, hum, false);

    // ── Print locally ────────────────────────────────────────
    printSensorData(temp, hum, light, heatIdx);

    // ── LED blink = upload indicator ─────────────────────────
    digitalWrite(LED_PIN, LOW);  // ON
    delay(100);
    digitalWrite(LED_PIN, HIGH); // OFF

    // ── Upload ───────────────────────────────────────────────
    bool ok = uploadToThingSpeak(temp, hum, light, heatIdx);
    if (!ok) {
      Serial.println(F("Retrying upload in next cycle..."));
    }
  }

  // ── Yield to ESP8266 WiFi stack (important!) ─────────────
  yield();
}
