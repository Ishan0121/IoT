# Experiment 09 — Working with Arduino Shields

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To understand what Arduino shields are, how they are physically stacked, and to use an **Ethernet Shield (W5100)** to create a simple web server that serves live sensor data to any browser on the local network.

---

## Theory

### What is a Shield?

An Arduino **shield** is a plug-in add-on board that sits directly on top of the Arduino, connecting to its headers. Shields expand the Arduino's capabilities without complex wiring.

```
      [Shield on Top]
   ┌──────────────────┐
   │   ETHERNET       │  ← Shield: adds wired internet
   │   SHIELD         │
   └────────┬─────────┘
            │ (pins pass through)
   ┌────────┴─────────┐
   │   ARDUINO UNO    │  ← Base board
   └──────────────────┘
```

### Stacking Principle

- Shields use **tall headers (stackable)** so pins pass through
- Multiple shields can be stacked — but they must not conflict on pins
- Each shield's documentation lists which pins it uses

---

### Common Arduino Shields

| Shield | Adds | Occupied Pins |
|---|---|---|
| **Ethernet (W5100/W5500)** | Wired internet (RJ45) | 10–13 (SPI) + 4 (SD CS) |
| **WiFi Shield** | Wireless internet | 4, 7, 10–13 |
| **Motor Shield (L293D)** | 2× DC motors, 1× stepper | 3,8,11,12 (channel A) |
| **GSM/GPRS Shield** | Cellular network | D2/D3 (software serial) |
| **SD Card Shield** | MicroSD storage | 10–13 (SPI) |
| **Relay Shield** | 4× relays for AC | 4,5,6,7 |
| **LCD Keypad Shield** | 16×2 LCD + 5 buttons | 4,5,6,7,8,A0 |
| **Prototype Shield** | Empty board to solder on | None (your choice) |

---

### Ethernet Shield (W5100) — Deep Dive

The W5100 chip implements the full TCP/IP stack in hardware, offloading network processing from the Arduino's CPU.

**Communication to Arduino:** SPI (Serial Peripheral Interface)

```
W5100 Chip
    │ SPI Bus
    ├── Pin 11 (MOSI) → Data from Arduino to W5100
    ├── Pin 12 (MISO) → Data from W5100 to Arduino
    ├── Pin 13 (SCK)  → Clock signal
    └── Pin 10 (SS)   → W5100 chip select (exclusive use)

Pin 4 → SD card chip select (if using onboard SD card)
```

**⚠ Pins 10–13 are RESERVED when Ethernet Shield is in use. Do NOT connect other components to these pins.**

---

### HTTP Protocol Basics

When you open a browser and type an IP address, your browser:

1. Sends an **HTTP GET request** to that IP
2. Arduino receives it via Ethernet Shield
3. Arduino sends back an **HTTP response** with HTML content
4. Browser renders the HTML page

```
Browser → GET / HTTP/1.1\r\n
          Host: 192.168.1.100\r\n
          \r\n                      ← blank line = end of headers

Arduino → HTTP/1.1 200 OK\r\n
          Content-Type: text/html\r\n
          \r\n                      ← blank line = end of headers
          <html><body>...</body></html>
```

---

## Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| Ethernet Shield (W5100) | 1 | Press firmly onto UNO headers |
| Ethernet cable (Cat5e) | 1 | RJ45 plug to router/switch |
| DHT11 Sensor | 1 | Data to Pin 3 (not 10–13!) |
| LDR + 10kΩ resistor | 1 | Wiper to A0 |
| Router/Switch | 1 | For local network |

---

## Network Configuration

The sketch uses **DHCP** — the router automatically assigns an IP address. After upload, open the Serial Monitor to see which IP was assigned, then type it in a browser.

```
Example:
  Serial Monitor shows: "Server at 192.168.1.105"
  Browser: http://192.168.1.105
  → You see the sensor dashboard!
```

---

## MAC Address

Every Ethernet device has a unique MAC address (hardware ID). The shield may have one printed on a sticker. If not, use any unique 6-byte value — ensure no other device on your network has the same one.

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments for Ethernet.h, HTTP server logic |
| `program.ino` | Full web server serving DHT11 + LDR data as auto-refreshing HTML page |

---

## Troubleshooting

| Issue | Likely Cause | Fix |
|---|---|---|
| "DHCP failed" | Cable not connected | Check cable and router |
| Browser "connection refused" | Wrong IP or server not started | Check Serial Monitor for correct IP |
| Garbled Serial output | Pins 10–13 used by other component | Remove all components from 10–13 |
| Shield not recognised | Not fully seated | Press down firmly on all pins |
