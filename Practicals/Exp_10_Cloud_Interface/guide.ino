/*
 * ============================================================
 * Experiment 10 — Interfacing Arduino with Cloud (ThingSpeak)
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 *
 * Target Board: ESP8266 (NodeMCU or Wemos D1 Mini) — Standalone
 * (The ESP8266 runs this code directly — no Arduino UNO needed)
 *
 * Install ESP8266 support in Arduino IDE first:
 *   File → Preferences → Additional Boards Manager URLs:
 *   http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *   Tools → Board → Boards Manager → search "esp8266" → Install
 *   Tools → Board → ESP8266 Boards → NodeMCU 1.0
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Include Required Libraries
// ─────────────────────────────────────────────────────────────
// You need THREE libraries:
//
//   1. ESP8266WiFi.h — Built into ESP8266 board package
//      → Connects ESP8266 to WiFi network
//
//   2. ESP8266HTTPClient.h — Built into ESP8266 package
//      → Lets you make HTTP requests (like a browser does)
//
//   3. DHT.h — Install from Library Manager
//      → Reads temperature and humidity from DHT11
//
// YOUR TASK:
//   #include <ESP8266WiFi.h>
//   #include <ESP8266HTTPClient.h>
//   #include <DHT.h>


// ─────────────────────────────────────────────────────────────
// STEP 2: Define Your Secret Credentials
// ─────────────────────────────────────────────────────────────
// YOU MUST CHANGE THESE to your real values:
//
//   const char* WIFI_SSID    = "YourWiFiName";
//   const char* WIFI_PASS    = "YourWiFiPassword";
//   const char* API_KEY      = "YourThingSpeakWriteAPIKey";
//   const char* TS_HOST      = "api.thingspeak.com";
//
// How to get your API key:
//   1. Log in to thingspeak.com
//   2. Open your channel
//   3. Click "API Keys" tab
//   4. Copy the "Write API Key"
//
// SECURITY NOTE:
//   Never share or push these credentials to GitHub!
//   In professional code, store them in a separate config file.


// ─────────────────────────────────────────────────────────────
// STEP 3: Define Sensor Pins and DHT Object
// ─────────────────────────────────────────────────────────────
// On NodeMCU, GPIO pins are labeled D0–D8, NOT 0–8.
// Use the D-notation or the actual GPIO number:
//   D4 = GPIO4, D5 = GPIO5, etc.
//
// YOUR TASK:
//   const int DHT_PIN = D4;   // GPIO4 on NodeMCU
//   const int LDR_PIN = A0;   // NodeMCU has ONE analog pin (A0)
//   #define DHTTYPE DHT11
//   DHT dht(DHT_PIN, DHTTYPE);
//
// WiFiClient object (needed by HTTPClient):
//   WiFiClient client;


// ─────────────────────────────────────────────────────────────
// STEP 4: setup() — Connect to WiFi
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Serial.begin(115200)  ← ESP8266 uses 115200 baud
//
//   Task B: Initialize DHT
//   → dht.begin();
//
//   Task C: Connect to WiFi
//   → WiFi.begin(WIFI_SSID, WIFI_PASS);
//   → Serial.print("Connecting to WiFi");
//   → while (WiFi.status() != WL_CONNECTED) {
//       delay(500);
//       Serial.print(".");  ← print dots while connecting
//     }
//   → Serial.println(" Connected!");
//   → Serial.print("IP: "); Serial.println(WiFi.localIP());
//
//   Why check WL_CONNECTED in a loop?
//   WiFi connection takes 2–10 seconds.
//   We MUST wait before trying to send any data.
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: Create sendToThingSpeak() Function
// ─────────────────────────────────────────────────────────────
// void sendToThingSpeak(float temp, float hum, int light) {
//
//   Step A: Check WiFi is still connected
//   → if (WiFi.status() != WL_CONNECTED) {
//       Serial.println("WiFi lost! Reconnecting...");
//       WiFi.reconnect();
//       return;
//     }
//
//   Step B: Build the URL string
//   → String url = "http://api.thingspeak.com/update?api_key=";
//   → url += API_KEY;
//   → url += "&field1=" + String(temp);
//   → url += "&field2=" + String(hum);
//   → url += "&field3=" + String(light);
//   → url += "&field4=" + String(dht.computeHeatIndex(temp, hum, false));
//
//   What is URL structure?
//   http://server/path?key1=val1&key2=val2&key3=val3
//   → '?' marks start of parameters
//   → '&' separates parameters
//
//   Step C: Create HTTP client and send GET request
//   → HTTPClient http;
//   → http.begin(client, url);             ← set target URL
//   → int httpCode = http.GET();           ← send request
//
//   Step D: Check response
//   → if (httpCode == 200) {               ← 200 = success
//       String response = http.getString();  ← ThingSpeak returns message ID
//       Serial.print("Uploaded! Message ID: ");
//       Serial.println(response);
//     } else {
//       Serial.print("Upload failed. HTTP code: ");
//       Serial.println(httpCode);
//     }
//
//   → http.end();  ← ALWAYS close the connection after use
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 6: loop() Function
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Task A: Read sensors
//   → float temp = dht.readTemperature();
//   → float hum  = dht.readHumidity();
//   → int  light = analogRead(LDR_PIN);  ← 0 to 1023
//
//   Task B: Validate DHT reading
//   → if (isnan(temp) || isnan(hum)) {
//       Serial.println("Sensor error! Skipping upload.");
//       delay(5000);
//       return;
//     }
//
//   Task C: Print to Serial
//   → "Temp: X°C | Hum: Y% | Light: Z"
//
//   Task D: Upload to ThingSpeak
//   → sendToThingSpeak(temp, hum, light);
//
//   Task E: Wait 15 seconds minimum (ThingSpeak rate limit)
//   → delay(15000);
//   → Why 15s? Free ThingSpeak allows 1 update per 15 seconds.
//     Sending faster = message rejected (returns "0")
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: Verify on ThingSpeak Dashboard
// ─────────────────────────────────────────────────────────────
// After uploading the sketch and running:
//   1. Open Serial Monitor at 115200 baud
//   2. Watch for: "Connected! IP: 192.168.x.x"
//   3. Then: "Uploaded! Message ID: 1" (then 2, 3, 4...)
//   4. Open thingspeak.com → Your Channel → Private View
//   5. Watch 3 graphs update every 15 seconds!
//   6. Try: breathe on DHT11 (humidity rises)
//          cover LDR (light level drops)
//          warm DHT11 with finger (temperature rises)


// ─────────────────────────────────────────────────────────────
// CHALLENGE 1: Receive Data FROM Cloud
// ─────────────────────────────────────────────────────────────
// ThingSpeak can SEND data back to your device too.
// Write a field from the ThingSpeak web app (manually):
//   Field 5: LED_COMMAND (set to 1 or 0)
//
// Then in code, read it:
//   String readUrl = "http://api.thingspeak.com/channels/";
//   readUrl += CHANNEL_ID;
//   readUrl += "/fields/5/last.txt?api_key=" + READ_API_KEY;
//
//   http.begin(client, readUrl);
//   http.GET();
//   String val = http.getString();
//   if (val == "1") digitalWrite(LED_PIN, HIGH);
//   else            digitalWrite(LED_PIN, LOW);


// ─────────────────────────────────────────────────────────────
// CHALLENGE 2: ThingSpeak React Alert
// ─────────────────────────────────────────────────────────────
// Set up an alert ON ThingSpeak (no code needed):
//   1. ThingSpeak → Apps → React
//   2. Test Expression: field('field1') > 35
//   3. Action: ThingHTTP → Send email
//   4. Now: If temp > 35°C → you get an email automatically!
