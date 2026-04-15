/*
 * ============================================================
 * Experiment 02 — Installing and Working with Arduino IDE
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 *
 * This file walks you through YOUR FIRST Arduino sketch.
 * Follow each comment block, understand it, then write the code.
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: The Header Comment Block
// ─────────────────────────────────────────────────────────────
// Every professional sketch starts with a block comment:
//   - Experiment title
//   - Your name, roll number, class, date
//   - Brief description: What does this sketch do?
//
// YOUR TASK: Write a block comment at the top of your file
// Use this format:
//   /*
//    * Experiment 02 : Arduino IDE First Sketch
//    * Author        : [Your Name]
//    * Date          : [Date]
//    * Description   : Blinks built-in LED and prints to Serial Monitor
//    */


// ─────────────────────────────────────────────────────────────
// STEP 2: Defining the LED Pin as a Named Constant
// ─────────────────────────────────────────────────────────────
// Instead of hardcoding pin number 13 everywhere:
//   → Harder to read, harder to change
//
// Define a CONSTANT so the name describes the pin:
//   const int LED_PIN = 13;
//
// Why 'const'? It tells the compiler this value cannot change.
// Why 'int'? Pin numbers are integers.
//
// Arduino also provides: LED_BUILTIN
//   → This is automatically set to 13 on UNO
//   → Use either LED_BUILTIN or your own constant
//
// YOUR TASK: Define LED_PIN = 13 as a constant above setup()


// ─────────────────────────────────────────────────────────────
// STEP 3: setup() — Initialization
// ─────────────────────────────────────────────────────────────
// void setup() {
//
//   Task A: Start Serial communication at 9600 baud
//   → This allows your Arduino to "talk" to your computer
//   → Open Serial Monitor in IDE to see what it sends
//   → In Serial Monitor, select "9600 baud" at the bottom
//   → Hint: Serial.begin(9600);
//
//   Task B: Configure LED pin direction
//   → The pin needs to be an OUTPUT (we're SENDING signal to LED)
//   → Hint: pinMode(LED_PIN, OUTPUT);
//
//   Task C: Print a welcome message to Serial Monitor
//   → This confirms setup ran, and you see it in the monitor
//   → Use Serial.println() to add a newline after the text
//   → Try printing: "=== Arduino IDE First Sketch ==="
//   → Then print: "Setup complete. Starting loop..."
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 4: loop() — Main Repeated Logic
// ─────────────────────────────────────────────────────────────
// void loop() {
//
//   Task A: Declare a STATIC counter inside the loop
//   → A STATIC variable keeps its value between calls
//   → Unlike regular int counter = 0; which resets each time!
//   → Syntax: static int counter = 0;
//   → Then increment: counter++;
//
//   Task B: Turn LED ON and wait
//   → digitalWrite(LED_PIN, HIGH);   ← 5V goes to pin → LED lights
//   → delay(1000);                   ← wait 1000 ms = 1 second
//
//   Task C: Print to Serial Monitor while LED is ON
//   → Serial.print("Loop ");
//   → Serial.print(counter);
//   → Serial.println(": LED is ON");
//
//   Task D: Turn LED OFF and wait
//   → digitalWrite(LED_PIN, LOW);    ← 0V → LED off
//   → delay(1000);
//   → Serial.print("Loop ");
//   → Serial.print(counter);
//   → Serial.println(": LED is OFF");
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: Using the Serial Plotter
// ─────────────────────────────────────────────────────────────
// The Serial Plotter draws a GRAPH of any number printed via serial.
// This is extremely useful for visualizing sensor data.
//
// How to plot:
//   → Print numbers separated by spaces or commas
//   → Open Tools → Serial Plotter
//
// YOUR TASK:
//   → Print the LED state as a number: 1 when ON, 0 when OFF
//   → Serial.println(1);   ← when LED is HIGH
//   → Serial.println(0);   ← when LED is LOW
//   → Watch the square wave pattern in Serial Plotter!
//
// THINK ABOUT:
//   What does a square wave look like?
//   What happens if ON time ≠ OFF time?


// ─────────────────────────────────────────────────────────────
// STEP 6: Keyboard Shortcuts to Learn Today
// ─────────────────────────────────────────────────────────────
// Ctrl + R       → Verify/Compile sketch
// Ctrl + U       → Upload sketch to board
// Ctrl + Shift + M → Open Serial Monitor
// Ctrl + Shift + L → Open Serial Plotter
// Ctrl + Shift + I → Library Manager
// Ctrl + Z       → Undo
// Ctrl + /       → Toggle comment on selected lines
//
// YOUR TASK: Practice each shortcut at least once today.


// ─────────────────────────────────────────────────────────────
// CHALLENGE: Change the Blink Pattern
// ─────────────────────────────────────────────────────────────
// Instead of a simple 1-second ON, 1-second OFF blink:
//
// Challenge 1: Make it blink 3 times quickly, then pause 2 seconds
//   HINT: Write a helper function:
//   void blinkNTimes(int n, int onMs, int offMs) {
//     for (int i = 0; i < n; i++) {
//       // turn on, delay, turn off, delay
//     }
//   }
//   Then call: blinkNTimes(3, 200, 200); in loop()
//
// Challenge 2: SOS signal (... --- ...)
//   S = 3 short blinks   (200ms each)
//   O = 3 long blinks    (600ms each)
//   S = 3 short blinks   (200ms each)
//   Pause: 2 seconds before repeating
