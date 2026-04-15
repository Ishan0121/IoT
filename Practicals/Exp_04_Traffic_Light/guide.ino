/*
 * ============================================================
 * Experiment 04 — 4-Way Traffic Light Simulation
 * FILE: guide.ino  (Step-by-step commented guide — NO real logic)
 * ============================================================
 */


// ─────────────────────────────────────────────────────────────
// STEP 1: Define All 12 LED Pins
// ─────────────────────────────────────────────────────────────
// You have 12 LEDs: 4 directions × 3 colours each.
// Organise your constants by direction for clarity.
//
// YOUR TASK — Fill in the pin numbers:
//
//   // NORTH signal
//   const int N_RED    = 2;
//   const int N_YELLOW = 3;
//   const int N_GREEN  = 4;
//
//   // SOUTH signal
//   const int S_RED    = ???;
//   const int S_YELLOW = ???;
//   const int S_GREEN  = ???;
//
//   // EAST signal
//   const int E_RED    = ???;
//   const int E_YELLOW = ???;
//   const int E_GREEN  = ???;
//
//   // WEST signal
//   const int W_RED    = ???;
//   const int W_YELLOW = ???;
//   const int W_GREEN  = ???;
//
// Refer to README.md for the pin assignment table.


// ─────────────────────────────────────────────────────────────
// STEP 2: Define Timing Constants
// ─────────────────────────────────────────────────────────────
// Real traffic lights use:
//   Green  = 25–60 seconds
//   Yellow = 3–5 seconds
//   All-red buffer = 1 second
//
// For testing, use shorter durations:
//
//   const int GREEN_DURATION  = 5000;   // 5 seconds
//   const int YELLOW_DURATION = 2000;   // 2 seconds
//   const int ALL_RED_BUFFER  = 1000;   // 1 second


// ─────────────────────────────────────────────────────────────
// STEP 3: Understand Arrays for Pin Management
// ─────────────────────────────────────────────────────────────
// With 12 pins, using 12 separate setTimeout calls is messy.
// Use ARRAYS to handle all pins together.
//
// An array groups related variables:
//   int allPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
//
// Then loop through them:
//   for (int i = 0; i < 12; i++) {
//     pinMode(allPins[i], OUTPUT);
//   }
//
// This sets ALL 12 pins as OUTPUT in just 2 lines!
//
// YOUR TASK:
//   Create an array 'allPins[]' containing all 12 pin numbers
//   Use it in setup() to set all as OUTPUT with a for loop


// ─────────────────────────────────────────────────────────────
// STEP 4: Create the allRed() Helper Function
// ─────────────────────────────────────────────────────────────
// EVERY colour transition must go through ALL RED first.
// This is a critical safety requirement.
//
// void allRed() {
//
//   Task: Set all 4 RED pins to HIGH, all other 8 pins to LOW
//
//   NORTH:   digitalWrite(N_RED, HIGH);  digitalWrite(N_YELLOW, LOW);  digitalWrite(N_GREEN, LOW);
//   SOUTH:   [do the same for S pins]
//   EAST:    [do the same for E pins]
//   WEST:    [do the same for W pins]
//
//   Then: Print "Phase: ALL RED" to Serial
//   Then: delay(ALL_RED_BUFFER);
//
// }


// ─────────────────────────────────────────────────────────────
// STEP 5: Create Phase Functions (FSM States)
// ─────────────────────────────────────────────────────────────
// Each phase is a function that sets specific LEDs and waits.
//
// void phaseNorthSouthGreen() {
//   // N/S: GREEN on, RED off, YELLOW off
//   // E/W: RED on, GREEN off, YELLOW off
//   // Print: "Phase 1: N/S GREEN | E/W RED"
//   // delay(GREEN_DURATION);
// }
//
// void phaseNorthSouthYellow() {
//   // N/S: YELLOW on, GREEN off, RED off
//   // E/W: RED still on
//   // Print: "Phase 2: N/S YELLOW | E/W RED"
//   // delay(YELLOW_DURATION);
// }
//
// void phaseEastWestGreen() {
//   // E/W: GREEN on, RED off, YELLOW off
//   // N/S: RED on (opposite pair)
//   // Print: "Phase 3: E/W GREEN | N/S RED"
//   // delay(GREEN_DURATION);
// }
//
// void phaseEastWestYellow() {
//   // E/W: YELLOW on, GREEN off
//   // N/S: RED still on
//   // Print: "Phase 4: E/W YELLOW | N/S RED"
//   // delay(YELLOW_DURATION);
// }
//
// YOUR TASK: Write all four phase functions.


// ─────────────────────────────────────────────────────────────
// STEP 6: setup() Function
// ─────────────────────────────────────────────────────────────
// void setup() {
//   Task A: Set all 12 pins as OUTPUT (use the array + for loop!)
//   Task B: Serial.begin(9600);
//   Task C: Call allRed() — start in the safe ALL-RED state
//   Task D: Print: "Traffic Light System Initialized"
// }


// ─────────────────────────────────────────────────────────────
// STEP 7: loop() Function — The FSM Cycle
// ─────────────────────────────────────────────────────────────
// void loop() {
//   allRed();                    // Safety buffer before each cycle
//   phaseNorthSouthGreen();      // N/S gets green
//   phaseNorthSouthYellow();     // N/S transitions to yellow
//   allRed();                    // Safety buffer
//   phaseEastWestGreen();        // E/W gets green
//   phaseEastWestYellow();       // E/W transitions to yellow
//   // loop() will then repeat automatically
// }
//
// THINK ABOUT:
//   What happens if you remove the allRed() calls?
//   Could both N/S and E/W ever be GREEN at the same time?
//   Why is yellow shown BEFORE red, never after?


// ─────────────────────────────────────────────────────────────
// CHALLENGE: Emergency Vehicle Override
// ─────────────────────────────────────────────────────────────
// Add a pushbutton on pin A0.
// When pressed, ALL signals go RED and stay RED for 10 seconds
// (simulating an emergency vehicle passing through).
//
// Hint: Read the button state at the START of each phase function.
//   if (digitalRead(EMERGENCY_BTN) == LOW) {
//     allRed();
//     delay(10000);
//     return;   ← exit current phase early
//   }
