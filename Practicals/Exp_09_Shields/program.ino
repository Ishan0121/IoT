/*
 * ============================================================
 * Experiment 09 — Working with Shields (Ethernet W5100)
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Requires: Ethernet shield (W5100) stacked on Arduino UNO
 *           Ethernet cable connected to router
 *           DHT11 on Pin 3, LDR voltage divider on A0
 *
 * ⚠ RESERVED PINS (Ethernet Shield): 10, 11, 12, 13, 4
 *   Do NOT connect sensors to these pins.
 *
 * Features:
 *   - DHCP auto IP assignment
 *   - HTTP web server on port 80
 *   - Serves auto-refreshing HTML dashboard with sensor data
 *   - LED toggle via URL (/led=on / /led=off)
 * ============================================================
 */

#include <Ethernet.h>
#include <DHT.h>

// ── Ethernet MAC Address ───────────────────────────────────
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// ── Server on port 80 (HTTP) ───────────────────────────────
EthernetServer server(80);

// ── DHT11 Sensor ──────────────────────────────────────────
#define DHT_PIN  3
#define DHTTYPE  DHT11
DHT dht(DHT_PIN, DHTTYPE);

// ── Other Pins ────────────────────────────────────────────
const int LDR_PIN    = A0;
const int LED_PIN    = 7;   // Controllable via URL

// ── LED state ─────────────────────────────────────────────
bool ledState = false;

// ── Helper: send HTTP headers ─────────────────────────────
void sendHeaders(EthernetClient& client) {
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println(F("Connection: close"));
  client.println(); // Blank line — mandatory headers/body separator
}

// ── Helper: send HTML dashboard ───────────────────────────
void sendDashboard(EthernetClient& client, float temp, float hum, int ldr) {
  client.println(F("<!DOCTYPE html>"));
  client.println(F("<html lang='en'><head>"));
  client.println(F("<meta charset='UTF-8'>"));
  client.println(F("<meta http-equiv='refresh' content='10'>"));
  client.println(F("<title>Arduino Sensor Dashboard</title>"));
  client.println(F("<style>"));
  client.println(F("body{font-family:Arial,sans-serif;background:#1a1a2e;color:#eee;padding:30px;}"));
  client.println(F("h1{color:#00d4ff;} .card{background:#16213e;border-radius:12px;padding:20px;"));
  client.println(F("margin:12px 0;border-left:4px solid #00d4ff;}"));
  client.println(F(".val{font-size:2em;font-weight:bold;color:#00d4ff;}"));
  client.println(F("a.btn{display:inline-block;padding:10px 20px;border-radius:8px;"));
  client.println(F("text-decoration:none;margin:5px;font-weight:bold;}"));
  client.println(F(".on{background:#27ae60;color:#fff;} .off{background:#c0392b;color:#fff;}"));
  client.println(F("</style></head><body>"));

  client.println(F("<h1>&#x1F4E1; Arduino Sensor Dashboard</h1>"));

  // Temperature card
  client.println(F("<div class='card'>"));
  client.print(F("<p>&#x1F321; Temperature</p><p class='val'>"));
  if (isnan(temp)) client.print(F("--"));
  else client.print(temp, 1);
  client.println(F(" &deg;C</p></div>"));

  // Humidity card
  client.println(F("<div class='card'>"));
  client.print(F("<p>&#x1F4A7; Humidity</p><p class='val'>"));
  if (isnan(hum)) client.print(F("--"));
  else client.print(hum, 1);
  client.println(F(" %</p></div>"));

  // Light card
  client.println(F("<div class='card'>"));
  client.print(F("<p>&#x1F506; Light Level</p><p class='val'>"));
  client.print(ldr);
  client.println(F(" / 1023</p></div>"));

  // Uptime card
  client.println(F("<div class='card'>"));
  client.print(F("<p>&#x23F1; Uptime</p><p class='val'>"));
  client.print(millis() / 1000);
  client.println(F(" s</p></div>"));

  // LED control
  client.println(F("<div class='card'><p>&#x1F4A1; LED Control (Pin 7)</p>"));
  client.println(F("<a class='btn on' href='/led=on'>Turn ON</a>"));
  client.println(F("<a class='btn off' href='/led=off'>Turn OFF</a>"));
  client.print(F("<p>Current state: <strong>"));
  client.print(ledState ? F("ON") : F("OFF"));
  client.println(F("</strong></p></div>"));

  client.println(F("<p style='color:#888;font-size:0.8em;'>Auto-refreshes every 10 seconds</p>"));
  client.println(F("</body></html>"));
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println(F("=== Ethernet Shield Web Server ==="));
  Serial.print(F("Requesting DHCP address..."));

  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("\nDHCP FAILED! Check cable and router. Halting."));
    while (true) delay(1000);
  }

  delay(1000); // Allow link to stabilise

  Serial.println(F(" Done!"));
  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
  Serial.println(F("Open a browser on the same network and navigate to:"));
  Serial.print(F("http://"));
  Serial.println(Ethernet.localIP());

  server.begin();
  Serial.println(F("Server started on port 80. Waiting for clients..."));
}

// ── loop ──────────────────────────────────────────────────
void loop() {
  // Maintain DHCP lease (renew if needed)
  Ethernet.maintain();

  EthernetClient client = server.available();
  if (!client) return;

  Serial.println(F("\nClient connected."));

  // ── Read HTTP request ─────────────────────────────────────
  String request        = "";
  bool   headersDone    = false;
  bool   blankLine      = true;
  unsigned long timeout = millis() + 1000;

  while (client.connected() && millis() < timeout) {
    if (client.available()) {
      char c = client.read();
      if (!headersDone) request += c;
      if (c == '\n' && blankLine) { headersDone = true; break; }
      blankLine = (c == '\n') ? true : (c == '\r' ? blankLine : false);
    }
  }

  // ── Parse LED commands from URL ───────────────────────────
  if (request.indexOf("led=on") >= 0) {
    ledState = true;
    digitalWrite(LED_PIN, HIGH);
    Serial.println(F("LED → ON via web command"));
  } else if (request.indexOf("led=off") >= 0) {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println(F("LED → OFF via web command"));
  }

  // ── Read sensors ──────────────────────────────────────────
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int   ldr  = analogRead(LDR_PIN);

  Serial.print(F("Serving: Temp="));
  Serial.print(isnan(temp) ? 0 : temp, 1);
  Serial.print(F("°C Hum="));
  Serial.print(isnan(hum) ? 0 : hum, 1);
  Serial.print(F("% LDR="));
  Serial.println(ldr);

  // ── Send response ─────────────────────────────────────────
  sendHeaders(client);
  sendDashboard(client, temp, hum, ldr);

  // ── Close connection ──────────────────────────────────────
  delay(1);
  client.stop();
  Serial.println(F("Client disconnected."));
}
