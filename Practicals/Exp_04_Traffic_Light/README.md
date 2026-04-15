# Experiment 04 — Simulation of 4-Way Traffic Light with Arduino

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To simulate a real-world 4-way traffic intersection using 12 LEDs (3 per direction × 4 directions) controlled by Arduino, implementing proper traffic light phases with a **Finite State Machine** approach.

---

## Theory

### Traffic Light System

A 4-way traffic intersection has signals for: **North, South, East, West**.  
Each signal has 3 lights: **Red, Yellow, Green**.  
At any moment, only ONE pair of directions gets GREEN — the other pair must remain RED.

### Phase Sequence

```
Phase 0 — ALL RED (safety buffer between transitions)
Phase 1 — North + South: GREEN  |  East + West: RED      [5s]
Phase 2 — North + South: YELLOW |  East + West: RED      [2s]
Phase 3 — ALL RED (safety buffer)                        [1s]
Phase 4 — East + West: GREEN    |  North + South: RED    [5s]
Phase 5 — East + West: YELLOW   |  North + South: RED    [2s]
(Cycle repeats)
```

### Finite State Machine (FSM) Concept

An FSM is a model where the system is always in one of a finite set of **states**. Each state has defined **outputs** (which LEDs are on), and defined **transitions** (when to move to the next state).

```
        ┌──────────────────────────────────────┐
        │                                      │
     ┌──▼──┐  5s   ┌─────┐  2s   ┌──────┐  1s  │
     │ N/S │─────▶│ N/S │─────▶│ All  │──────┤
     │GREEN│       │YEL  │       │ RED  │      │
     └─────┘       └─────┘       └──┬───┘      │
                                    │5s        │
                              ┌─────▼─┐ 2s  ┌──┴──┐
                              │ E/W   │───▶│ E/W │
                              │ GREEN │     │ YEL │
                              └───────┘     └─────┘
```

---

## Components Required

| Component | Quantity | Colour |
|---|---|---|
| Arduino UNO | 1 | — |
| Red LEDs | 4 | Red |
| Yellow LEDs | 4 | Yellow |
| Green LEDs | 4 | Green |
| Resistors 220Ω | 12 | — |
| Breadboard | 2 | — |
| Jumper Wires | 25+ | Mixed |

---

## Pin Assignment

| Signal | Red | Yellow | Green |
|---|---|---|---|
| North | Pin 2 | Pin 3 | Pin 4 |
| South | Pin 5 | Pin 6 | Pin 7 |
| East | Pin 8 | Pin 9 | Pin 10 |
| West | Pin 11 | Pin 12 | Pin 13 |

---

## Circuit Description

```
For EACH LED (12 total):
  Arduino_Pin → [220Ω Resistor] → LED Anode(+) → LED Cathode(−) → GND

Layout tip:
  - Use 2 breadboards side by side
  - Create a common GND rail on both breadboards
  - Colour-code your wires: Red wire for Red LEDs, Green for Green, etc.
  - Label each section: North, South, East, West

Safety Rule:
  Start with ALL RED → verify → then proceed to other phases
```

---

## Traffic Light Logic Table

| Phase | N-Red | N-Yellow | N-Green | S-Red | S-Yellow | S-Green | E-Red | E-Yellow | E-Green | W-Red | W-Yellow | W-Green |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| ALL RED | ON | off | off | ON | off | off | ON | off | off | ON | off | off |
| N/S GREEN | off | off | ON | off | off | ON | ON | off | off | ON | off | off |
| N/S YELLOW | off | ON | off | off | ON | off | ON | off | off | ON | off | off |
| E/W GREEN | ON | off | off | ON | off | off | off | off | ON | off | off | ON |
| E/W YELLOW | ON | off | off | ON | off | off | off | ON | off | off | ON | off |

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comment walk-through of FSM design |
| `program.ino` | Full working FSM traffic light implementation |

---

## Safety Rules (IMPORTANT)

1. **NEVER** allow N/S and E/W to both be GREEN simultaneously
2. Always insert an ALL-RED phase during transitions (prevents intersection collision)
3. Yellow phase is mandatory before every Green-to-Red transition
4. Verify ALL-RED state works before testing full cycle

---

## Extension Ideas

1. **Pedestrian button:** Add a pushbutton that requests crossing time.
2. **Emergency mode:** A button that turns all signals RED (ambulance passing).
3. **Night mode:** At midnight, all lights blink amber (yellow) slowly.
4. **Countdown timer:** Add a 7-segment display showing seconds remaining.
