# Experiment 05 — Ultrasonic Sensor Handling with Arduino

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To measure distance using the **HC-SR04 ultrasonic sensor** with Arduino, display readings on the Serial Monitor, and trigger proximity alerts (LED + buzzer) when an object is detected within a defined threshold.

---

## Theory

### How Ultrasonic Distance Sensing Works

Sound travels through air at approximately **343 m/s** (at 20°C).  
The HC-SR04 works by emitting an ultrasonic pulse at **40 kHz** and measuring how long it takes for the echo to return.

```
Step 1: Arduino sends a 10µs HIGH pulse to TRIG pin
         ↓
Step 2: Sensor emits 8 ultrasonic pulses at 40 kHz
         ↓
Step 3: Pulses travel through air at 343 m/s
         ↓
Step 4: Pulses hit an object and bounce back
         ↓
Step 5: ECHO pin goes HIGH — stays HIGH for echo travel time
         ↓
Step 6: Arduino measures ECHO HIGH duration using pulseIn()
         ↓
Step 7: Calculate distance using physics formula
```

### Distance Formula

```
Time measured includes BOTH directions (to object + back):

Distance = (echo_duration_µs × speed_of_sound) / 2

Speed of sound = 0.0343 cm/µs

Distance (cm) = (echo_time × 0.0343) / 2
```

**Example:** Echo time = 1000 µs  
Distance = (1000 × 0.0343) / 2 = **17.15 cm**

---

## HC-SR04 Sensor Specifications

| Parameter | Value |
|---|---|
| Operating Voltage | 5V DC |
| Quiescent Current | <2 mA |
| Working Frequency | 40 kHz |
| Measuring Range | 2 cm – 400 cm |
| Accuracy | ±3 mm |
| Measuring Angle | 15° |
| Trigger Input Signal | 10 µs TTL pulse |
| Echo Output Signal | TTL pulse (proportional to distance) |

---

## HC-SR04 Pin Description

```
HC-SR04 (Front View)
┌─────────────────────┐
│  [O]           [O]  │   ← Ultrasonic emitter / receiver
│                     │
│  VCC TRIG ECHO GND  │
│   │    │    │    │  │
└───┼────┼────┼────┼──┘
    │    │    │    │
   5V  Out  In  GND
        ↑    ↑
   Arduino sends   Arduino receives
   trigger pulse   echo pulse
```

---

## Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| HC-SR04 Ultrasonic Sensor | 1 | — |
| Red LED | 1 | Danger zone indicator |
| Yellow LED | 1 | Caution zone indicator |
| Green LED | 1 | Safe zone indicator |
| Buzzer (active) | 1 | Proximity alarm |
| Resistors 220Ω | 3 | One per LED |
| Breadboard | 1 | — |
| Jumper Wires | 12 | — |

---

## Circuit Description

```
HC-SR04 Connections:
  VCC  → Arduino 5V
  GND  → Arduino GND
  TRIG → Arduino Pin 9  (Arduino sends trigger)
  ECHO → Arduino Pin 10 (Arduino reads echo)

Alert LEDs:
  Green  LED: Pin 4 → 220Ω → LED(+) → LED(−) → GND  [SAFE zone]
  Yellow LED: Pin 5 → 220Ω → LED(+) → LED(−) → GND  [CAUTION zone]
  Red    LED: Pin 6 → 220Ω → LED(+) → LED(−) → GND  [DANGER zone]

Buzzer:
  Pin 7 → Buzzer(+) → Buzzer(−) → GND
```

---

## Distance Zones

| Zone | Range | LED | Buzzer |
|---|---|---|---|
| **SAFE** | > 40 cm | Green ON | OFF |
| **CAUTION** | 20–40 cm | Yellow ON | Slow beep |
| **DANGER** | < 20 cm | Red ON + Blink | Rapid beep |

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments — `pulseIn()`, distance formula, zones |
| `program.ino` | Full working distance measurement with 3-zone alert system |

---

## `pulseIn()` Function Explained

```cpp
long duration = pulseIn(ECHO_PIN, HIGH);
```

- Waits for the ECHO pin to go HIGH
- Measures how long it stays HIGH (in microseconds)
- Has a default timeout of 1 second
- Returns 0 if no echo received within timeout

---

## Common Issues

| Problem | Cause | Fix |
|---|---|---|
| Always reads 0 | No echo received / timeout | Check wiring; object too close (<2cm) |
| Readings jump wildly | Electrical noise | Add 100µF cap on VCC; average readings |
| Always reads max (400cm) | ECHO wire disconnected | Verify ECHO connection |
| Reads negative distance | Formula error | Check you divide by 2 |
