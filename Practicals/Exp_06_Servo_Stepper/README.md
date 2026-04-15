# Experiment 06 — Servo Motor and Stepper Motor Handling with Arduino

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To understand and control two types of precision electromechanical actuators:
- **Servo Motor (SG90):** Rotate to a precise angle (0°–180°)
- **Stepper Motor (28BYJ-48):** Rotate by precise step counts via ULN2003 driver

---

## Theory

### Part A — Servo Motor

A **servo motor** is a rotary actuator that allows for **accurate control of angular position**. It contains:
1. A DC motor (for power)
2. A gearbox (for torque)
3. A position feedback sensor (potentiometer)
4. A control circuit (compares target vs actual)

**Control Signal:** PWM (Pulse Width Modulation) at 50 Hz (20ms period)

```
Pulse Width → Angle:
  1.0 ms pulse → 0°
  1.5 ms pulse → 90°  (centre)
  2.0 ms pulse → 180°

┌─────────────────────────────────────────┐
│ 20ms period (50 Hz)                     │
│ ▓▓░░░░░░░░░░░░░░░░░░ → 1ms = 0°        │
│ ▓▓▓░░░░░░░░░░░░░░░░░ → 1.5ms = 90°     │
│ ▓▓▓▓░░░░░░░░░░░░░░░░ → 2ms = 180°      │
└─────────────────────────────────────────┘
```

**Arduino `Servo.h` library** handles all timing automatically.

### SG90 Servo Specifications

| Parameter | Value |
|---|---|
| Operating Voltage | 4.8V – 6V |
| Stall Torque | 1.8 kg·cm |
| No-load Speed | 0.1 sec/60° |
| Rotation Range | 0° – 180° |
| Connector | 3-wire (VCC, GND, Signal) |

### Wire Colours

| Wire | Colour | Connect To |
|---|---|---|
| Power | Red | 5V |
| Ground | Brown/Black | GND |
| Signal | Orange/Yellow | PWM Pin |

---

### Part B — Stepper Motor (28BYJ-48)

A **stepper motor** divides a full rotation into a large number of equal **steps**.  
Each electrical pulse moves the rotor by exactly one step.

This gives **precise position control without a feedback sensor.**

**28BYJ-48 Specifications:**

| Parameter | Value |
|---|---|
| Type | Unipolar, 4-phase |
| Voltage | 5V |
| Step Angle (full step) | 5.625° × 1/64 gear = 0.0878° |
| Steps per Revolution | 2048 (half-step mode) |
| Gear Ratio | 64:1 |

**Step Sequence (Half-step mode — 8 steps):**

```
Step | IN1 | IN2 | IN3 | IN4
  1  |  1  |  0  |  0  |  0
  2  |  1  |  1  |  0  |  0
  3  |  0  |  1  |  0  |  0
  4  |  0  |  1  |  1  |  0
  5  |  0  |  0  |  1  |  0
  6  |  0  |  0  |  1  |  1
  7  |  0  |  0  |  0  |  1
  8  |  1  |  0  |  0  |  1
```

### ULN2003 Driver Board

The Arduino cannot directly drive the stepper's inductive coils (too much current). The **ULN2003** is a Darlington transistor array that amplifies the Arduino's signals to drive the motor.

```
Arduino Pin (5mA) → ULN2003 Input
ULN2003 Output → Motor Coil (200–500mA)
```

---

## Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| SG90 Servo Motor | 1 | 3 wires |
| 28BYJ-48 Stepper Motor | 1 | 5V unipolar |
| ULN2003 Driver Board | 1 | Included with stepper kit |
| Potentiometer 10kΩ | 1 | Servo angle control |
| Jumper Wires | 20 | — |

---

## Circuit Description

```
SERVO MOTOR:
  Red   → Arduino 5V
  Brown → Arduino GND
  Orange → Arduino Pin 9 (PWM ~ pin)

STEPPER + ULN2003:
  ULN2003 IN1 → Arduino Pin 8
  ULN2003 IN2 → Arduino Pin 9   ← Don't use with servo simultaneously
  ULN2003 IN3 → Arduino Pin 10
  ULN2003 IN4 → Arduino Pin 11
  ULN2003 VCC → External 5V (recommended) or Arduino 5V
  ULN2003 GND → Arduino GND + external supply GND
  Stepper 5-pin cable → ULN2003 output socket

POTENTIOMETER (for servo angle control):
  Pin 1 → 5V | Pin 2 (wiper) → A0 | Pin 3 → GND

⚠ WARNING: Do NOT run servo and stepper on same pins.
  Run them separately (two different programs).
```

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comments for Servo.h and Stepper.h usage |
| `program.ino` | Part A (servo sweep + pot control) + Part B (stepper) |
