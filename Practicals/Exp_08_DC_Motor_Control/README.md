# Experiment 08 — DC Motor Speed and Direction Control

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To control a DC motor's **rotational speed** using PWM and its **spin direction** using the L298N H-Bridge motor driver, with a potentiometer for speed selection and a pushbutton for direction toggling.

---

## Theory

### Why Can't Arduino Drive a DC Motor Directly?

| Parameter | Arduino Pin | DC Motor |
|---|---|---|
| Max Output Current | 40 mA | 200–1000 mA |
| Voltage | 5V | 5–12V |

Connecting a DC motor directly to an Arduino pin = **fried pin, possibly fried Arduino**.  
Always use a **motor driver IC** between Arduino and motor.

---

### H-Bridge Concept

An **H-Bridge** is a circuit of 4 switches arranged in an H shape. By toggling pairs of switches, current is directed through the motor in either direction.

```
         +12V
          │
    ┌─────┴─────┐
   [S1]       [S2]
    │           │
    ├── Motor ──┤
    │           │
   [S3]       [S4]
    │           │
    └─────┬─────┘
         GND

Forward (CW):   S1 + S4 closed → Current → Left to Right
Reverse (CCW):  S2 + S3 closed → Current → Right to Left
Brake:          S1 + S3 or S2 + S4 → Both motor terminals same potential
```

---

### L298N Motor Driver Module

The L298N contains **two full H-bridges** (can drive 2 DC motors or 1 stepper).

**Key Pins for one motor channel:**

| L298N Pin | Function | Connect To |
|---|---|---|
| IN1 | Direction control bit 1 | Arduino digital pin |
| IN2 | Direction control bit 2 | Arduino digital pin |
| ENA | Enable / Speed (PWM) | Arduino PWM pin |
| OUT1, OUT2 | Motor terminals | DC Motor |
| 12V | Motor power supply | External 9–12V |
| GND | Common ground | Arduino GND + Supply GND |
| 5V | Logic power | Arduino 5V (if jumper present) |

**Direction Truth Table:**

| IN1 | IN2 | Motor State |
|---|---|---|
| HIGH | LOW | Forward (CW) |
| LOW | HIGH | Reverse (CCW) |
| HIGH | HIGH | Brake (stop) |
| LOW | LOW | Coast (free spin) |

**Speed Control with PWM:**

```
analogWrite(ENA, 0)   → Motor stopped (0% duty)
analogWrite(ENA, 128) → Half speed    (50% duty)
analogWrite(ENA, 255) → Full speed    (100% duty)
```

---

### What is PWM?

PWM (Pulse Width Modulation) rapidly switches a pin ON and OFF. The **duty cycle** (percentage of time ON vs total period) controls average power:

```
100% duty cycle: ███████████████ 5V constant → Full speed
 50% duty cycle: ████░░░░████░░░ 2.5V avg   → Half speed
 25% duty cycle: ██░░░░░░██░░░░░ 1.25V avg  → Quarter speed
  0% duty cycle: ░░░░░░░░░░░░░░░ 0V          → No motion
```

---

### Button Debouncing

When a physical button is pressed, the contacts mechanically bounce — producing 5–20 false presses in a few milliseconds. **Debouncing** filters this out.

Software debounce: Read button, detect edge (HIGH→LOW), wait 50ms, confirm again.

---

## Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| DC Motor | 1 | 5–12V rated |
| L298N Motor Driver | 1 | Dual H-bridge module |
| Potentiometer 10kΩ | 1 | Speed control |
| Pushbutton | 1 | Direction toggle |
| External Supply | 1 | 9–12V / 1A for motor |
| Capacitor 100µF | 1 | Noise suppression across motor |
| Jumper Wires | 15+ | — |

---

## Circuit Description

```
L298N Module:
  IN1 → Arduino Pin 5
  IN2 → Arduino Pin 6
  ENA → Arduino Pin 9 (PWM ~)
  OUT1, OUT2 → DC Motor terminals
  12V pin → External 9–12V supply (+)
  GND     → External supply (−) AND Arduino GND (MUST link!)

Potentiometer (speed control):
  Left pin  → 5V
  Middle pin (wiper) → A0
  Right pin → GND

Direction button:
  One leg → Pin 2 | Other leg → GND
  Mode    → INPUT_PULLUP (no external resistor needed)

⚠ CRITICAL: Always link L298N GND to Arduino GND.
  Without this, direction signals from Arduino have no reference.

⚠ Add 100µF capacitor across motor terminals to
  suppress interference from motor switching.
```

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments — H-bridge logic, PWM, debounce |
| `program.ino` | Full working speed + direction control with Serial monitoring |
