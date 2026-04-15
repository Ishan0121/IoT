# Experiment 10 — Interfacing Arduino with Cloud

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To send live sensor data (temperature, humidity, light level) from Arduino to the **ThingSpeak IoT cloud platform** over WiFi (via ESP8266 or ESP32), and visualise it as real-time graphs accessible from anywhere in the world.

---

## Theory

### The IoT Data Pipeline

```
Physical World
      │ (temperature rises)
      ▼
DHT11 Sensor
      │ (electrical signal)
      ▼
Arduino (reads and packages data)
      │ (serial command or WiFi)
      ▼
ESP8266 / ESP32 (WiFi module)
      │ (TCP/IP over WiFi → Internet)
      ▼
ThingSpeak API Server
      │ (stores in time-series database)
      ▼
ThingSpeak Web Dashboard
      │ (graphs, gauges, alerts)
      ▼
You (view from any browser, anywhere)
```

---

### ThingSpeak Platform

**ThingSpeak** (by MathWorks, makers of MATLAB) is a free cloud IoT platform that:
- Accepts data via HTTP REST API or MQTT
- Stores up to 8 fields per channel
- Visualises data as real-time charts
- Supports MATLAB analysis, alerts, and integrations

**Free Tier Limits:**
- 3 million messages per year
- Minimum 15-second gap between updates (rate limited)
- Up to 4 channels

**API Format:**
```
POST https://api.thingspeak.com/update
Body: api_key=XXXX&field1=23.5&field2=65&field3=750
Response: message ID (e.g. "42") on success, "0" on failure
```

---

### ESP8266 — The WiFi Module

The **ESP8266** is a low-cost WiFi microcontroller chip. In this experiment it is used in two ways:

#### Option A: As AT-Command Module (paired with Arduino UNO)
- Arduino sends text AT commands via serial
- ESP8266 handles WiFi and HTTP
- Needs a logic level converter (5V→3.3V) on RX line

#### Option B: ESP8266 as Standalone (Recommended!)
- Install ESP8266 board support in Arduino IDE
- Write code directly in Arduino IDE targeting ESP8266
- Upload directly to ESP8266 (no Arduino UNO needed)
- Connect DHT11 directly to ESP8266 GPIO pin

**ESP8266 in Arduino IDE:**
```
File → Preferences → Additional Board Manager URLs:
Add: http://arduino.esp8266.com/stable/package_esp8266com_index.json

Tools → Board → Boards Manager → search "esp8266" → Install
Tools → Board → ESP8266 Boards → NodeMCU 1.0 (or your module)
```

---

### MQTT vs HTTP for IoT

| Feature | HTTP (REST) | MQTT |
|---|---|---|
| Protocol | Request-Response | Publish-Subscribe |
| Overhead | High (headers) | Very low |
| Direction | One-way request | Bidirectional |
| Best for | Simple uploads | Real-time two-way |
| ThingSpeak | ✅ Supported | ✅ Supported |

This experiment uses **HTTP** (simpler for beginners).

---

## Components Required

| Component | Quantity | Notes |
|---|---|---|
| ESP8266 (NodeMCU / Wemos D1) | 1 | Standalone WiFi MCU |
| DHT11 Sensor | 1 | Temperature + Humidity |
| LDR + 10kΩ resistor | 1 | Light level (A0) |
| USB cable (Micro-USB) | 1 | For programming ESP8266 |
| WiFi Router | 1 | 2.4 GHz network |

---

## ThingSpeak Setup

```
Step 1: Create account at https://thingspeak.com (free)
Step 2: Click "New Channel"
Step 3: Set up fields:
  Field 1: Temperature (°C)
  Field 2: Humidity (%)
  Field 3: Light Level
  Field 4: Heat Index (optional)
Step 4: Save Channel
Step 5: Go to "API Keys" tab
Step 6: Copy your WRITE API KEY (looks like: XXXXXXXXXXXXXXXX)
Step 7: Note your Channel ID (number in the URL)
```

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments — WiFi connection, HTTP client, data upload |
| `program.ino` | Full working ESP8266 sketch uploading 3 sensor fields to ThingSpeak |

---

## Security Note

> ⚠️ **Never upload your WiFi password or API key to a public repository!**  
> In production, use environment variables or a config file. In this lab, keep these credentials private.

---

## Expected Output

- Serial Monitor shows WiFi connection status and each upload result
- ThingSpeak channel shows 3 live graphs updating every 15 seconds
- Accessible from any device with internet — phone, laptop, anywhere
