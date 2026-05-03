# Experiment 01 — Understanding Arduino UNO Board and Components

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To study, identify, and understand every component of the Arduino UNO board — its physical layout, electrical specifications, pin types, and roles — so that future experiments can be performed with full confidence.

---

## What is Arduino UNO?

The **Arduino UNO** is an open-source microcontroller development board based on the **ATmega328P** chip. It is the most popular entry point for learning embedded systems and IoT.

- "UNO" means "One" in Italian, marking it as the first in a new series.
- It was designed to make electronics accessible to artists, students, and hobbyists with zero prior experience.

---

## Board Overview

```
                    Arduino UNO — Top View
   ┌──────────────────────────────────────────────────────────┐
   │  [USB Type-B Port]                [DC Power Jack 7-12V]  │
   │                                                          │
   │  ┌──────────┐                                            │
   │  │ATmega328P│   <- Main microcontroller chip             │
   │  └──────────┘                                            │
   │                                                          │
   │  Digital Pins:  D0  D1  D2  D3~ D4  D5~ D6~ D7           │
   │                 D8  D9~ D10~ D11~ D12 D13(LED)           │
   │                 ~ = PWM capable                          │
   │                                                          │
   │  Analog Pins:   A0  A1  A2  A3  A4(SDA) A5(SCL)          │
   │                                                          │
   │  Power Header:  IOREF  RESET  3.3V  5V  GND  GND  Vin    │
   │                                                          │
   │  [RESET Button]     [TX LED]  [RX LED]  [Pin13 LED]      │
   │  [ICSP Header]      [16MHz Crystal]                      │
   └──────────────────────────────────────────────────────────┘
```

---

## Key Electrical Specifications

| Parameter | Value |
|---|---|
| Microcontroller | ATmega328P (8-bit AVR) |
| Operating Voltage | 5V |
| Input Voltage (recommended) | 7–12V |
| Input Voltage (absolute max) | 6–20V |
| Digital I/O Pins | 14 (6 with PWM) |
| Analog Input Pins | 6 (10-bit ADC) |
| DC Current per I/O Pin | 40 mA max |
| DC Current for 3.3V Pin | 50 mA max |
| Flash Memory | 32 KB (0.5 KB bootloader) |
| SRAM (runtime memory) | 2 KB |
| EEPROM (permanent storage) | 1 KB |
| Clock Speed | 16 MHz |

---

## Pin Types Explained

### Digital Pins (D0–D13)
- Output: `HIGH` = 5V, `LOW` = 0V
- Input: Reads 5V as HIGH, 0V as LOW
- **D0, D1** are also Serial RX/TX — avoid using these when serial debugging
- **PWM Pins (marked ~):** D3, D5, D6, D9, D10, D11
  - Simulate analog output using Pulse Width Modulation
  - `analogWrite(pin, 0-255)` controls duty cycle

### Analog Input Pins (A0–A5)
- 10-bit ADC → reads values 0 to 1023
- Maps 0V → 0, 5V → 1023
- Can also be used as digital pins if needed
- **A4 = SDA, A5 = SCL** for I2C communication

### Power Pins
| Pin | Description |
|---|---|
| `5V` | Regulated 5V output (max 200mA draw) |
| `3.3V` | Regulated 3.3V (max 50mA draw) |
| `GND` | Ground reference (two GND pins) |
| `Vin` | Unregulated input from barrel jack |
| `RESET` | Pull LOW to reset the microcontroller |

---

## Communication Interfaces

| Interface | Pins | Protocol | Use Case |
|---|---|---|---|
| Serial (UART) | D0(RX), D1(TX) | UART | Serial Monitor, GPS, GSM |
| I2C | A4(SDA), A5(SCL) | I2C | LCD, MPU6050, BME280 |
| SPI | D10(SS), D11(MOSI), D12(MISO), D13(SCK) | SPI | SD card, RFID, TFT |

---

## On-Board LEDs

| LED | Pin | Lights up when... |
|---|---|---|
| **PWR** | — | Board is powered |
| **TX** | D1 | Arduino sends serial data |
| **RX** | D0 | Arduino receives serial data |
| **L (Pin 13)** | D13 | Pin 13 is set HIGH in code |

---

## Memory Architecture

```
ATmega328P Memory:

Flash (32KB) ──→ Stores your compiled program
                 Survives power off. Loaded by bootloader.

SRAM (2KB)   ──→ Runtime memory for variables
                 Lost on power off / reset

EEPROM (1KB) ──→ Non-volatile user storage
                 Survives power off. Write-limited (~100,000 writes)
```

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Step-by-step commented exploration sketch |
| `program.ino` | Working sketch that demonstrates board features |

---

## Things to Observe

1. Locate every pin label on the board physically before coding.
2. Notice the `~` symbol — only those pins support `analogWrite()`.
3. Observe TX/RX LEDs blink when Serial Monitor is open.
4. Float pin A0 (leave unconnected) and watch the random values.
5. Understand the difference between `5V` output pin (limited to 200mA) and a power supply.

---

## Common Beginner Mistakes

| Mistake | Consequence | Fix |
|---|---|---|
| Short-circuit between GND and 5V | Possible board damage | Always double-check wiring |
| Drawing >40mA from a digital pin | Pin burns out | Use transistor or driver IC |
| Using D0/D1 while serial is open | Garbled serial output | Avoid D0/D1 for sensors |
| Floating analog pin | Random 0–1023 readings | Always tie input to GND or VCC |
| Providing >5V to digital input | Permanent damage | Use voltage divider |
