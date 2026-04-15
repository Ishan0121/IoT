# Experiment 03 — Blinking LED Sketch with Arduino

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To understand digital output control by wiring an external LED with a current-limiting resistor, then making it blink with configurable timing using `digitalWrite()` and `delay()`.

---

## Theory

### What is an LED?

A **Light Emitting Diode (LED)** is a semiconductor device that emits light when current flows through it in the forward direction.

Key properties:
- **Polarized:** Has a positive (anode) and negative (cathode) terminal — **direction matters!**
- **Voltage Drop:** A red LED drops ~2V; blue/white LEDs drop ~3.2V.
- **Current Limit:** Maximum safe current is **20 mA** (0.02 A). Exceed this — LED burns.

### Why a Current-Limiting Resistor?

Without a resistor, the LED draws unlimited current → **immediate burnout**.

Using **Ohm's Law:**

```
R = (V_supply − V_LED) / I_desired

For a red LED on Arduino 5V:
R = (5V − 2V) / 0.02A = 150Ω → Use 220Ω (next standard value — safer)
```

**Always use a resistor in series with an LED.**

### How to Identify LED Polarity

```
        Anode (+)   Cathode (−)
             │           │
External:  Longer leg  Shorter leg
Inside:    Small part  Large flat part (look through the lens)
Flat edge: Always on the Cathode side
```

### What is `digitalWrite()`?

```cpp
digitalWrite(pin, HIGH);  // Sets pin to 5V → current flows → LED ON
digitalWrite(pin, LOW);   // Sets pin to 0V → no current   → LED OFF
```

### What is `delay()`?

```cpp
delay(1000);  // Pause execution for 1000 milliseconds = 1 second
```

**Limitation:** `delay()` blocks ALL code — nothing else runs during it.  
For complex projects, use `millis()` instead (non-blocking).

---

## Components Required

| Component | Quantity | Specification |
|---|---|---|
| Arduino UNO | 1 | — |
| LED | 1 | Any colour (Red recommended for beginners) |
| Resistor | 1 | 220Ω (Red-Red-Brown-Gold) |
| Breadboard | 1 | Half-size or full-size |
| Jumper Wires | 3 | Male-to-Male |
| USB Cable | 1 | Type-B |

---

## Circuit Diagram

```
Arduino UNO                 Breadboard
──────────                 ──────────
Pin 13  ──── Wire ───→    Row A5  → [220Ω Resistor] → Row A8
                                                          │
                                              LED Anode (+) at A8
                                              LED Cathode (−) at A9
                                                          │
GND     ──── Wire ───→    GND Rail ←─── Wire ──── A9

Current Path:
Pin 13 [5V] → Resistor → LED Anode → LED Cathode → GND [0V]
```

**Reading Resistor Color Bands (220Ω):**
```
RED  - RED  - BROWN  - GOLD
 2  -  2  -  ×10   - ±5%
= 22 × 10 = 220Ω
```

---

## Pin Configuration

| Arduino Pin | Connected To | Direction |
|---|---|---|
| Pin 13 (or any digital) | Resistor → LED(+) | OUTPUT |
| GND | LED(−) | — |

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comment walk-through of LED blink logic |
| `program.ino` | Full implementation with variable timing & Serial output |

---

## Expected Output

- External LED blinks at the programmed interval.
- Serial Monitor shows: `"Blink #X: ON for 500ms"` / `"Blink #X: OFF for 500ms"`.
- Changing `ON_TIME` and `OFF_TIME` constants changes the blink pattern.

---

## Extension Ideas After This Experiment

1. **Multi-LED:** Wire 3 LEDs on pins 11, 12, 13 and blink them in sequence.
2. **PWM Fade:** Use `analogWrite()` on a PWM pin to fade the LED in/out.
3. **Non-blocking blink:** Replace `delay()` with `millis()` logic.
4. **Morse code:** Encode a message in light pulses.
