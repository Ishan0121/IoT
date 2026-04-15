# Experiment 02 — Installing and Working with Arduino IDE

> **Lab:** MJ DSE-2P: Practical of IoT (Arduino Lab) | **Credits:** 01

---

## Objective

To install Arduino IDE 2.x, configure it for the Arduino UNO board, understand the IDE's structure and compilation pipeline, and successfully upload a first sketch.

---

## What is Arduino IDE?

The **Arduino IDE (Integrated Development Environment)** is the software tool used to write, compile, and upload programs (called **sketches**) to Arduino boards. It is available for Windows, macOS, and Linux.

- IDE 1.x: Classic version (still widely used)
- IDE 2.x: Modern rebuild with autocomplete, debugger, live plotter — **recommended**

---

## Installation (Step-by-Step)

### On Linux (Ubuntu/Debian)
```bash
# Method 1: AppImage (recommended, no system install needed)
# 1. Download from arduino.cc/en/software
# 2. Make executable:
chmod +x arduino-ide_*.AppImage
# 3. Run:
./arduino-ide_*.AppImage

# Method 2: Snap package
sudo snap install arduino
```

### On Windows
1. Download the `.exe` installer from [arduino.cc/en/software](https://arduino.cc/en/software)
2. Run installer, accept defaults
3. Install USB drivers when prompted (important!)

---

## IDE Layout

```
┌───────────────────────────────────────────────────────────┐
│  [File] [Edit] [Sketch] [Tools] [Help]     Menu Bar       │
├───────────────────────────────────────────────────────────┤
│  [✓ Verify] [→ Upload] [Serial Plotter] [Serial Monitor]  │
├──────────────────┬────────────────────────────────────────┤
│                  │                                        │
│  File Explorer   │     CODE EDITOR                        │
│  (left panel)    │     (write your sketch here)           │
│                  │                                        │
├──────────────────┴────────────────────────────────────────┤
│  OUTPUT (bottom panel)                                    │
│  Shows: compilation errors, upload status, warnings       │
└───────────────────────────────────────────────────────────┘
```

---

## Compilation Pipeline

Understanding what happens when you click **Verify (✓)** and **Upload (→)**:

```
Your Code (.ino / .cpp)
        │
        ▼
  Preprocessing       ← Arduino adds hidden setup boilerplate
        │
        ▼
  Compilation         ← avr-gcc compiles to object files (.o)
  (by avr-gcc)
        │
        ▼
  Linking             ← Links all object files + Arduino core
        │
        ▼
  HEX file generated  ← Machine code for ATmega328P
        │
        ▼
  Upload (avrdude)    ← Sends HEX to board via USB bootloader
        │
        ▼
  Bootloader runs     ← Bootloader hands control to your sketch
        │
        ▼
  Program executes!
```

---

## Board Configuration

| Setting | Value for Arduino UNO |
|---|---|
| **Tools → Board** | Arduino AVR Boards → Arduino UNO |
| **Tools → Port (Windows)** | COM3, COM4, etc. (varies) |
| **Tools → Port (Linux)** | /dev/ttyUSB0 or /dev/ttyACM0 |
| **Tools → Programmer** | AVRISP mkII (default) |
| **Tools → Baud Rate** | 9600 (for Serial Monitor) |

### Linux Serial Port Permission Fix
```bash
# If you get "permission denied" on /dev/ttyUSB0:
sudo usermod -aG dialout $USER
# Log out and log back in for this to take effect
```

---

## Key IDE Features

### Serial Monitor
- Keyboard shortcut: `Ctrl + Shift + M`
- Shows all `Serial.print()` / `Serial.println()` output from board
- **Must match baud rate** set in `Serial.begin()` in your sketch

### Serial Plotter
- Keyboard shortcut: `Ctrl + Shift + L`
- Plots numeric `Serial.println()` values as a real-time graph
- Excellent for visualizing sensor data trends

### Library Manager
- Keyboard shortcut: `Ctrl + Shift + I`
- Install community libraries (DHT, Servo, RFID, etc.)
- Search by name, click Install

### Board Manager
- `Tools → Board → Boards Manager`
- Install support for non-standard boards (ESP8266, ESP32, etc.)

---

## Sketch Structure Reference

```cpp
// Every Arduino sketch must have exactly these two functions:

void setup() {
  // Runs ONCE at startup — initialize pins, serial, libraries
}

void loop() {
  // Runs FOREVER after setup() — main program logic
}
```

---

## Files in This Experiment

| File | Purpose |
|---|---|
| `guide.ino` | Guided comment walk-through of IDE features |
| `program.ino` | Feature-rich sketch demonstrating IDE tools |

---

## Common IDE Issues and Fixes

| Issue | Cause | Fix |
|---|---|---|
| "Port not found" | Driver not installed / permission issue | Install CH340 driver or run `usermod -aG dialout` |
| "Unable to upload" | Wrong board selected | Tools → Board → Arduino UNO |
| "Sketch too large" | SRAM or Flash overflow | Reduce variables; use `F()` macro for strings |
| Compilation error | Syntax mistake | Read error line number carefully |
| Serial Monitor garbled | Baud mismatch | Match `Serial.begin(X)` with Monitor baud rate |
