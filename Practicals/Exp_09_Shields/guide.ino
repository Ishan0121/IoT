/*
 * ============================================================
 * Experiment 09 — Working with Arduino Shields (Ethernet)
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Understand Which Pins the Shield Uses
// ─────────────────────────────────────────────────────────────
// BEFORE writing a single line of code, know the constraints:
//
// Ethernet Shield (W5100) OCCUPIES:
//   Pin 10 → Ethernet Chip Select (SPI SS)
//   Pin 11 → SPI MOSI
//   Pin 12 → SPI MISO
//   Pin 13 → SPI SCK
//   Pin 4  → SD Card Chip Select (if SD feature used)
//
// RULE: NEVER connect any of your sensors to pins 10, 11, 12, 13.
// If you do, the Ethernet will malfunction and vice versa.
//
// Safe pins for YOUR use: 2, 3, 5, 6, 7, 8, 9, A0–A5
//
// YOUR TASK: Before wiring anything, circle 10,11,12,13 as
// "RESERVED — Ethernet only" in your lab notebook.


// ─────────────────────────────────────────────────────────────
// STEP 2: Include the Ethernet Library
// ─────────────────────────────────────────────────────────────
// The Ethernet.h library is BUILT INTO Arduino IDE.
// No installation needed — just include it.
//
// YOUR TASK:
//   #include <Ethernet.h>
//
// This gives you access to:
//   - Ethernet.begin() → connect to network
//   - EthernetServer   → create a server
//   - EthernetClient   → handle client connections


// ─────────────────────────────────────────────────────────────
// STEP 3: Define the MAC Address
// ─────────────────────────────────────────────────────────────
// Every network device needs a unique MAC address.
// Check if your shield has a sticker on the bottom with a MAC.
// If not, define one manually — just ensure it's unique on your network.
//
// YOUR TASK:
//   byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//
// This is written as 6 hexadecimal bytes (0x00 to 0xFF each).
// The first byte (0xDE) should have its second-least bit = 1
// to mark it as a "locally administered" address (standard practice).
//
// THINK ABOUT:
//   Why does a network need unique MAC addresses?
//   What happens if two devices share the same MAC?
//   (Answer: Packet collisions, network chaos)


// ─────────────────────────────────────────────────────────────
// STEP 4: Create the EthernetServer
// ─────────────────────────────────────────────────────────────
// A "server" listens on a port number and accepts connections.
// Port 80 is the standard HTTP port (what browsers use by default).
//
// YOUR TASK (declare GLOBALLY, outside any function):
//   EthernetServer server(80);
//
// This creates a server object that listens on port 80.
// Later you will call: server.begin(); to activate it.
//
// WHY port 80? When you type http://192.168.1.x in a browser
// without specifying a port, it defaults to port 80.


// ─────────────────────────────────────────────────────────────
// STEP 5: setup() Function — Connect to Network
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Serial.begin(9600) for debugging
//
//   Task B: Start Ethernet with DHCP
//   → if (Ethernet.begin(mac) == 0) {
//       Serial.println("DHCP failed! Check cable and router.");
//       while (true); ← halt if network not available
//     }
//
//   Why might DHCP fail?
//   → No ethernet cable connected
//   → Router not assigning addresses (rare)
//   → Shield not properly seated on Arduino
//
//   Task C: Wait 1 second for link to stabilise
//   → delay(1000);
//
//   Task D: Print the assigned IP address
//   → Serial.print("Server at: ");
//   → Serial.println(Ethernet.localIP());
//   ← Write this IP down! You will type it into your browser.
//
//   Task E: Start the server
//   → server.begin();
//   → Serial.println("Listening on port 80...");
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 6: loop() — Handle Incoming Client Requests
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Step A: Check for a waiting client
//   → EthernetClient client = server.available();
//   → if (!client) return; ← no client, do nothing
//
//   Step B: Read and DISCARD the HTTP request
//   The browser sends headers we don't need to parse for now.
//   We just need to detect the blank line that marks header end.
//
//   → boolean currentLineIsBlank = true;
//   → while (client.connected()) {
//       if (client.available()) {
//         char c = client.read();
//         if (c == '\n' && currentLineIsBlank) break; ← headers done
//         if (c == '\n') currentLineIsBlank = true;
//         else if (c != '\r') currentLineIsBlank = false;
//       }
//     }
//
//   Step C: Send HTTP response headers
//   → client.println("HTTP/1.1 200 OK");
//   → client.println("Content-Type: text/html");
//   → client.println("Connection: close");
//   → client.println(); ← CRITICAL blank line separates headers from body
//
//   Step D: Send HTML body
//   Build an HTML page showing sensor readings.
//   Read sensors BEFORE sending (DHT11 on Pin 3, LDR on A0).
//
//   → client.println("<!DOCTYPE html><html>");
//   → client.println("<head><title>Arduino Sensor Dashboard</title>");
//   → client.println("<meta http-equiv='refresh' content='10'>"); ← auto-refresh
//   → client.println("</head><body>");
//   → client.println("<h1>Arduino Sensor Dashboard</h1>");
//   → client.print("<p>Temperature: "); client.print(temp); client.println(" C</p>");
//   → client.print("<p>Humidity: "); client.print(hum); client.println(" %</p>");
//   → client.print("<p>Light Level: "); client.print(ldrVal); client.println("</p>");
//   → client.print("<p>Uptime: "); client.print(millis()/1000); client.println(" s</p>");
//   → client.println("</body></html>");
//
//   Step E: Close the connection
//   → delay(1);         ← let data transmit
//   → client.stop();    ← disconnect client
//   → Serial.println("Client served and disconnected.");
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: Testing Your Web Server
// ─────────────────────────────────────────────────────────────
// After uploading:
//   1. Open Serial Monitor
//   2. Note the IP address printed (e.g. 192.168.1.105)
//   3. Open a browser on the SAME network as Arduino
//   4. Type: http://192.168.1.105 → press Enter
//   5. You should see the sensor dashboard!
//   6. Page auto-refreshes every 10 seconds with new readings
//
// THINK ABOUT:
//   What is the difference between client.print() and Serial.print()?
//   → Serial goes to your computer's terminal
//   → client goes to the browser over the network
//
//   What does the <meta refresh> tag do?
//   → Tells the browser to reload the page automatically


// ─────────────────────────────────────────────────────────────
// CHALLENGE: LED Control via URL
// ─────────────────────────────────────────────────────────────
// When the user visits http://[IP]/led=on  → Turn LED on Pin 7 ON
// When the user visits http://[IP]/led=off → Turn LED off
//
// To do this, DON'T discard the HTTP request — read it:
//   → String request = "";
//   → while (client.available()) request += (char)client.read();
//
// Then check:
//   → if (request.indexOf("led=on") != -1)  digitalWrite(LED, HIGH);
//   → if (request.indexOf("led=off") != -1) digitalWrite(LED, LOW);
//
// Add two links to your HTML page:
//   <a href="/led=on">Turn LED ON</a>
//   <a href="/led=off">Turn LED OFF</a>
