/*
 * ============================================================
 * Experiment 01 — Understanding Arduino UNO Board
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 *
 * PURPOSE OF THIS FILE:
 * Read every comment carefully. Understand what each step does
 * conceptually BEFORE looking at program.ino.
 * Then try to write the code yourself based on these hints.
 * ============================================================
 */

// ─────────────────────────────────────────
// STEP 1: Understand Constants vs Variables
// ─────────────────────────────────────────
// A CONSTANT never changes after definition.
// Use 'const int' for pin numbers so you never accidentally change them.
// Naming convention: ALL_CAPS for constants.
//
// Question: Why use a constant instead of just writing '13' everywhere?
// Answer:   If you ever change the pin, you only change one line.
//
// YOUR TASK: Define a constant for the built-in LED pin.
// Hint: The built-in LED is connected to pin 13 on Arduino UNO.
// Syntax: const int NAME = VALUE;


// ─────────────────────────────────────────
// STEP 2: Understand the setup() Function
// ─────────────────────────────────────────
// setup() runs ONCE when the Arduino powers on or resets.
// Use it for:
//   - Setting pin directions (INPUT or OUTPUT)
//   - Starting Serial communication
//   - Initializing libraries
//
// YOUR TASK in setup():
//
//   a) Call Serial.begin(9600)
//      - This opens a serial connection at 9600 bits/second
//      - 9600 is the "baud rate" — how fast data is sent
//      - You must use the SAME baud rate in the Serial Monitor
//
//   b) Set the LED pin as OUTPUT using pinMode()
//      - Syntax: pinMode(PIN_NUMBER, OUTPUT);
//      - Why OUTPUT? Because we want to SEND signal (turn LED on/off)
//      - If reading a sensor, you'd use INPUT
//
//   c) Print a startup message using Serial.println()
//      - Hint: Serial.println("Hello World"); prints and adds newline
//      - Serial.print("Hello"); prints WITHOUT newline


// ─────────────────────────────────────────
// STEP 3: Understand the loop() Function
// ─────────────────────────────────────────
// loop() runs continuously FOREVER after setup() finishes.
// Think of it as an infinite while(true) loop.
//
// YOUR TASK in loop():
//
//   a) Declare a loop counter variable BEFORE the loop() function
//      - Syntax: int counter = 0;
//      - Why outside loop()? So it persists across iterations
//
//   b) Inside loop(), increment counter each time
//      - Use the ++ operator: counter++;
//
//   c) Blink the built-in LED (Pin 13):
//      Turn ON:  digitalWrite(LED_BUILTIN, HIGH);
//      Delay:    delay(500);  ← 500 milliseconds = 0.5 seconds
//      Turn OFF: digitalWrite(LED_BUILTIN, LOW);
//      Delay:    delay(500);
//
//   d) Print the counter and LED state to Serial Monitor:
//      Serial.print("Loop #");
//      Serial.print(counter);
//      Serial.println(": LED blinked");


// ─────────────────────────────────────────
// STEP 4: Understand Analog Pins
// ─────────────────────────────────────────
// analogRead(A0) reads voltage on pin A0 and converts it to 0–1023
// 0V    →    0
// 2.5V  →  511
// 5V    → 1023
//
// YOUR TASK:
//   - Leave A0 UNCONNECTED (floating)
//   - Read its value: int rawVal = analogRead(A0);
//   - Print it to serial
//   - Observe: it gives random values because the pin is "floating"
//   - This is why we always tie unused analog inputs to GND or VCC!
//
// THINK ABOUT:
//   What happens if you connect A0 to the 5V pin?
//   What value should you expect? (Hint: close to 1023)
//   What if you connect to GND? (Hint: close to 0)


// ─────────────────────────────────────────
// STEP 5: Understand Serial Monitor Output
// ─────────────────────────────────────────
// The Serial Monitor (Ctrl+Shift+M) is your debugging window.
// Every Serial.print/println message appears there.
//
// Two useful functions:
//   Serial.print(value)    → no newline at end
//   Serial.println(value)  → adds newline at end (\n)
//
// You can print text, numbers, or variables:
//   Serial.println("Text");      ← String
//   Serial.println(42);          ← Integer
//   Serial.println(3.14);        ← Float
//   Serial.println(counter);     ← Variable
//
// YOUR TASK:
//   - Create a "System Info" report that prints:
//     "=== Arduino UNO Board Info ==="
//     "CPU: ATmega328P @ 16MHz"
//     "Digital Pins: 14"
//     "Analog Pins: 6"
//     "PWM Pins: 6 (3,5,6,9,10,11)"
//     "Flash: 32KB | SRAM: 2KB | EEPROM: 1KB"
//   - Print this report ONCE in setup()
//   - Then in loop() print only the live data (counter, analog reads)


// ─────────────────────────────────────────
// CHALLENGE TASKS
// ─────────────────────────────────────────
// After completing the above:
//
// Challenge 1: Read A0, A1, A2 and print all three values per loop
//
// Challenge 2: Use the millis() function to print elapsed time
//   unsigned long t = millis();   ← milliseconds since board started
//   Serial.print("Uptime: ");
//   Serial.print(t / 1000);      ← convert to seconds
//   Serial.println(" seconds");
//
// Challenge 3: Count how many times you pressed RESET
//   Hint: EEPROM stores values permanently
//   #include <EEPROM.h>
//   int resets = EEPROM.read(0);
//   resets++;
//   EEPROM.write(0, resets);
//   Serial.print("This board has been reset "); Serial.print(resets); Serial.println(" times.");
