# Experiment 07 — Smart Home Sensors with Arduino

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To integrate multiple smart home sensors (PIR motion detector, DHT11 temperature/humidity, LDR light sensor, MQ-2 gas sensor) with Arduino, and implement automatic responses — auto-lighting, temperature alerts, and gas emergency alarms.

---

## Theory

### Smart Home Concept

A smart home uses sensors to monitor the environment and actuators to respond automatically — **without human intervention**.

```
Environment Change
      ↓ (detected by sensor)
Microcontroller (Arduino)
      ↓ (processes logic)
Actuator responds
      ↓ (light on, fan on, alarm, etc.)
Feedback to user (Serial Monitor / App)
```

---

### Sensor Explanations

#### 1. PIR Motion Sensor (HC-SR501)

**PIR = Passive Infrared** — does NOT emit anything; it only detects IR radiation from warm objects (humans, animals).

```
Internal structure:
  Two pyroelectric elements side-by-side with a Fresnel lens
  When human moves across → one element sees MORE IR, other LESS
  Differential output → TRIGGER!
```

- **Output:** Digital HIGH when motion detected, LOW when clear
- **Adjustments (on the sensor board):**
  - **Sensitivity potentiometer** → how far away it detects (3–7m)
  - **Time-delay potentiometer** → how long output stays HIGH after motion
- **Warm-up time:** 30–60 seconds after power-on (ignore false triggers)

#### 2. DHT11 Temperature & Humidity Sensor

- Uses a single-wire digital protocol with a specific timing sequence
- Must NOT be read more than once every 2 seconds
- Requires the `DHT.h` library (Adafruit)

| Parameter | DHT11 | DHT22 |
|---|---|---|
| Temperature | 0–50°C ±2°C | -40–80°C ±0.5°C |
| Humidity | 20–90% ±5% | 0–100% ±2% |
| Sampling | 1 Hz (1 reading/sec) | 0.5 Hz |
| Cost | Cheap | Higher |

#### 3. LDR (Light Dependent Resistor)

- Resistance changes with light level:
  - **Dark room:** ~1 MΩ (very high resistance)
  - **Bright light:** ~1 kΩ (low resistance)
- Used in a **voltage divider** with a fixed resistor to produce analog voltage

```
Voltage Divider Circuit:
5V ─── [10kΩ fixed] ──── A0 ──── [LDR] ──── GND

In dark:  LDR has high R → Most voltage across LDR → A0 HIGH
In light: LDR has low R  → Most voltage across 10kΩ → A0 LOW
```

#### 4. MQ-2 Gas Sensor

- Uses a tin-oxide semiconductor heated by an internal coil
- Gas molecules react with semiconductor → resistance changes → analog voltage changes
- **Detects:** LPG, butane, propane, methane, alcohol, hydrogen, smoke
- **Warm-up time: 30 seconds minimum** after powering on (crucial!)
- Output: Both analog (A0) and digital (D0 with adjustable threshold)

---

## Components Required

| Component | Quantity | Purpose |
|---|---|---|
| Arduino UNO | 1 | Controller |
| PIR Sensor (HC-SR501) | 1 | Motion detection |
| DHT11 Sensor Module | 1 | Temp + Humidity |
| LDR + 10kΩ Resistor | 1 + 1 | Light sensing |
| MQ-2 Gas Sensor | 1 | Gas detection |
| Relay Module (5V) | 1 | Switching lamp/fan |
| Buzzer (active) | 1 | Gas alarm |
| Green LED | 1 | Light indicator |
| Red LED | 1 | Gas indicator |
| Resistors 220Ω | 2 | LED protection |
| Breadboard | 1 | — |
| Jumper Wires | 30+ | — |

---

## Circuit Description

```
PIR Sensor:
  VCC → 5V | GND → GND | OUT → Pin 2

DHT11 Module (3-pin):
  VCC → 5V | GND → GND | DATA → Pin 3

LDR Voltage Divider:
  5V → [10kΩ] → A0 → [LDR] → GND

MQ-2 Gas Sensor:
  VCC → 5V | GND → GND | A0 → A1
  (Wait 30 seconds after power-on for accurate readings!)

Relay Module:
  VCC → 5V | GND → GND | IN → Pin 7
  (Relay switches an external LED or appliance)

Buzzer → Pin 8 → GND
Green LED → Pin 9 → 220Ω → LED(+) → GND
Red LED   → Pin 10 → 220Ω → LED(+) → GND
```

---

## System Logic Table

| Sensor | Condition | Action |
|---|---|---|
| PIR | Motion detected | Turn relay ON (light/fan) |
| PIR | No motion for 10s | Turn relay OFF |
| DHT11 | Temp > 35°C | Print warning |
| DHT11 | Humidity > 80% | Print warning |
| LDR | Dark (value > threshold) | Turn on green LED |
| LDR | Bright (value < threshold) | Turn off green LED |
| MQ-2 | Gas level > threshold | Sound buzzer + red LED |

---

## Library Required

Install via Library Manager (`Ctrl + Shift + I`):
- **DHT sensor library** by Adafruit
- **Adafruit Unified Sensor** (dependency)

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments — DHT library, sensor fusion, alerts |
| `program.ino` | Full multi-sensor smart home system |
