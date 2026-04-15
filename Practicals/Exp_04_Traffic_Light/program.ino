/*
 * ============================================================
 * Experiment 04 — 4-Way Traffic Light Simulation
 * FILE: program.ino  (Complete working implementation)
 * ============================================================
 * Circuit:
 *   North: Red=2, Yellow=3, Green=4
 *   South: Red=5, Yellow=6, Green=7
 *   East:  Red=8, Yellow=9, Green=10
 *   West:  Red=11,Yellow=12,Green=13
 *   Emergency button: A0 (INPUT_PULLUP)
 * ============================================================
 */

// ── Pin Definitions ───────────────────────────────────────
// North
const int N_RED = 2, N_YELLOW = 3, N_GREEN = 4;
// South
const int S_RED = 5, S_YELLOW = 6, S_GREEN = 7;
// East
const int E_RED = 8, E_YELLOW = 9, E_GREEN = 10;
// West
const int W_RED = 11, W_YELLOW = 12, W_GREEN = 13;

const int EMERGENCY_BTN = A0;

// ── All 12 LED pins in one array (for easy setup) ─────────
const int ALL_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int NUM_PINS   = 12;

// ── Timing (ms) ───────────────────────────────────────────
const int GREEN_TIME  = 5000;
const int YELLOW_TIME = 2000;
const int ALL_RED_T   = 1000;

static int cycleCount = 0;

// ── Helper: check emergency button ────────────────────────
bool isEmergency() {
  return (digitalRead(EMERGENCY_BTN) == LOW);
}

// ── Set a single signal direction ─────────────────────────
// color: 0=RED, 1=YELLOW, 2=GREEN
void setSignal(int r, int y, int g, int color) {
  digitalWrite(r, color == 0 ? HIGH : LOW);
  digitalWrite(y, color == 1 ? HIGH : LOW);
  digitalWrite(g, color == 2 ? HIGH : LOW);
}

// ── All 4 signals to RED ───────────────────────────────────
void allRed(bool verbose = true) {
  setSignal(N_RED, N_YELLOW, N_GREEN, 0);
  setSignal(S_RED, S_YELLOW, S_GREEN, 0);
  setSignal(E_RED, E_YELLOW, E_GREEN, 0);
  setSignal(W_RED, W_YELLOW, W_GREEN, 0);
  if (verbose) Serial.println(F("[ALL RED]"));
  delay(ALL_RED_T);
}

// ── FSM Phase Functions ────────────────────────────────────
void phaseNS_Green() {
  if (isEmergency()) return;
  setSignal(N_RED, N_YELLOW, N_GREEN, 2); // North: GREEN
  setSignal(S_RED, S_YELLOW, S_GREEN, 2); // South: GREEN
  setSignal(E_RED, E_YELLOW, E_GREEN, 0); // East:  RED
  setSignal(W_RED, W_YELLOW, W_GREEN, 0); // West:  RED
  Serial.println(F("[Phase 1] N/S GREEN | E/W RED"));
  delay(GREEN_TIME);
}

void phaseNS_Yellow() {
  if (isEmergency()) return;
  setSignal(N_RED, N_YELLOW, N_GREEN, 1); // North: YELLOW
  setSignal(S_RED, S_YELLOW, S_GREEN, 1); // South: YELLOW
  setSignal(E_RED, E_YELLOW, E_GREEN, 0);
  setSignal(W_RED, W_YELLOW, W_GREEN, 0);
  Serial.println(F("[Phase 2] N/S YELLOW | E/W RED"));
  delay(YELLOW_TIME);
}

void phaseEW_Green() {
  if (isEmergency()) return;
  setSignal(N_RED, N_YELLOW, N_GREEN, 0);
  setSignal(S_RED, S_YELLOW, S_GREEN, 0);
  setSignal(E_RED, E_YELLOW, E_GREEN, 2); // East:  GREEN
  setSignal(W_RED, W_YELLOW, W_GREEN, 2); // West:  GREEN
  Serial.println(F("[Phase 3] E/W GREEN | N/S RED"));
  delay(GREEN_TIME);
}

void phaseEW_Yellow() {
  if (isEmergency()) return;
  setSignal(N_RED, N_YELLOW, N_GREEN, 0);
  setSignal(S_RED, S_YELLOW, S_GREEN, 0);
  setSignal(E_RED, E_YELLOW, E_GREEN, 1); // East:  YELLOW
  setSignal(W_RED, W_YELLOW, W_GREEN, 1); // West:  YELLOW
  Serial.println(F("[Phase 4] E/W YELLOW | N/S RED"));
  delay(YELLOW_TIME);
}

// ── Emergency override ────────────────────────────────────
void emergencyOverride() {
  Serial.println(F("*** EMERGENCY OVERRIDE — ALL RED 10s ***"));
  for (int i = 0; i < 10; i++) {
    allRed(false);
    delay(900); // total ~10s
  }
  Serial.println(F("*** EMERGENCY CLEARED ***"));
}

// ── setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(ALL_PINS[i], OUTPUT);
  }
  pinMode(EMERGENCY_BTN, INPUT_PULLUP);
  allRed(true);
  Serial.println(F("=== 4-Way Traffic Light System Ready ==="));
  Serial.println(F("Green: 5s | Yellow: 2s | Buffer: 1s"));
  Serial.println(F("Press A0 button for emergency override"));
  Serial.println();
}

// ── Main FSM loop ─────────────────────────────────────────
void loop() {
  // Emergency check before each cycle
  if (isEmergency()) {
    emergencyOverride();
    return;
  }

  cycleCount++;
  Serial.print(F("\n=== Cycle #")); Serial.print(cycleCount); Serial.println(F(" ==="));

  allRed();           // Safety buffer
  phaseNS_Green();    // N/S green
  phaseNS_Yellow();   // N/S yellow
  allRed();           // Safety buffer
  phaseEW_Green();    // E/W green
  phaseEW_Yellow();   // E/W yellow
}
