# 🌐 Internet of Things (IoT) – Complete Beginner to Practical Guide
### MJ DSE-2T | Credits: 03 | Full Marks: 75

> **How to use this guide:** Read each section from top to bottom. Every concept starts simple and builds up. Don't skip sections — IoT connects everything!

---

## 📚 Table of Contents

1. [Introduction to IoT](#introduction-to-iot)
2. [UNIT I – Fundamentals of IoT](#unit-i--fundamentals-of-iot)
3. [UNIT II – Sensors & Networks](#unit-ii--sensors-and-networks)
4. [UNIT III – Data Handling & Analytics](#unit-iii--data-handling--analytics)
5. [UNIT IV – Applications of IoT](#unit-iv--applications-of-iot)
6. [Practical Lab – Arduino Experiments](#practical-lab-mj-dse-2p-arduino-lab)
7. [References and Further Reading](#references-and-further-reading)

---

# Introduction to IoT

## What is IoT? (Start Simple)

Imagine your refrigerator texting you: *"You're out of milk!"*  
Or your alarm waking you up 10 minutes early because it checked the traffic report online.

**That's IoT.**

> 💡 **Simple Definition:**  
> IoT (Internet of Things) is the network of physical objects — devices, appliances, vehicles, machines — embedded with sensors, software, and internet connectivity so they can collect, share, and act on data without human intervention.

> 📖 **Technical Definition (Exam Ready):**  
> IoT is a global infrastructure for the information society, enabling advanced services by interconnecting physical and virtual things based on existing and evolving interoperable information and communication technologies (ICTs). — *ITU-T*

---

## Key Characteristics of IoT

| Characteristic | What it Means | Example |
|---|---|---|
| **Connectivity** | Everything is connected | Smartwatch syncing to phone |
| **Intelligence** | Devices can make decisions | Thermostat adjusting temperature |
| **Sensing** | Gather real-world data | Humidity sensor in greenhouse |
| **Dynamic Nature** | State changes constantly | Traffic sensors updating every second |
| **Scalability** | Can handle millions of devices | Smart city with 1M sensors |
| **Heterogeneity** | Different devices, different protocols | Bluetooth + WiFi + Zigbee in one home |
| **Safety** | Protects privacy and security | Encrypted data transfer |
| **Energy Efficiency** | Low power consumption | IoT battery lasting 10 years |

---

## Real-World Examples of IoT

```
Your Day with IoT:

6:00 AM   → Smart alarm checks traffic, wakes you up early
6:15 AM   → Smart fridge displays what you need to buy
7:00 AM   → Smart lock auto-unlocks when your face is recognized
8:00 AM   → Car navigation updates route based on live traffic
All Day   → Fitness band tracks heart rate and steps
Evening   → Smart bulbs auto-dim at sunset
Night     → Security camera sends alert if motion detected
```

**Industry Examples:**
- 🏥 **Healthcare** – ECG transmitted to doctor remotely
- 🌾 **Agriculture** – Soil moisture sensor auto-triggers irrigation
- 🏭 **Industry** – Machines self-report when maintenance is needed
- 🏙️ **City** – Streetlights that dim when no one is around
- 🛒 **Retail** – RFID tags track every item on the shelf

---

## Evolution and History of IoT

```
Timeline:
1969  → ARPANET (Internet precursor) born
1982  → Carnegie Mellon's "Internet Coke Machine" – first internet thing
1990  → John Romkey's internet toaster – first IoT device ever
1991  → Mark Weiser coins "Ubiquitous Computing"
1999  → Kevin Ashton coins the term "Internet of Things" at P&G
2000  → LG announces first internet refrigerator
2008  → More devices connected than people on Earth (milestone!)
2011  → IPv6 launched – 340 undecillion IP addresses available
2020  → 30+ billion IoT devices worldwide
2025  → 75+ billion IoT devices projected
```

> 🧠 **Kevin Ashton** is considered the **Father of IoT** — he used the term for the first time in 1999 to describe RFID-based supply chain management at Procter & Gamble.

---

[Back to top](#)

---
# UNIT I — Fundamentals of IoT

---

## 1.1 Definitions & Characteristics of IoT

### Simple Explanation
Think of IoT as giving "senses" to everyday objects.
- A **thermometer** always measured temperature, but an **IoT thermometer** sends that data to your phone and auto-adjusts your AC.

### The 5 C's of IoT (Framework to Remember)

```
Collect → Connect → Compute → Control → Create value
   ↑          ↑         ↑         ↑          ↑
Sensors    Network    Cloud      Act      Business
```

### Core Definitions (Exam Important)

- **Thing:** Any physical object with a unique identity (IP or RFID) and ability to communicate.
- **IoT Device:** Hardware capable of sensing, processing, and communicating.
- **IoT System:** Complete ecosystem of devices, networks, platforms, and applications.

---

## 1.2 IoT Architectures

### Physical Design of IoT

**What it is:** The actual hardware and physical components that form an IoT system.

**Physical Components:**

```
Layer 1: Things / Devices
   └── Sensors (temperature, humidity, motion)
   └── Actuators (motor, relay, display)
   └── Microcontrollers (Arduino, ESP8266)

Layer 2: Local Network
   └── WiFi Router / Bluetooth Hub / Zigbee Gateway

Layer 3: Backend / Cloud
   └── Server, Database, Cloud Platform (AWS IoT, Azure IoT)

Layer 4: User Interface
   └── Mobile App, Dashboard, Web App
```

**Analogy:** Think of it like the human body:
- Sensors = Eyes, Ears (collect info)
- Microcontroller = Brain (process info)
- Network = Nervous System (transmit info)
- Actuator = Hands/Legs (take action)
- Cloud = Memory/Database (store info)

---

### Logical Design of IoT

**What it is:** The flow of data and decision-making in an IoT system — how information moves and what happens at each step.

**Standard 3-Layer Architecture:**

```
┌─────────────────────────────────┐
│       Application Layer         │  ← Apps, UI, Business Logic
├─────────────────────────────────┤
│        Network Layer            │  ← Internet, WiFi, 4G, Zigbee
├─────────────────────────────────┤
│       Perception Layer          │  ← Sensors, RFID, Actuators
└─────────────────────────────────┘
```

**Extended 5-Layer Architecture (Advanced):**

```
┌──────────────────────┐
│  5. Business Layer   │  → Business models, graphs, reports
├──────────────────────┤
│  4. Processing Layer │  → Cloud, big data, AI analytics
├──────────────────────┤
│  3. Middleware Layer │  → Data filtering, device management
├──────────────────────┤
│  2. Network Layer    │  → WiFi, 3G/4G, Bluetooth, Zigbee
├──────────────────────┤
│  1. Perception Layer │  → Sensors, RFID, GPS, actuators
└──────────────────────┘
```

> 📌 **Exam Tip:** You may be asked to draw the IoT architecture layers. Always include at least 3 layers: Perception, Network, and Application.

---

## 1.3 Enabling Technologies in IoT

These are the technologies that **make IoT possible**. Without these, IoT cannot work.

### 1. Wireless Sensor Networks (WSN)
- **What:** A network of small sensor nodes that wirelessly communicate.
- **How:** Each node has a sensor, a tiny processor, and a radio transmitter.
- **Use:** Forest fire detection, battlefield monitoring, industrial monitoring.

### 2. Cloud Computing
- **What:** Remote servers on the internet to store, manage, and process data.
- **Why IoT needs it:** IoT generates TB of data — local storage is not enough.
- **Examples:** AWS IoT Core, Google Cloud IoT, Microsoft Azure IoT Hub.

### 3. Big Data & Analytics
- **What:** Tools to process massive volumes of sensor data and find patterns.
- **Example:** Analyzing 10 million temperature readings to predict equipment failure.

### 4. Communication Protocols
| Protocol | Range | Speed | Power | Used For |
|---|---|---|---|---|
| **WiFi** | 50–100m | High | High | Smart Home |
| **Bluetooth/BLE** | 10–100m | Medium | Low | Wearables |
| **Zigbee** | 10–100m | Low | Very Low | Industrial |
| **LoRa** | 2–15 km | Very Low | Very Low | Agriculture |
| **NFC** | <10 cm | Low | Very Low | Payments |
| **4G/5G** | Wide | High | High | Connected Cars |
| **Z-Wave** | 30m | Low | Low | Smart Home |

### 5. Embedded Systems
- Microcontrollers (Arduino, ESP32, Raspberry Pi) that run IoT logic.

### 6. IPv6 / 6LoWPAN
- **Why:** Every IoT device needs a unique address. IPv4 had only ~4 billion addresses. IPv6 provides 340 undecillion — enough for every grain of sand on Earth!
- **6LoWPAN:** IPv6 adapted for Low-Power Wireless Personal Area Networks.

### 7. RFID (Radio Frequency Identification)
- **What:** Tags emit signals; readers pick them up to identify objects.
- **Use:** Warehouse inventory, animal tracking, passport scanning.

### 8. Middleware
- Software that sits between devices and applications. Translates different formats. Examples: MQTT broker, REST API, CoAP.

---

## 1.4 History of IoT

```
Key Milestone Timeline:

1832 → Telegraph – first electrical long-distance communication
1926 → Tesla predicts global wireless communication
1969 → ARPANET – birth of the internet
1982 → CMU Coke Machine – first internet-connected appliance
1990 → John Romkey's Internet Toaster – demonstrated at INTEROP
1991 → Mark Weiser: "Ubiquitous Computing" paper at Xerox PARC
1994 → Reza Raji describes "small data packets sent to large set of nodes"
1999 → Kevin Ashton coins "Internet of Things"
1999 → Auto-ID Center at MIT (RFID + IoT foundation)
2000 → LG Internet Digital DIOS fridge
2003–2004 → RFID deployment begins in military and retail
2005 → ITU report: "The Internet of Things"
2008 → Number of connected devices > world population
2011 → IPv6 Launch Day – solves address exhaustion problem
2013 → Google acquires Nest (Smart Thermostat) – mainstream IoT
2014 → Arduino becomes mainstream for IoT prototyping
2019 → 5G rollout begins globally
2020 → 30+ billion devices globally
2025 → Projected 75 billion devices
```

---

## 1.5 About Things in IoT

### What is a "Thing"?

A **Thing** in IoT is any physical object that:
1. Can be uniquely identified (has an ID)
2. Can sense its environment (has a sensor)
3. Can communicate (has network connectivity)
4. Can optionally take action (actuator)

### Types of Things

```
Smart Things:
├── Sensing Things     → Weather station, smoke detector
├── Actuating Things   → Smart lock, robotic arm
├── Processing Things  → Edge server, Arduino
└── Storing Things     → Local SD card, cloud buffer

Passive Things (tracked but not active):
└── RFID-tagged packages, barcoded items
```

---

## 1.6 The Identifiers in IoT

### Why Identifiers Matter
Every device in IoT needs a **unique identity** — otherwise, how would the system know WHICH device is sending data?

### Types of Identifiers

| Identifier | Full Form | Example Use |
|---|---|---|
| **IP Address** | Internet Protocol Address | Every WiFi device |
| **MAC Address** | Media Access Control | Network card identity |
| **RFID** | Radio Frequency ID | Warehouse tags |
| **EPC** | Electronic Product Code | Retail items |
| **URI/URL** | Uniform Resource Identifier | Web-connected devices |
| **IPv6** | Internet Protocol v6 | Massive scale IoT |
| **EUI-64** | 64-bit Extended Unique ID | Zigbee, 6LoWPAN |

> 🔑 **Exam Ready:** An IoT identifier must be: **Persistent, Unique, Scalable, Secure, and Resolvable.**

### How Identification Works

```
Step 1: Each IoT device is assigned a unique ID (e.g., IPv6 address)
Step 2: When device powers on, it announces itself on the network
Step 3: The gateway/server registers the device using its ID
Step 4: All data is tagged with this ID
Step 5: Application layer uses ID to route data to correct service
```

---

## 1.7 About the Internet in IoT

### How IoT Uses the Internet

The internet is the backbone of IoT — it allows data to travel from your sensor in a remote field to a data center thousands of miles away.

**Internet Stack for IoT:**

```
Application Layer  → MQTT, CoAP, HTTP, AMQP
Transport Layer    → TCP (reliable), UDP (fast)
Network Layer      → IPv4, IPv6, 6LoWPAN
Data Link Layer    → WiFi, Zigbee, Bluetooth, Ethernet
Physical Layer     → Radio waves, cables, fiber
```

### Key Protocols for IoT

| Protocol | Purpose | Where Used |
|---|---|---|
| **MQTT** | Lightweight pub/sub messaging | Most IoT devices |
| **CoAP** | Constrained Application Protocol | Low-power devices |
| **HTTP/REST** | Standard web request | Dashboard APIs |
| **WebSocket** | Real-time bidirectional | Live dashboards |
| **AMQP** | Advanced message queuing | Enterprise IoT |

---

## 1.8 IoT Frameworks

A **framework** provides the platform, tools, and protocols to build IoT applications without reinventing the wheel.

### Popular IoT Frameworks

| Framework | Provider | What it Does |
|---|---|---|
| **AWS IoT Core** | Amazon | Cloud platform for device management |
| **Azure IoT Hub** | Microsoft | Enterprise IoT backend |
| **Google Cloud IoT** | Google | ML-powered IoT analytics |
| **Arm Mbed IoT** | ARM | IoT OS for microcontrollers |
| **ThingsBoard** | Open Source | Device management + dashboard |
| **Node-RED** | IBM/OpenJS | Visual programming for IoT flows |
| **Arduino Cloud** | Arduino | Cloud platform for Arduino makers |
| **Raspberry Pi Foundation** | Open Foundation | Education-focused IoT development |

### How a Framework Works

```
Your Device (Sensor Data)
        ↓
    IoT Gateway
        ↓
  Framework SDK (e.g., AWS IoT SDK)
        ↓
  Cloud Platform (Device Registry, Rules Engine)
        ↓
  Analytics / Storage / Notification
        ↓
  Your App / Dashboard
```

---

## 1.9 IoT and M2M Communication

### What is M2M?

**M2M (Machine-to-Machine)** communication means devices talk to each other **without any human involvement**.

**Analogy:**  
Old way — A factory machine breaks → Worker notices → Worker calls technician.  
M2M way — Machine detects fault → Sends SMS to technician automatically.

### M2M vs IoT

| Feature | M2M | IoT |
|---|---|---|
| **Scope** | Point-to-point (1:1) | Many-to-many network |
| **Connectivity** | Cellular/Serial | Internet-based |
| **Intelligence** | Limited | Cloud AI-powered |
| **Scale** | Hundreds of devices | Billions of devices |
| **Standards** | Proprietary | Open (MQTT, HTTP) |
| **Data** | Operational data only | Context-rich big data |

### M2M Architecture

```
Machine A                           Machine B
(Sensor + Modem)   ←—Network—→    (Controller + Modem)
       ↑                                  ↓
  Collects Data                    Takes Action
       ↑                                  ↓
       └──── M2M Middleware Platform ─────┘
              (SIM, APN, Application Server)
```

> 📌 **Key Difference:** M2M is a **subset** / precursor of IoT. IoT is more intelligent, scalable, and internet-based.

---

[Back to top](#)

---

# UNIT II — Sensors and Networks

---

## 2.1 What is a Sensor Network?

**Definition:** A Sensor Network is a collection of sensor nodes that monitor physical or environmental conditions (like temperature, sound, pressure) and cooperatively pass data through the network to a central location.

**Analogy:** Think of it like a colony of bees. Each bee collects information (nectar/data). They communicate through dance (radio signals). Information ends up at the hive (central server).

---

## 2.2 Types of Sensors

A **sensor** converts a physical quantity into an electrical signal that can be read by a computing device.

### By Parameter Measured:

#### A. Temperature Sensors
- **LM35** – analog, 10mV per °C, used in room thermostats
- **DHT11 / DHT22** – digital, measures both temperature & humidity
- **DS18B20** – digital, waterproof, used in liquid monitoring
- **Thermocouple** – high-temperature industrial environments

#### B. Humidity Sensors
- **DHT11** – 20–90% RH, ±5% accuracy (cheap, beginner-friendly)
- **DHT22** – 0–100% RH, ±2% accuracy (more precise)
- **SHT31** – industrial-grade, I2C interface

#### C. Light Sensors
- **LDR (Light Dependent Resistor)** – resistance changes with light
- **BH1750** – digital lux meter for precise lighting control
- **Photodiode / Phototransistor** – high-speed light detection

#### D. Motion / Proximity Sensors
- **PIR (Passive Infrared)** – detects body heat movement
- **Ultrasonic (HC-SR04)** – measures distance using sound echoes
- **IR Proximity** – detects nearby objects using infrared
- **Microwave Radar (RCWL-0516)** – penetrates walls

#### E. Pressure / Force Sensors
- **BMP180 / BMP280** – barometric pressure, used in weather apps
- **FSR (Force Sensitive Resistor)** – touch/pressure detection
- **MPX5100** – gas/liquid pressure

#### F. Gas Sensors
- **MQ-2** – detects LPG, methane, propane, smoke
- **MQ-7** – carbon monoxide detection
- **MQ-135** – air quality (CO2, NH3, benzene)

#### G. Sound Sensors
- **Electret Microphone** – basic sound detection
- **MAX4466** – amplified microphone module
- **Sound Detector Module** – simple clap-detection

#### H. Accelerometer / Gyroscope
- **MPU-6050** – 6-axis (accelerometer + gyroscope), I2C
- **ADXL345** – 3-axis accelerometer
- Used in: Fall detection, robot orientation, wearables

#### I. Magnetic Field Sensors
- **Hall Effect Sensor** – speed measurement, gear counting
- **Reed Switch** – magnetic field-based switch (door open/close)

#### J. GPS / Location Sensors
- **NEO-6M GPS Module** – satellite-based location tracking
- Used in: Vehicle tracking, drone navigation

---

### How a Sensor Works (Step-by-Step)

```
Step 1: Physical World Event happens (temperature rises)
        ↓
Step 2: Transducer effect occurs (resistance changes in thermistor)
        ↓
Step 3: Electrical signal generated (voltage/current)
        ↓
Step 4: Signal Conditioning (amplification, filtering, ADC)
        ↓
Step 5: Microcontroller reads value (via analog/digital pin)
        ↓
Step 6: Data processed, displayed, or transmitted
```

---

## 2.3 Types of Actuators

**Definition:** An actuator converts an electrical signal back into a physical action. It is the "output" side of an IoT system.

| Actuator | Type | What it Does | Example |
|---|---|---|---|
| **LED** | Electrical | Emits light | Status indicator |
| **Buzzer** | Electrical | Makes sound | Alert/alarm |
| **DC Motor** | Electromechanical | Rotates continuously | Fan, conveyor belt |
| **Servo Motor** | Electromechanical | Rotates at precise angle | Robot arm, camera pan |
| **Stepper Motor** | Electromechanical | Precise step-by-step rotation | 3D printer, CNC |
| **Relay** | Electrical switch | Controls high-power devices | Smart home appliances |
| **Solenoid** | Electromagnetic | Linear push/pull motion | Door lock, valve |
| **LCD / OLED** | Display | Shows text/graphics | User interface |
| **Servo Valve** | Hydraulic | Controls fluid flow | Industrial systems |
| **Speaker** | Acoustic | Plays audio | Alerts, voice response |

---

## 2.4 IoT Development Boards

### Arduino IDE and Board Types

#### What is Arduino?
Arduino is an open-source electronics platform based on easy-to-use hardware and software. It allows you to read inputs (sensors) and turn them into outputs (actuators).

**Think of it as:** A tiny computer that executes one program (called a "sketch") repeatedly.

#### Arduino Board Variants

| Board | Processor | Pins | RAM | Flash | Best For |
|---|---|---|---|---|---|
| **Arduino UNO** | ATmega328P | 14D/6A | 2 KB | 32 KB | Learning, prototyping |
| **Arduino Mega** | ATmega2560 | 54D/16A | 8 KB | 256 KB | Complex projects |
| **Arduino Nano** | ATmega328P | 22 pins | 2 KB | 32 KB | Compact projects |
| **Arduino Leonardo** | ATmega32U4 | 20D/12A | 2.5 KB | 32 KB | USB emulation |
| **Arduino Due** | ARM Cortex-M3 | 54D/12A | 96 KB | 512 KB | High-performance |
| **Arduino MKR** | ARM Cortex-M0+ | Various | 32 KB | 256 KB | IoT + WiFi |

#### Arduino UNO – Detailed Component Overview

```
         Arduino UNO Board Layout
         
┌────────────────────────────────────────────┐
│  [USB Port]        [Power Jack]            │
│                                            │
│  Pin 13 ──● (Built-in LED)                 │
│                                            │
│  Digital Pins 0-13  (14 pins)              │
│  ├── Pins 3,5,6,9,10,11 → PWM (~)          │
│  ├── Pin 0,1 → Serial RX/TX                │
│  └── Pin 13 → LED_BUILTIN                  │
│                                            │
│  Analog Pins A0-A5  (6 pins)               │
│  └── 10-bit ADC (reads 0–1023)             │
│                                            │
│  Power Pins: 5V, 3.3V, GND, Vin            │
│                                            │
│  [RESET Button]    [ICSP Header]           │
│  ATmega328P Chip (brain of the board)      │
└────────────────────────────────────────────┘
```

#### Arduino IDE Setup (Step-by-Step)

```
Step 1: Visit arduino.cc/en/software
Step 2: Download Arduino IDE 2.x for your OS
Step 3: Install the IDE
Step 4: Connect Arduino UNO via USB
Step 5: Open IDE → Tools → Board → Arduino AVR Boards → Arduino UNO
Step 6: Tools → Port → Select COM port (Windows) or /dev/ttyUSB0 (Linux)
Step 7: Write your sketch (program)
Step 8: Click ✓ (Verify) to compile
Step 9: Click → (Upload) to flash to board
Step 10: Open Serial Monitor (Ctrl+Shift+M) to debug
```

#### Basic Arduino Sketch Structure

```cpp
// Every Arduino program has two mandatory functions:

void setup() {
  // Runs ONCE at startup
  // Used to: set pin modes, initialize serial, configure sensors
}

void loop() {
  // Runs FOREVER in a loop
  // Used to: read sensors, control outputs, send data
}
```

---

### Raspberry Pi Development Kit

#### What is Raspberry Pi?

Raspberry Pi is a **single-board computer** (not just a microcontroller). It runs a full operating system (Raspberry Pi OS, based on Linux).

**Key Difference from Arduino:**

| Feature | Arduino | Raspberry Pi |
|---|---|---|
| Type | Microcontroller | Microcomputer |
| OS | None (bare metal) | Linux (Raspberry Pi OS) |
| Language | C/C++ (Sketch) | Python, C, Java, etc. |
| RAM | 2KB – 8MB | 1GB – 8GB |
| Processing | 8/32-bit MCU | ARM Cortex 64-bit |
| GPIO Count | 14 digital + 6 analog | 40 GPIO pins |
| Networking | Optional (shields) | WiFi/Ethernet built-in |
| Cost | $25–35 | $35–75 |
| Use Case | Sensor reading, control | AI, video, web server |

#### Raspberry Pi GPIO

```
GPIO (General Purpose Input/Output) pins:
- 40 pins total
- Uses 3.3V logic (NOT 5V tolerant!)
- Supports: Digital I/O, I2C, SPI, UART, PWM
- Programming: Python with RPi.GPIO or gpiozero library
```

#### When to Use Which?

```
Use Arduino when:
→ Controlling motors/sensors directly
→ Tight timing required (real-time)
→ Low power project
→ Beginner learning electronics

Use Raspberry Pi when:
→ Need internet connectivity + processing
→ Running complex algorithms / AI
→ Web server or dashboard on the device
→ Camera or display processing
```

---

## 2.5 RFID Principles and Components

### What is RFID?

**RFID (Radio Frequency Identification)** uses radio waves to read and capture information stored on a tag attached to an object.

**Analogy:** Like a barcode but:
- No line-of-sight needed
- Can scan through walls/boxes
- Can scan multiple items at once
- Can read from meters away

### RFID System Components

```
┌─────────────┐        Radio Waves        ┌──────────┐
│  RFID Tag   │ ←───────────────────────→ │  Reader  │
│  (on item)  │                           │(antenna) │
└─────────────┘                           └────┬─────┘
                                               │
                                          ┌────▼─────┐
                                          │ Computer │
                                          │ /Database│
                                          └──────────┘
```

#### RFID Tag Types

| Type | Power Source | Range | Memory | Cost |
|---|---|---|---|---|
| **Passive** | From reader signal | Up to 10m | Small | Low |
| **Active** | Battery-powered | Up to 100m | Large | High |
| **Semi-passive** | Battery + reader | Up to 30m | Medium | Medium |

#### RFID Frequencies

| Band | Frequency | Range | Use Case |
|---|---|---|---|
| LF | 125–134 kHz | <10 cm | Animal tracking, access cards |
| HF | 13.56 MHz | <1m | NFC payments, library books |
| UHF | 860–960 MHz | 1–12m | Supply chain, retail inventory |
| Microwave | 2.45 GHz | <1m | Toll collection, parking |

#### RC522 RFID Module (Arduino-Compatible)

```
RC522 RFID Module Pins:
- SDA  → Pin 10 (Chip Select)
- SCK  → Pin 13 (Clock)
- MOSI → Pin 11 (Data to module)
- MISO → Pin 12 (Data from module)
- IRQ  → Not used
- GND  → GND
- RST  → Pin 9
- 3.3V → 3.3V
```

---

## 2.6 Wireless Sensor Networks (WSN)

### History and Context

```
1980s → Military DARPA research on distributed sensors
1990s → Academic research on ad-hoc networks
1998 → Jan Rabaey: PicoRadio – ultra-low power WSN nodes
1999 → Kris Pister: "Smart Dust" – mote-sized sensor nodes
2000s → Commercial WSN products: Crossbow, Dust Networks
2010s → WSN merged with IoT infrastructure
```

### WSN Architecture

```
       Sensor Field
       
   [Node]   [Node]   [Node]    ← Sense environment
       \       |       /
        \      |      /
         [Cluster Head]         ← Aggregates data
              |
         [Gateway]             ← Connects to internet
              |
         [Base Station]        ← Central data collection
              |
      [Internet/Cloud]         ← Data processing & storage
```

### The Node – Anatomy of a Sensor Node

```
A WSN Node contains:
┌─────────────────────────────┐
│  Sensing Unit               │  → Sensor + ADC
│  Processing Unit            │  → Microcontroller (MCU)
│  Communication Unit         │  → Radio Transceiver
│  Power Unit                 │  → Battery / Harvesting
└─────────────────────────────┘

Key Design Constraints:
- Must use minimal power (months/years on battery)
- Must be small and cheap
- Must self-organize into a network
- Must handle lossy wireless communication
```

### Connecting Nodes (WSN Topologies)

```
Star Topology:              Mesh Topology:
Each node → Gateway         Nodes relay each other's data
     [N]                    [N]─[N]─[N]
    / | \                    |   |   |
[G][G][G]                   [N]─[N]─[N]
  Gateway                   (Self-healing)

Tree Topology:              Cluster Topology:
Hierarchical                [N][N] → [CH] ─┐
   Gateway                  [N][N] → [CH] ─┤→ Gateway
    / | \                   [N][N] → [CH] ─┘
  [N] [N] [N]              CH = Cluster Head
```

### Networking Nodes – WSN Protocols

| Protocol | Standard | Range | Power | Use Case |
|---|---|---|---|---|
| **Zigbee** | IEEE 802.15.4 | 10–100m | Ultra Low | Smart home, industrial |
| **Z-Wave** | Proprietary | 30m | Low | Home automation |
| **Bluetooth LE** | IEEE 802.15.1 | 10–100m | Very Low | Wearables |
| **LoRaWAN** | LoRa Alliance | 2–15km | Very Low | Agriculture, smart city |
| **6LoWPAN** | IETF RFC 4944 | 10–100m | Low | IPv6 IoT networks |
| **Thread** | Thread Group | 10–100m | Low | Google Home ecosystem |

### WSN and IoT – The Relationship

```
WSN provides the "nervous system" of IoT:

Physical World
      ↓ (sensing)
WSN Nodes (temperature, humidity, motion, etc.)
      ↓ (multi-hop wireless communication)
WSN Gateway
      ↓ (IP routing)
IoT Platform (Cloud)
      ↓ (analytics + AI)
Decision / Action / Alert
```

> 📌 **Exam Key:** WSN is the **sensing infrastructure** of IoT. IoT adds cloud, analytics, and application layers on top of WSN.

---

[Back to top](#)

---

# UNIT III — Data Handling & Analytics

---

## 3.1 Introduction

When thousands of IoT sensors collect data 24/7, you get an unimaginable volume of data. This unit covers **how that data is managed, stored, and turned into useful insights.**

### IoT Data Flow (Big Picture)

```
┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────┐
│ Sensors  │──▶│  Edge    │──▶│ Gateway  │──▶│  Cloud   │──▶│Analytics │
│(Generate │    │Computing │    │(Protocol │    │(Storage  │    │(Insights)│
│  Data)   │    │(Filter)  │    │ Bridge)  │    │  + AI)   │    │          │
└──────────┘    └──────────┘    └──────────┘    └──────────┘    └──────────┘
     Raw Data →  Pre-processed →  Transmitted →   Stored     →  Actionable
```

---

## 3.2 Big Data

### What is Big Data?

**Simple Explanation:** When your data is so massive, so fast, and so varied that traditional databases simply can't handle it.

**Example:** A smart city with 1 million sensors, each sending 1 data point every second = 86.4 billion data points per day!

### The 5 V's of Big Data

| V | What It Means | IoT Example |
|---|---|---|
| **Volume** | Enormous quantity of data | TB/day from city sensors |
| **Velocity** | Data generated very fast | 1000 readings/second |
| **Variety** | Different types (text, image, sensor) | Temperature + video + GPS |
| **Veracity** | Trustworthiness / accuracy | Faulty sensor = bad data |
| **Value** | Usefulness of data | Predicting equipment failure |

---

## 3.3 Types of Data in IoT

| Data Type | Description | Example |
|---|---|---|
| **Structured** | Tables, rows, columns | Temperature logs in CSV |
| **Unstructured** | No fixed format | Security camera video |
| **Semi-structured** | Has some structure | JSON sensor payload |
| **Time-series** | Indexed by timestamp | Heart rate over time |
| **Geospatial** | Location-based | GPS tracks of delivery truck |
| **Streaming** | Continuous real-time | Live stock price feed |

---

## 3.4 Characteristics of Big Data (IoT Context)

1. **Continuous generation** – Data never stops flowing
2. **Distributed sources** – Data from many different devices
3. **Heterogeneous formats** – JSON, XML, binary, CSV, video
4. **Temporal nature** – Timestamp matters (time-series)
5. **Context-dependence** – Same value means different things in different contexts
6. **Noise and outliers** – Sensor errors, signal interference
7. **Correlation required** – Meaning comes from combining multiple streams

---

## 3.5 Data Handling Technologies

### Tools for Managing IoT Data

| Technology | Type | Purpose |
|---|---|---|
| **MQTT Broker** | Protocol | Lightweight pub/sub messaging |
| **Apache Kafka** | Streaming | High-throughput real-time ingestion |
| **InfluxDB** | Time-series DB | Optimized for sensor time-series |
| **MongoDB** | NoSQL | Flexible JSON document storage |
| **MySQL / PostgreSQL** | SQL DB | Structured data storage |
| **Redis** | In-memory cache | Ultra-fast temporary storage |
| **Apache Spark** | Processing | Distributed big data processing |
| **Elasticsearch** | Search | Searching large datasets |

---

## 3.6 Flow of Data in IoT

### The Complete Data Journey

```
Step 1 — Generation:
Sensor detects environmental change
→ Example: Temperature rises to 35°C

Step 2 — Collection:
Microcontroller reads sensor value
→ ADC converts analog → digital

Step 3 — Pre-processing (Edge):
Filter noise, average readings, detect anomalies locally
→ Example: Discard readings outside valid range

Step 4 — Transmission:
Data packet sent via protocol (MQTT/HTTP)
Format: {"device": "sensor01", "temp": 35.2, "time": 1718000000}

Step 5 — Reception:
Cloud/server receives data
→ IoT Platform (AWS IoT / Azure IoT Hub) receives MQTT message

Step 6 — Storage:
Data stored in time-series database (InfluxDB)
→ Indexed by timestamp for fast retrieval

Step 7 — Processing:
Analytics engine analyzes patterns
→ "Temperature rising trend for 3 hours"

Step 8 — Decision:
AI/rule engine triggers action
→ Send alert: "Temperature critical! Check cooling system"

Step 9 — Action:
Actuator commanded: Turn on cooling fan
→ Feedback loop complete
```

---

## 3.7 Data Acquisition

**Data Acquisition (DAQ)** is the process of **sampling real-world signals** and converting them into digital formats a computer can work with.

### DAQ System Components

```
Physical Signal (temperature, pressure, motion)
         ↓
    Sensors / Transducers     → Convert to electrical signal
         ↓
    Signal Conditioning       → Amplify, filter, isolate
         ↓
    ADC (Analog-to-Digital)   → Convert analog → digital
         ↓
    Microcontroller / DAQ Board → Process and store
         ↓
    Data Storage / Transmission → Cloud, SD card, serial
```

### Sampling Rate (Nyquist Theorem)

> **Rule:** Sample at least **twice the highest frequency** of the signal you want to capture.

- Measuring temperature (changes slowly) → Sample every 5 seconds is fine
- Measuring vibration (changes fast) → Need 1000+ samples/second

---

## 3.8 Data Storage in IoT

### Storage Options

| Storage Type | Location | Speed | Capacity | When to Use |
|---|---|---|---|---|
| **Local (SD card)** | On device | Fast | Limited | Offline, backup |
| **Edge Storage** | Gateway | Fast | Medium | Pre-filtered data |
| **Cloud Storage** | Remote server | Network-dependent | Unlimited | Long-term analytics |
| **In-memory (RAM)** | Device RAM | Very Fast | Tiny | Temporary buffer |
| **Time-Series DB** | Cloud | Fast | Scalable | Sensor history |

### Time-Series Database (Most Important for IoT)

A **time-series database** is optimized for data that changes over time:
- Each record has a **timestamp**
- Queries are time-based ("show me last 24 hours of temperature")
- Efficient compression for repeated data
- Examples: **InfluxDB, TimescaleDB, OpenTSDB**

---

## 3.9 Introduction to Hadoop

### What is Hadoop?

**Apache Hadoop** is an open-source framework for storing and processing massive datasets across clusters of computers.

**Analogy:** Instead of one super-powerful computer, Hadoop uses 1000 cheap computers working together.

### Hadoop Core Components

```
┌──────────────────────────────────────────┐
│                 HADOOP                   │
├─────────────────┬────────────────────────┤
│   HDFS          │    MapReduce           │
│ (Storage)       │    (Processing)        │
│                 │                        │
│ Stores data     │ Map: Split problem     │
│ across many     │ Reduce: Combine results│
│ machines        │                        │
└─────────────────┴────────────────────────┘
       YARN (Resource Management)
```

#### HDFS (Hadoop Distributed File System)
- Files split into 128MB **blocks**
- Each block replicated 3 times on different machines
- Fault-tolerant: If one machine fails, data still available

#### MapReduce
- **Map phase:** Break big problem into small tasks, process in parallel
- **Reduce phase:** Combine results from all Map tasks

**IoT Example:**  
1 million sensors send 1 temperature reading/minute.  
→ MapReduce calculates average by city, by hour, in minutes.

### Hadoop Ecosystem for IoT

| Tool | Purpose |
|---|---|
| **HDFS** | Distributed file storage |
| **MapReduce** | Batch data processing |
| **Hive** | SQL queries on Hadoop |
| **Pig** | Data transformation scripting |
| **HBase** | Real-time read/write column database |
| **Spark** | Faster in-memory processing (replaces MR) |
| **Kafka** | Real-time streaming into Hadoop |
| **Flume** | Data ingestion from logs/sensors |

---

## 3.10 Introduction to Data Analytics

**Data Analytics** = Finding patterns, trends, and meaning in raw data.

### Why IoT Needs Analytics

Raw data from sensors is useless by itself:
- "35.2°C" means nothing alone
- But "Temperature rising 0.5°C per hour for 8 hours" = machine overheating warning!

---

## 3.11 Types of Data Analytics

| Type | Question Answered | Complexity | Value |
|---|---|---|---|
| **Descriptive** | "What happened?" | Low | Lowest |
| **Diagnostic** | "Why did it happen?" | Medium | Medium |
| **Predictive** | "What will happen?" | High | High |
| **Prescriptive** | "What should we do?" | Highest | Highest |

### Detailed Explanation

#### 1. Descriptive Analytics
- **Purpose:** Summarize past data
- **Techniques:** Averages, counts, charts, dashboards
- **IoT Example:** "Average temperature in warehouse last 30 days = 22°C"

#### 2. Diagnostic Analytics
- **Purpose:** Find root cause of an issue
- **Techniques:** Drill-down, correlation analysis
- **IoT Example:** "Temperature spike on Day 12 correlates with AC failure"

#### 3. Predictive Analytics
- **Purpose:** Forecast future outcomes
- **Techniques:** Machine Learning, regression, time series forecasting
- **IoT Example:** "Bearing vibration pattern indicates failure in 72 hours"

#### 4. Prescriptive Analytics
- **Purpose:** Recommend the best action
- **Techniques:** Optimization algorithms, AI decision engines
- **IoT Example:** "Schedule maintenance for Machine 3 between 2–4 AM on Friday"

---

## 3.12 Local Analytics

**Local Analytics = Processing data ON the device or gateway** before sending to cloud.

Also called: **Edge Analytics** or **Fog Computing**

### Why Local Analytics?

```
Without Local Analytics:
Sensor → [Raw Data] → Cloud → [Analyze] → [Respond]
Latency: 200–500ms (too slow for safety-critical apps!)

With Local Analytics:
Sensor → [Analyze Locally] → [Respond Instantly]
Latency: <10ms (safe for real-time control!)
```

**Benefits:**
- Low latency response (critical for industrial safety)
- Reduced bandwidth (only send important data to cloud)
- Works offline (no internet dependency)
- Privacy (sensitive data never leaves the building)

**Examples:**
- Smart camera detecting motion locally → only sends clip when motion found
- Industrial sensor detecting anomaly → immediately shuts down machine

---

## 3.13 Cloud Analytics and Applications

**Cloud Analytics = Processing data in powerful remote servers** using AI/ML at massive scale.

### Cloud Analytics Pipeline

```
IoT Devices
    ↓ (MQTT/HTTP)
IoT Hub / Message Broker
    ↓
Stream Processing (Apache Kafka / Azure Stream Analytics)
    ↓
Storage (Data Lake / Time-Series DB)
    ↓
Batch Analytics (Apache Spark / Hadoop)
    ↓
ML Models (TensorFlow / SageMaker)
    ↓
Dashboards / Alerts / APIs
    ↓
Business Action
```

### Major Cloud IoT Analytics Platforms

| Platform | Key Service | AI/ML Feature |
|---|---|---|
| **AWS IoT** | IoT Core + Kinesis | SageMaker ML |
| **Azure IoT** | IoT Hub + Stream Analytics | Azure ML + Cognitive |
| **Google Cloud IoT** | Cloud IoT Core + Pub/Sub | BigQuery ML |
| **IBM Watson IoT** | Watson IoT Platform | Watson AI |
| **Siemens MindSphere** | Industrial IoT | Predictive Maintenance |

### Cloud Analytics Use Cases in IoT

- 🔮 **Predictive Maintenance** – ML predicts machine failure before it happens
- 🌡️ **Energy Optimization** – AI adjusts HVAC based on occupancy patterns
- 🚗 **Fleet Management** – Analyze millions of GPS points for route optimization
- 🏥 **Patient Monitoring** – Cloud ML alerts doctor about abnormal vitals
- 🛒 **Retail Analytics** – Track customer movement patterns in-store

---

[Back to top](#)

---

# UNIT IV — Applications of IoT

---

## 4.1 Home Automation (Smart Home)

### What It Is
A network of interconnected devices in a home that can be controlled remotely, automated, and optimized to improve comfort, security, and energy efficiency.

### Key Components of Smart Home

```
┌─────────────────────────────────────────────────────┐
│                    SMART HOME                       │
│                                                     │
│  💡 Smart Lighting    🌡️ Smart Thermostat           │
│  🔒 Smart Locks       📷 Security Cameras           │
│  🔌 Smart Plugs       🔊 Smart Speakers             │
│  🤖 Robotic Vacuum    🍳 Smart Appliances           │
│                                                     │
│  All connected via: WiFi / Zigbee / Z-Wave          │
│  Controlled by: Mobile App / Voice Assistant        │
└─────────────────────────────────────────────────────┘
```

### Technologies Used
- **Protocols:** Zigbee, Z-Wave, WiFi, Bluetooth, Thread/Matter
- **Hubs:** Amazon Echo, Google Nest Hub, Samsung SmartThings
- **Voice:** Alexa, Google Assistant, Siri
- **Standard:** Matter (unified smart home standard since 2022)

### Real-World Case Study
> **Google Nest Thermostat:** Learns your temperature preferences over 1 week. Automatically adjusts heating/cooling. Detects when you leave home (geofencing) and saves energy. Users report 10–12% savings on heating bills and 15% on cooling bills.

---

## 4.2 Smart Cities

### What It Is
Using IoT to make cities more efficient, safer, and sustainable by connecting infrastructure, services, and citizens.

### Smart City Domains

| Domain | IoT Application | Benefit |
|---|---|---|
| **Traffic** | Smart signals, congestion sensors | Reduce travel time 25% |
| **Parking** | Underground sensors, apps | Find parking in seconds |
| **Waste** | Smart bins with fill sensors | Only collect when full |
| **Lighting** | Adaptive street lights | Save 50% energy |
| **Water** | Leak detection sensors | Reduce water loss |
| **Safety** | Gunshot detection, surveillance | Faster emergency response |
| **Air Quality** | PM2.5 sensors across city | Real-time pollution maps |
| **Transit** | Real-time bus/train tracking | Optimized schedules |

### Real-World Case Study
> **Songdo, South Korea:** World's first purpose-built smart city. Pneumatic waste tubes replace garbage trucks. 70% of surface dedicated to green space with IoT monitoring. Sensors in roads track traffic and adjust signals automatically. Buildings share energy based on demand.

---

## 4.3 Energy Management (IoT in Energy)

### Smart Grid

**Smart Grid** = Electric power grid + IoT sensors + two-way communication

```
Traditional Grid:         Smart Grid:
Power Plant → Consumers   Power Plant ↔ Consumers ↔ Solar/Wind
(One-way)                 (Two-way with real-time control)
```

### IoT Energy Applications
- **Smart Meters** – Real-time consumption monitoring, TOU pricing
- **Demand Response** – Auto adjust load during peak hours
- **Solar Integration** – Predict and balance solar output
- **EV Charging Management** – Smart charging during off-peak hours
- **Industrial Energy Monitoring** – Per-machine energy tracking

### Real-World Example
> **Tesla Virtual Power Plant (SA, Australia):** 50,000+ solar + Powerwall homes connected as a single IoT-controlled virtual power plant. Automatically provides grid support during peak demand.

---

## 4.4 Retail Management

### IoT in Retail

| Application | What It Does |
|---|---|
| **RFID Inventory** | Real-time stock tracking |
| **Smart Shelves** | Alert when items run low |
| **Customer Analytics** | Track movement in store |
| **Smart Checkout** | Amazon Go – no cashier needed |
| **Cold Chain Monitoring** | Ensure temperature for perishables |
| **Digital Price Tags** | Change prices remotely |
| **Loss Prevention** | RFID + camera AI |

### Amazon Go: Case Study
> Uses computer vision + sensor fusion + RFID. Customers scan phone to enter, pick items, and just walk out. AI tracks what you took and charges your Amazon account.

---

## 4.5 Logistics & Supply Chain

### IoT in Logistics

```
Manufacturer → Warehouse → Distribution → Retail → Consumer
     ↑              ↑            ↑           ↑          ↑
  IoT Tags      IoT Sensors   GPS Trucks   RFID      Delivery
 (Asset ID)    (Temp/Humidity) (Location)  (Stock)   (Confirm)
```

### Key Applications
- **Asset Tracking** – Real-time GPS location of shipments
- **Cold Chain** – Temperature + humidity logging for pharma/food
- **Fleet Management** – Driver behavior, fuel efficiency, routing
- **Predictive Maintenance** – Truck sensor data predicts breakdowns
- **Port Automation** – IoT-guided cranes and AGVs

---

## 4.6 Agriculture (Smart Farming / Precision Agriculture)

### IoT Transforms Farming

**Traditional Farming:** Farmer guesses when to water, fertilize, harvest.  
**Smart Farming:** Sensors provide exact data → AI gives precise recommendations.

### IoT Agriculture Systems

```
┌─────────────────────────────────────────────────────┐
│              SMART FARM ARCHITECTURE                │
│                                                     │
│  🌱 Soil Sensors     → NPK, moisture, pH            │
│  🌦️ Weather Station  → Rain, temp, humidity, wind   │
│  🐄 Animal Wearables → Health, location, activity   │
│  🚜 GPS Tractors     → Auto-steer, variable rate    │
│  🛸 Drones           → Crop surveillance, spraying  │
│  💧 Irrigation       → Auto water based on need     │
│  🏚️ Greenhouse       → Auto climate control         │
│                                                     │
│  All connected → Farm Management Software           │
└─────────────────────────────────────────────────────┘
```

### Case Study – John Deere
> John Deere's Operations Center connects GPS tractors, yield monitors, and soil sensors. Farmers see real-time field maps. Variable rate seeding adjusts per GPS zone based on soil data. Result: 15–20% yield increase, 10–15% input cost reduction.

---

## 4.7 Health and Lifestyle (IoT in Healthcare)

### IoT Healthcare Applications

| Application | Device/Technology | Benefit |
|---|---|---|
| **Remote Patient Monitoring** | Smart ECG patch, oximeter | Hospital at home |
| **Medication Management** | Smart pill dispenser | Prevent missed doses |
| **Elderly Care** | Fall detection sensors | Faster emergency response |
| **Wearable Health** | Smartwatch, fitness band | Continuous vitals |
| **Smart Hospital** | RFID patient tracking | Reduce wait times |
| **Surgical Robots** | IoT-connected medical devices | Precision surgery |
| **Rehabilitation** | IoT exoskeleton | Remote physio |
| **Mental Health** | Mood tracking wearables | Early intervention |

### Case Study – AliveCor KardiaMobile
> A credit-card-sized ECG device. Patient holds it for 30 seconds. AI analyzes ECG instantly on phone. Detects Afib (atrial fibrillation) with 99% sensitivity. Alerts patient and sends PDF to doctor.

---

## 4.8 Industrial IoT (IIoT)

### What is IIoT?

**IIoT (Industrial Internet of Things)** applies IoT in manufacturing, energy, logistics, and heavy industry environments.

### Key Industrial Applications

1. **Predictive Maintenance** – Sensors detect vibration, heat, wear → predict failure
2. **Asset Tracking** – Know where every tool, vehicle is in real-time
3. **Quality Control** – Camera AI rejects defective parts instantly
4. **Digital Twin** – Virtual replica of machine/factory for simulation
5. **Worker Safety** – Wearables detect gas exposure, fatigue, falls
6. **Automated Guided Vehicles (AGVs)** – LiDAR + IoT material handling

### Purdue Model for Industrial IoT Security

```
Level 4: Business Planning  (ERP, MES)
Level 3: Operations         (SCADA, Historian)
Level 2: Control            (DCS, PLC)
Level 1: Sensing/Actuation  (Sensors, Actuators)
Level 0: Physical Process   (Actual machines)
```

### Industry 4.0 – The 4th Industrial Revolution

```
1st: Steam Engine (1760s)
2nd: Electricity (1870s)
3rd: Computers & Automation (1960s)
4th: IoT + AI + Big Data + Cyber-Physical Systems (NOW)
```

---

## 4.9 IoT in Environmental Protection

### Applications

| Environmental Issue | IoT Solution |
|---|---|
| **Air Pollution** | PM2.5/PM10 sensor networks in cities |
| **Water Quality** | pH, turbidity, heavy metal sensors in rivers |
| **Deforestation** | Acoustic sensors detect chainsaw sounds in forests |
| **Wildlife** | GPS collars on endangered animals |
| **Climate** | Ocean buoys monitoring sea temperature |
| **Earthquake** | MEMS accelerometer sensor networks |
| **Flood** | River level sensors + early warning systems |

### Case Study – Rainforest Connection (RFCx)
> Repurposed old Android phones mounted in trees. Detects chainsaw & gunshot sounds with AI. Alerts forest rangers within 25 minutes. Covers 1000+ acres of forest per device.

---

## 4.10 Legal Challenges in IoT

### Privacy Issues

- Continuous collection of personal data (home behavior, health, location)
- Data sold to third parties without clear consent
- Lack of transparency about what is collected

### Security Vulnerabilities

- Default passwords never changed by users
- Rarely updated firmware (security patches)
- Mirai Botnet (2016): 600,000 IoT devices hijacked → largest DDoS attack ever

### Regulatory Frameworks

| Regulation | Region | Focus |
|---|---|---|
| **GDPR** | EU | Data privacy and consent |
| **CCPA** | California, USA | Consumer data rights |
| **IoT Cybersecurity Act** | USA | Federal IoT standards |
| **NIS2 Directive** | EU | Critical infrastructure security |
| **India PDPB** | India | Personal Data Protection Bill |

---

## 4.11 IoT Design Ethics

### Ethical Principles for IoT

1. **Privacy by Design** – Build privacy in from the start, not as afterthought
2. **Informed Consent** – Users must know exactly what is collected
3. **Data Minimization** – Collect only what is necessary
4. **Transparency** – Open algorithms and data usage policies
5. **Accountability** – Clear responsibility for breaches
6. **Non-Maleficence** – IoT must not harm users
7. **Fairness** – AI models must not discriminate
8. **Sustainability** – Consider e-waste and energy impact

### Key Ethical Dilemmas

```
Scenario 1: Smart Home Surveillance
Your smart speaker records conversations "for voice activation"
→ Who owns this data? Can it be subpoenaed in court?

Scenario 2: Insurance Company Smart Meter
IoT shows you watch TV all night → Health insurance rate increases
→ Is this discrimination?

Scenario 3: Autonomous Vehicle
Emergency: hit wall or hit pedestrian?
→ Who programmed the ethics?
```

---

[Back to top](#)

---

# Practical Lab MJ DSE-2P Arduino Lab

> **Credits: 01** | Each experiment follows a consistent format.
>
> ⚠️ **Important:** Code sections below contain **comment-guided frameworks only**. You must use your knowledge and fill in the actual code. This is how real engineers learn!

---

## Lab Experiments Index

Each experiment folder contains a full **README**, a **guide.ino** (comment-only hints), and a **program.ino** (complete working code).

| # | Experiment | Folder |
|---|---|---|
| 01 | Understanding Arduino UNO Board and Components | [Exp\_01\_Arduino\_UNO\_Board](Practicals/Exp_01_Arduino_UNO_Board/README.md) |
| 02 | Installing and Working with Arduino IDE | [Exp\_02\_Arduino\_IDE](Practicals/Exp_02_Arduino_IDE/README.md) |
| 03 | Blinking LED Sketch with Arduino | [Exp\_03\_LED\_Blink](Practicals/Exp_03_LED_Blink/README.md) |
| 04 | Simulation of 4-Way Traffic Light with Arduino | [Exp\_04\_Traffic\_Light](Practicals/Exp_04_Traffic_Light/README.md) |
| 05 | Ultrasonic Sensor Handling with Arduino | [Exp\_05\_Ultrasonic\_Sensor](Practicals/Exp_05_Ultrasonic_Sensor/README.md) |
| 06 | Servo Motor and Stepper Motor Handling | [Exp\_06\_Servo\_Stepper](Practicals/Exp_06_Servo_Stepper/README.md) |
| 07 | Different Sensors for Smart Home using Arduino | [Exp\_07\_Smart\_Home\_Sensors](Practicals/Exp_07_Smart_Home_Sensors/README.md) |
| 08 | Spinning a DC Motor and Motor Speed Control | [Exp\_08\_DC\_Motor\_Control](Practicals/Exp_08_DC_Motor_Control/README.md) |
| 09 | Working with Shields | [Exp\_09\_Shields](Practicals/Exp_09_Shields/README.md) |
| 10 | Interfacing Arduino with Cloud | [Exp\_10\_Cloud\_Interface](Practicals/Exp_10_Cloud_Interface/README.md) |

---

## 🧪 Experiment 1: Understanding Arduino UNO Board and Components

### 1. Objective

To study and understand all components of the Arduino UNO board, their location, function, and electrical specifications.

### 2. Components Required

| Component | Quantity | Purpose |
|---|---|---|
| Arduino UNO Board | 1 | Main development board |
| USB Type-B Cable | 1 | Power and programming |
| Computer with Arduino IDE | 1 | Development environment |
| Multimeter (optional) | 1 | Verify voltages |

### 3. Theory

The Arduino UNO uses the **ATmega328P** microcontroller, an 8-bit AVR chip.

**Key Specifications:**
- Operating Voltage: 5V
- Input Voltage: 7–12V (recommended)
- Digital I/O Pins: 14 (6 with PWM)
- Analog Input Pins: 6 (10-bit ADC → 0 to 1023)
- Flash Memory: 32KB (0.5KB used by bootloader)
- SRAM: 2KB (runtime memory)
- EEPROM: 1KB (non-volatile storage)
- Clock Speed: 16 MHz

**Pin Types:**
- **Digital pins:** HIGH (5V) or LOW (0V) only
- **Analog pins (A0–A5):** Reads 0-5V and maps to 0-1023
- **PWM pins (~):** Simulate analog output using pulse width
- **I2C:** SDA (A4), SCL (A5) – for sensors like LCD, MPU6050
- **SPI:** MOSI(11), MISO(12), SCK(13), SS(10) – for SD card, RFID

### 4. Circuit Description

```
No external circuit needed for this experiment.

Study the board layout:

TOP of board:
  ← DIGITAL PINS (0-13) including PWM (3,5,6,9,10,11) →

                    [Arduino UNO]
                    
  ← ANALOG PINS (A0-A5) | POWER (3.3V, 5V, GND, Vin) →

BOTTOM of board:
  Chip: ATmega328P
  Crystal: 16 MHz oscillator
  Voltage regulator: 5V from barrel jack
```

### 5. Algorithm / Steps

```
Step 1: Observe the board physically
Step 2: Identify the USB port (Type-B)
Step 3: Locate digital pins 0–13 (note ~ symbols for PWM)
Step 4: Locate analog pins A0–A5
Step 5: Identify power header: 5V, 3.3V, GND, Vin
Step 6: Find the RESET button
Step 7: Identify the ATmega328P chip
Step 8: Locate the 16MHz crystal oscillator
Step 9: Find TX/RX LEDs (communication indicators)
Step 10: Locate the built-in LED on Pin 13
```

### 6. Code Section

```cpp id="iot001"
// Experiment 1: Arduino UNO Exploration
// This sketch helps you understand pin behavior

// Step 1: Define variables to identify board specs
// Hint: Use comments to document what each pin does

// Step 2: In setup(), initialize Serial communication
// Hint: What baud rate is standard? (look up Serial.begin())

// Step 3: Print a "Board Information Report" to Serial Monitor
// Hint: Use Serial.println() to display:
//   - Board name
//   - Clock speed
//   - Number of digital pins
//   - Number of analog pins

// Step 4: Set pin 13 (LED) as OUTPUT
// Hint: Use pinMode(pin, mode)

// Step 5: In loop(), blink the built-in LED
// Hint: Use digitalWrite(pin, HIGH/LOW) and delay()

// Step 6: Print current loop count to Serial Monitor
// Step 7: Observe TX LED blink when data is sent serially

// CHALLENGE:
// Read analog pin A0 and print its value (leave A0 unconnected)
// What value does a floating pin give? Why?
```

### 7. Output Explanation

- Built-in LED on Pin 13 should blink
- Serial Monitor should show board information
- TX LED flickers when serial data is transmitted
- Floating pin on A0 should show random values (explanation of noise)

---

## 🧪 Experiment 2: Installing and Working with Arduino IDE

### 1. Objective

To install Arduino IDE 2.x, configure it for Arduino UNO, and write and upload a basic test sketch.

### 2. Components Required

| Component | Quantity |
|---|---|
| Computer (Windows/Linux/Mac) | 1 |
| Arduino UNO | 1 |
| USB Type-B Cable | 1 |

### 3. Theory

The **Arduino IDE (Integrated Development Environment)** is the software tool used to write, compile, and upload programs (called "sketches") to Arduino boards. Sketches are written in a simplified version of C++.

**Compilation Process:**
```
Your Code (.ino)
      ↓ (Compile with avr-gcc)
Machine Code (HEX file)
      ↓ (Upload via avrdude)
ATmega328P Flash Memory
      ↓ (Bootloader runs your sketch)
Program Executes
```

### 4. Circuit Description

```
No external circuit needed.
Just connect Arduino UNO to computer via USB.

USB Connection:
Computer USB-A ─── Cable ─── Arduino USB-B Port

Power indicator LED should light up immediately.
```

### 5. Algorithm / Steps

```
Step 1: Open browser → go to https://arduino.cc/en/software
Step 2: Download Arduino IDE 2.x for your OS
Step 3: Install (Linux: chmod +x the AppImage, then run)
Step 4: Launch Arduino IDE
Step 5: Connect Arduino via USB
Step 6: Go to Tools → Board → Arduino AVR Boards → Arduino UNO
Step 7: Go to Tools → Port → Select correct COM/tty port
Step 8: Go to File → Examples → 01.Basics → Blink
Step 9: Click Verify (✓) – watch for "Done compiling"
Step 10: Click Upload (→) – watch for "Done uploading"
Step 11: Observe Pin 13 LED blinking on board
Step 12: Open Serial Monitor → set baud rate → observe output
```

### 6. Code Section

```cpp id="iot002"
// Experiment 2: First Arduino Sketch - IDE Familiarization

// Step 1: At the top, write a comment block with:
//   - Experiment number and name
//   - Your name, roll number, date
//   - Brief description of what this sketch does

// Step 2: Define a constant for the LED pin
// Why use a constant? (hint: easy to change pin later)
// Hint: const int LED_PIN = ?;

// Step 3: setup() function
// - Initialize Serial at 9600 baud
// - Set LED_PIN as output
// - Print "Arduino IDE Test - Ready!" to serial

// Step 4: loop() function
// - Turn LED ON using digitalWrite()
// - Print "LED is ON" to Serial Monitor
// - Wait 1 second (hint: delay(1000))
// - Turn LED OFF
// - Print "LED is OFF"
// - Wait 1 second

// Step 5: OBSERVE in Serial Monitor:
// Does the print match the LED state?
// What happens if you change delay to 500?

// BONUS CHALLENGE:
// Add a counter variable that increments each loop
// Print: "Loop #X: LED is ON/OFF"
```

### 7. Output Explanation

- LED blinks at 1-second intervals
- Serial Monitor displays ON/OFF messages in sync with LED
- The upload process shows progress bar and success message

---

## 🧪 Experiment 3: Blinking LED Sketch with Arduino

### 1. Objective

To understand digital output by making an external LED blink with configurable timing using Arduino.

### 2. Components Required

| Component | Quantity | Specification |
|---|---|---|
| Arduino UNO | 1 | — |
| LED | 1 | Red/Green/Yellow |
| Resistor | 1 | 220Ω (red-red-brown) |
| Breadboard | 1 | — |
| Jumper Wires | 3 | M-M |

### 3. Theory

**LED = Light Emitting Diode**  
- It is a **polarized** component (has + and – direction)
- **Anode (+):** Longer leg → connects to positive (through resistor)
- **Cathode (−):** Shorter leg → connects to GND

**Why the 220Ω Resistor?**
```
Ohm's Law: V = I × R

Arduino 5V output, LED voltage drop ≈ 2V, max LED current = 20mA

R = (V_supply - V_LED) / I_desired
R = (5V - 2V) / 0.02A
R = 3V / 0.02A
R = 150Ω → Use 220Ω (standard, safe value)
```
Without resistor → LED burns immediately! Always use a resistor!

### 4. Circuit Description

```
Circuit Diagram (Text):

Arduino Pin 13 ──── [220Ω Resistor] ──── [LED Anode (+)] ──── [LED Cathode (−)] ──── Arduino GND

Breadboard Setup:
Row 1:  Arduino Pin 13 wire → Column A, Row 5
Row 5:  Resistor: A5 to E5
Row 5:  LED Anode: F5 (long leg)
Row 5:  LED Cathode: G5 (short leg)
Row 5:  Wire: H5 to GND rail
Power:  GND rail → Arduino GND

Current path: Pin13 → Resistor → LED(+) → LED(-) → GND
```

### 5. Algorithm / Steps

```
Step 1: Setup breadboard
Step 2: Insert LED into breadboard (note polarity!)
Step 3: Add resistor between Arduino pin 13 and LED anode
Step 4: Connect LED cathode to GND
Step 5: Connect 5V from Arduino to power rail (optional)
Step 6: Connect GND from Arduino to ground rail
Step 7: Open Arduino IDE
Step 8: Write the sketch (see code section)
Step 9: Set pin 13 as OUTPUT in setup()
Step 10: In loop() – turn ON → delay → turn OFF → delay
Step 11: Upload and verify LED blinks correctly
Step 12: Modify delay values and observe effect
```

### 6. Code Section

```cpp id="iot003"
// Experiment 3: External LED Blink
// Objective: Control external LED with variable timing

// Step 1: Define constants
// - LED pin number (try different pins!)
// - ON time duration in milliseconds
// - OFF time duration in milliseconds

// Step 2: Declare a counter variable (int type)

// Step 3: setup() function
// - Set LED pin as OUTPUT (pinMode)
// - Initialize Serial at 9600 baud
// - Print header: "LED Blink Experiment Started"

// Step 4: loop() function
// - Increment counter by 1 each iteration
// - Turn LED ON (HIGH)
// - Print: "Blink #X: ON for Y ms"
// - Delay for ON duration

// - Turn LED OFF (LOW)
// - Print: "Blink #X: OFF for Y ms"
// - Delay for OFF duration

// ADVANCED CHALLENGES:
// Challenge 1: Blink 3 times fast, then 1 time slow (SOS pattern?)
// Challenge 2: Fade the LED using analogWrite() on a PWM pin
// Challenge 3: Use millis() instead of delay() (non-blocking)

// THINK ABOUT:
// What is the maximum blink frequency before your eye can't detect it?
// What happens at delay(0)? At delay(1)?
```

### 7. Output Explanation

- External LED blinks at defined intervals
- Serial Monitor shows each blink with cycle number
- Changing `ON_TIME` and `OFF_TIME` changes blink pattern
- PWM version (challenge) creates smooth fade effect

---

## 🧪 Experiment 4: Simulation of 4-Way Traffic Light with Arduino

### 1. Objective

To simulate a 4-way traffic light system using Arduino, demonstrating sequential LED control with realistic timing logic.

### 2. Components Required

| Component | Quantity | Color |
|---|---|---|
| Arduino UNO | 1 | — |
| LED | 12 | 3 Red, 3 Yellow, 3 Green + 3 spare |
| Resistors | 12 | 220Ω each |
| Breadboard | 2 | — |
| Jumper Wires | 20+ | M-M |

### 3. Theory

A **4-way traffic intersection** has 4 directions: North, South, East, West.

**Traffic Light Phases:**
```
Phase 1: North-South GREEN  | East-West RED   → 30 sec
Phase 2: North-South YELLOW | East-West RED   → 5 sec
Phase 3: North-South RED    | East-West GREEN → 30 sec
Phase 4: North-South RED    | East-West YELLOW→ 5 sec
(Cycle repeats)
```

**State Machine Concept:**  
The traffic light operates as a **finite state machine** — always in one of 4 defined states, with defined transitions between them.

### 4. Circuit Description

```
Traffic Light Pin Assignment:

North Signal:   Red=Pin2,  Yellow=Pin3,  Green=Pin4
South Signal:   Red=Pin5,  Yellow=Pin6,  Green=Pin7
East Signal:    Red=Pin8,  Yellow=Pin9,  Green=Pin10
West Signal:    Red=Pin11, Yellow=Pin12, Green=Pin13

Each LED: Arduino_Pin → 220Ω Resistor → LED(+) → LED(-) → GND

Breadboard layout:
- Use two full breadboards for all 12 LEDs
- Connect all LED cathodes to common GND
- Color-code your wires! (Red=Red wire, Green=Green wire)
```

### 5. Algorithm / Steps

```
Step 1: Define 12 pins (4 signals × 3 lights each)
Step 2: Create arrays for each direction's pins
Step 3: In setup() - set all 12 pins as OUTPUT
Step 4: Initialize all lights to RED (safe initial state)

Step 5: Create a function: setSignal(direction, color)
  → Takes direction (N/S/E/W) and color (RED/YELLOW/GREEN)
  → Sets appropriate pins HIGH/LOW

Step 6: Create a function: allRed()
  → Sets all 4 directions to RED (pedestrian crossings)

Step 7: In loop() - implement 4 phases:
  Phase 1: N/S Green, E/W Red → Green duration
  Phase 2: N/S Yellow → Yellow duration
  Phase 3: E/W Green, N/S Red → Green duration
  Phase 4: E/W Yellow → Yellow duration
  
Step 8: (Advanced) Add pedestrian crossing phase between transitions
```

### 6. Code Section

```cpp id="iot004"
// Experiment 4: 4-Way Traffic Light Simulation
// Concept: State Machine with Arduino Digital Outputs

// Step 1: Define pin constants for all 12 LEDs
// Organize by direction: NORTH, SOUTH, EAST, WEST
// Each has: RED, YELLOW, GREEN pin
// Example: const int N_RED = 2; const int N_YELLOW = 3; ...

// Step 2: Define timing constants
// const int GREEN_TIME = 5000;   (5 seconds for demo)
// const int YELLOW_TIME = 2000;  (2 seconds transition)
// const int ALL_RED_TIME = 1000; (1 second safety buffer)

// Step 3: Create a helper function: void allRed()
// → Sets ALL 12 output pins:
//   RED pins → HIGH
//   YELLOW pins → LOW  
//   GREEN pins → LOW

// Step 4: Create function: void setNS_Green()
// → North and South: GREEN HIGH, RED LOW, YELLOW LOW
// → East and West: RED HIGH, others LOW

// Step 5: Create function: void setNS_Yellow()
// → N/S: YELLOW HIGH, others LOW
// → E/W: RED HIGH, others LOW

// Step 6: Create function: void setEW_Green()
// → East and West: GREEN HIGH, others LOW
// → N/S: RED HIGH, others LOW

// Step 7: Create function: void setEW_Yellow()
// → E/W: YELLOW HIGH, others LOW
// → N/S: RED HIGH, others LOW

// Step 8: setup() → pinMode all 12 pins as OUTPUT, call allRed()

// Step 9: loop() → call phases in sequence with delays:
// allRed (1 sec) → setNS_Green (5 sec) → setNS_Yellow (2 sec)
// → allRed (1 sec) → setEW_Green (5 sec) → setEW_Yellow (2 sec)
// → repeat

// ADVANCED: Print current phase to Serial Monitor
// ADVANCED: Add millis() for non-blocking timer
// ADVANCED: Simulate pedestrian button press with pushbutton
```

### 7. Output Explanation

- All 12 LEDs cycle through correct traffic light phases
- Opposing directions (N/S) NEVER show green at same time as (E/W)
- Yellow always appears before switching, for safety
- Serial Monitor (challenge) shows "Phase 1: N/S Green – 5 seconds"

---

## 🧪 Experiment 5: Ultrasonic Sensor Handling with Arduino

### 1. Objective

To measure distance using the HC-SR04 ultrasonic sensor and display readings on the Serial Monitor and trigger alerts at threshold distances.

### 2. Components Required

| Component | Quantity |
|---|---|
| Arduino UNO | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| LED | 1 |
| Buzzer | 1 |
| Resistor 220Ω | 1 |
| Breadboard | 1 |
| Jumper Wires | 8 |

### 3. Theory

**How Ultrasonic Sensing Works:**

```
Trigger → Sends ultrasonic pulse (40kHz) → travels through air
                                                    ↓
                                            Hits object
                                                    ↓
Pulse returns (echo) ← reflects back ←─────────────┘

Distance = (Time of Echo × Speed of Sound) / 2

Speed of sound = 343 m/s = 0.0343 cm/μs
Time includes BOTH directions → divide by 2

Formula:
Distance (cm) = (echo_time_microseconds × 0.0343) / 2
```

**HC-SR04 Specifications:**
- Operating Voltage: 5V
- Frequency: 40 kHz
- Range: 2 cm – 400 cm
- Accuracy: ±3 mm
- Trigger Pulse: 10 μs HIGH

### 4. Circuit Description

```
HC-SR04 Pin Connections:
VCC  → Arduino 5V
GND  → Arduino GND
TRIG → Arduino Pin 9  (output from Arduino)
ECHO → Arduino Pin 10 (input to Arduino)

Alert Circuit:
LED:    Pin 7 → 220Ω → LED(+) → LED(-) → GND
Buzzer: Pin 8 → Buzzer(+) → Buzzer(-) → GND

Physical placement:
Mount HC-SR04 facing forward for distance measurement
Place LED/buzzer separately as alert indicator
```

### 5. Algorithm / Steps

```
Step 1: Connect HC-SR04 per circuit description
Step 2: Define TRIG_PIN and ECHO_PIN
Step 3: In setup(), set TRIG as OUTPUT, ECHO as INPUT

Step 4: Create function: long measureDistance()
  - Send 10μs HIGH pulse to TRIG
  - Use pulseIn(ECHO_PIN, HIGH) to measure echo time
  - Calculate and return distance in cm

Step 5: In loop():
  - Call measureDistance() and store in variable
  - Print to Serial Monitor
  - Check if distance < threshold (e.g., 20cm)
  - If too close: sound buzzer, blink LED
  - If safe: turn off buzzer/LED

Step 6: Add delay(100) for stability
```

### 6. Code Section

```cpp id="iot005"
// Experiment 5: HC-SR04 Ultrasonic Distance Sensor
// Objective: Measure distance and trigger proximity alerts

// Step 1: Define pin numbers as constants
// TRIG_PIN: sends the pulse (output)
// ECHO_PIN: receives the reflection (input)
// LED_PIN: alert indicator
// BUZZ_PIN: audio alert

// Step 2: Define threshold distance (e.g., 20 cm for alert)

// Step 3: setup() function
// - Set TRIG and ECHO pin modes appropriately
// - Set LED and BUZZ as OUTPUT
// - Initialize Serial at 9600 baud
// - Print: "Ultrasonic Distance Sensor Ready"

// Step 4: Create function: long getDistance()
// This is the CORE function. Steps:
//   a) Set TRIG_PIN LOW for 2 microseconds (cleanup)
//   b) Set TRIG_PIN HIGH for 10 microseconds (send pulse)
//   c) Set TRIG_PIN LOW again
//   d) Use pulseIn() to measure ECHO_PIN pulse duration
//      Hint: duration = pulseIn(ECHO_PIN, HIGH);
//   e) Convert duration to centimeters
//      Hint: distance = duration * 0.034 / 2;
//   f) Return the distance value

// Step 5: loop() function
// - Call getDistance() → store in variable 'dist'
// - Print: "Distance: X cm"
// - Check: if (dist < THRESHOLD)
//     → Sound buzzer (analogWrite or tone())
//     → Blink LED rapidly
//     → Print: "⚠ OBJECT DETECTED!"
//   else:
//     → Buzzer off, LED off
//     → Print: "Clear"
// - delay(100) for stability

// ADVANCED CHALLENGES:
// Challenge 1: Create 3 zones - SAFE (green), CAUTION (yellow), DANGER (red)
//   using 3 different colored LEDs
// Challenge 2: Display distance on 4-digit 7-segment display
// Challenge 3: Use Serial Plotter to graph distance over time
//   (Tools → Serial Plotter in Arduino IDE)

// THINK ABOUT:
// Why do we divide by 2? (pulse travels TO object AND BACK)
// What happens with very close (<2cm) or very far (>4m) objects?
// How would you filter out inconsistent readings?
```

### 7. Output Explanation

- Serial Monitor displays real-time distance in cm
- Buzzer and LED activate when object is within threshold
- Serial Plotter (challenge) shows wave pattern as you move hand
- Readings oscillate slightly (normal) — averaging would improve accuracy

---

## 🧪 Experiment 6: Servo Motor and Stepper Motor with Arduino

### 1. Objective

To control the precise angular position of a servo motor and to drive a stepper motor through sequential step patterns using Arduino.

### 2. Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| Servo Motor | 1 | SG90 or MG995 |
| Stepper Motor | 1 | 28BYJ-48 (5V) |
| ULN2003 Driver Board | 1 | For stepper motor |
| Power Supply | 1 | 5V/2A for stepper |
| Jumper Wires | 20 | — |

### 3. Theory

#### Servo Motor
- **3 wires:** VCC (red), GND (brown/black), Signal (orange/yellow)
- Controlled by **PWM signal** (usually 50Hz)
- Pulse width maps to angle:
  - 1ms pulse → 0°
  - 1.5ms pulse → 90°
  - 2ms pulse → 180°
- Range: 0°–180° (standard servo)
- Arduino uses `Servo.h` library

#### Stepper Motor (28BYJ-48)
- **Type:** Unipolar 4-phase stepper
- **Steps:** 512 full steps = 360° (64 steps per revolution × 8:1 gear)
- Requires **driver circuit** (ULN2003) – Arduino cannot drive inductors directly
- Sequence: A → AB → B → BC → C → CD → D → DA (8-step half-step)

### 4. Circuit Description

```
SERVO MOTOR:
Red wire  → Arduino 5V
Brown wire → Arduino GND
Orange wire → Arduino Pin 9 (PWM ~)

STEPPER (28BYJ-48 + ULN2003):
ULN2003 IN1 → Arduino Pin 8
ULN2003 IN2 → Arduino Pin 9
ULN2003 IN3 → Arduino Pin 10
ULN2003 IN4 → Arduino Pin 11
ULN2003 VCC → External 5V supply
ULN2003 GND → Common GND (Arduino + supply)
Stepper connector → ULN2003 output connector

⚠ IMPORTANT: Always connect stepper motor to external 5V,
NOT the Arduino 5V pin. Stepper draws too much current!
```

### 5. Algorithm / Steps

```
SERVO:
Step 1: Include Servo.h library
Step 2: Create Servo object
Step 3: Attach servo to PWM pin in setup()
Step 4: In loop() sweep 0° to 180° in small increments
Step 5: Then sweep back 180° to 0°
Step 6: Print current angle to Serial

STEPPER:
Step 1: Include Stepper.h library
Step 2: Define steps per revolution
Step 3: Create Stepper object with 4 pin numbers
Step 4: Set target RPM (speed)
Step 5: Call stepper.step(512) for one full rotation
Step 6: Rotate clockwise and counter-clockwise
```

### 6. Code Section

```cpp id="iot006"
// Experiment 6: Servo + Stepper Motor Control
// Two separate sketches - practice both!

// ═══════════════════════════════════════
// PART A: SERVO MOTOR
// ═══════════════════════════════════════

// Step 1: Include the Servo library at the top
// Hint: #include <Servo.h>

// Step 2: Create a Servo object
// Hint: Servo myServo;

// Step 3: Define the servo pin constant

// Step 4: setup() function
// - Use myServo.attach(SERVO_PIN) to connect servo
// - Initialize Serial
// - Print "Servo Control Ready"

// Step 5: loop() function - Sweep Motion
// - Use a for loop: angle from 0 to 180, step by 1
//   → myServo.write(angle)
//   → delay(15) between each step (smooth motion)
//   → Print current angle
// - Then reverse: for loop angle from 180 to 0
// - This creates a sweeping back-and-forth motion

// SERVO CHALLENGE:
// Map a potentiometer reading (analogRead A0) to servo angle
// Hint: use map() function to convert 0-1023 → 0-180


// ═══════════════════════════════════════
// PART B: STEPPER MOTOR (28BYJ-48)
// ═══════════════════════════════════════

// Step 1: Include Stepper library
// Hint: #include <Stepper.h>

// Step 2: Define STEPS_PER_REVOLUTION constant
// For 28BYJ-48: 2048 steps = 360° (full step mode)

// Step 3: Create Stepper object
// Hint: Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);
// Note: Pin order matters for 28BYJ-48!

// Step 4: setup()
// - Set stepper speed with myStepper.setSpeed(RPM)
//   Start with 5 RPM (it's a slow motor)
// - Serial begin and print "Stepper Ready"

// Step 5: loop()
// - Rotate one full revolution clockwise
//   Hint: myStepper.step(STEPS_PER_REV)
// - Delay 1 second
// - Rotate one full revolution counter-clockwise
//   Hint: myStepper.step(-STEPS_PER_REV)
// - Delay 1 second
// - Print direction and step count to Serial

// STEPPER CHALLENGE:
// Rotate to specific angles
// Hint: steps_for_angle = (STEPS_PER_REV / 360.0) * target_angle
// Rotate 90° CW, pause, 45° CCW, pause, 180° CW
```

### 7. Output Explanation

- Servo smoothly sweeps from 0° to 180° and back
- Stepper makes exact full rotations (count steps to verify)
- Serial Monitor confirms current position/direction
- Potentiometer challenge: servo tracks knob position in real-time

---

## 🧪 Experiment 7: Different Sensors for Smart Home Using Arduino

### 1. Objective

To integrate multiple smart home sensors (PIR, DHT11, LDR, MQ-2 gas sensor) with Arduino and implement automatic responses.

### 2. Components Required

| Component | Quantity | Purpose |
|---|---|---|
| Arduino UNO | 1 | Controller |
| PIR Motion Sensor | 1 | Motion detection |
| DHT11 Sensor | 1 | Temp + Humidity |
| LDR Module | 1 | Light detection |
| MQ-2 Gas Sensor | 1 | Gas/smoke detection |
| Relay Module | 1 | Switch appliances |
| Buzzer | 1 | Gas alarm |
| LED (various colors) | 3 | Indicators |
| Resistors 220Ω | 3 | LED protection |
| Breadboard | 1 | — |
| Jumper Wires | 30+ | — |

### 3. Theory

**PIR Sensor (Passive Infrared):**
- Detects changes in infrared radiation (body heat)
- Two slots look in slightly different directions
- When human moves across field → differential signal triggers output
- Output: Digital HIGH when motion detected
- Adjustable: sensitivity (how far), time delay (how long HIGH stays)

**DHT11:**
- Single-wire digital protocol
- Temperature: 0–50°C (±2°C accuracy)
- Humidity: 20–90% RH (±5% accuracy)
- Update interval: once per 2 seconds minimum

**LDR (Light Dependent Resistor):**
- Resistance: ~10MΩ in dark, ~1kΩ in bright light
- Used in voltage divider with fixed resistor
- Arduino reads analog voltage → maps to light level

**MQ-2 Gas Sensor:**
- Heated metal oxide changes resistance when gas present
- Detects: LPG, i-butane, propane, methane, alcohol, H2, smoke
- Needs ~30 second warm-up time
- Set threshold based on clean air baseline reading

### 4. Circuit Description

```
PIR Sensor:
VCC → 5V | GND → GND | OUT → Pin 2

DHT11 Module:
VCC → 5V | GND → GND | DATA → Pin 3
(Library: DHT.h by Adafruit)

LDR Voltage Divider:
5V → [10kΩ resistor] → junction → A0
junction → [LDR] → GND
(Low light = high voltage at A0 = high analogRead value)

MQ-2 Gas Sensor:
VCC → 5V | GND → GND | A0 → A1
(Wait 30 seconds after powerup for stable readings)

Relay Module:
VCC → 5V | GND → GND | IN → Pin 7
(Controls external AC appliance - lights, fan)

Buzzer → Pin 8 → GND
Status LEDs → Pins 9,10,11 each through 220Ω → GND
```

### 5. Algorithm / Steps

```
Step 1: Include required libraries (DHT.h)
Step 2: Define all pin numbers
Step 3: Define thresholds:
  - GAS_THRESHOLD: value above which alarm triggers
  - DARK_THRESHOLD: LDR value below which auto-light triggers
Step 4: setup() - configure all pins, initialize serial, DHT

Step 5: In loop():
  a) Read PIR → if motion detected, turn on relay (light ON)
  b) Read DHT11 → print temp + humidity
     → if temp > 35°C print warning
  c) Read LDR → if dark, turn on light LED
     → if ldr > DARK_THRESHOLD (bright), turn off
  d) Read MQ-2 → if gas > threshold:
     → Sound buzzer rapidly
     → Print EMERGENCY ALERT
     → Turn off relay (safety)
  e) delay(500) between readings
```

### 6. Code Section

```cpp id="iot007"
// Experiment 7: Smart Home Multiple Sensor System
// Simulating: Motion detection, climate monitoring,
//             automatic lighting, gas alarm

// Step 1: Include required library for DHT sensor
// Hint: #include <DHT.h>
// Install from Library Manager: "DHT sensor library" by Adafruit

// Step 2: Define constants for all pin numbers
// PIR_PIN, DHT_PIN, LDR_PIN (analog), GAS_PIN (analog)
// RELAY_PIN, BUZZER_PIN, LED_MOTION, LED_LIGHT, LED_GAS

// Step 3: Define threshold values
// GAS_THRESHOLD = ? (calibrate: read clean air value, add 200)
// DARK_THRESHOLD = ? (read in dark room, use that value)
// HOT_TEMP = 35  (degrees C trigger point)

// Step 4: Create DHT object
// DHT dht(DHT_PIN, DHT11);

// Step 5: setup() function
// - Initialize Serial at 9600 baud
// - Set pin modes for all pins
// - dht.begin() to initialize sensor
// - Print: "Smart Home System Initialized"
// - Print: "Warming up sensors... (30 sec)"
// - delay(30000) → for MQ-2 warmup

// Step 6: Create helper functions:

// bool checkMotion():
// → reads PIR pin, returns true if motion
// → controls relay and motion LED

// void readClimate():
// → float temp = dht.readTemperature();
// → float hum = dht.readHumidity();
// → check if reading is valid (use isnan())
// → print temp and humidity
// → if temp is too high, print warning

// void checkLight():
// → int lightVal = analogRead(LDR_PIN);
// → compare to DARK_THRESHOLD
// → turn on/off light LED

// void checkGas():
// → int gasVal = analogRead(GAS_PIN);
// → compare to GAS_THRESHOLD
// → if dangerous: buzz alarm, print "⚠ GAS LEAK DETECTED!"
// → turn on gas LED indicator

// Step 7: loop() function
// - Call all helper functions
// - Add delay(1000)
// - Print separator line for readability

// ADVANCED CHALLENGE:
// Create a "SYSTEM STATUS" display every 5 seconds showing:
// | Motion | Temp | Humidity | Light Level | Gas Level | Status |
// Use millis() instead of delay() for non-blocking code
```

### 7. Output Explanation

- PIR triggers: relay clicks, light indicator on
- DHT11 prints temperature and humidity every second
- LDR: Light LED turns on in dark room, off in bright light
- Gas sensor: Buzzer alarms if gas detected, displays reading on serial

---

## 🧪 Experiment 8: Spinning a DC Motor and Motor Speed Control

### 1. Objective

To control a DC motor's spin direction and speed using PWM via the L298N or L293D motor driver module with Arduino.

### 2. Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| DC Motor | 1 | 5–12V |
| L298N Motor Driver | 1 | Or L293D IC |
| Potentiometer 10kΩ | 1 | Speed control |
| Pushbutton | 1 | Direction toggle |
| External Power Supply | 1 | 9–12V for motor |
| Capacitor 100µF | 1 | Noise suppression |
| Jumper Wires | 15+ | — |

### 3. Theory

**Why can't Arduino directly power a DC motor?**
- Arduino digital pin max current = **40mA**
- DC motor starting current = **200–1000mA**
- Directly connecting = **fried Arduino pin!**

**L298N Motor Driver:**  
An H-Bridge circuit that can switch DC voltage in both directions using 4 transistors:

```
H-Bridge Concept:
      Supply+
        |
   [S1]   [S2]
    |       |
    ┤ Motor ├
    |       |
   [S3]   [S4]
        |
      Supply-

Forward: S1+S4 close → Current flows left to right → Motor spins CW
Reverse: S2+S3 close → Current flows right to left → Motor spins CCW
```

**PWM Speed Control:**
- `analogWrite(pin, 0)` = 0% duty cycle = motor stopped
- `analogWrite(pin, 127)` = 50% duty cycle = half speed  
- `analogWrite(pin, 255)` = 100% duty cycle = full speed

### 4. Circuit Description

```
L298N Motor Driver:
IN1 → Arduino Pin 5 (direction control)
IN2 → Arduino Pin 6 (direction control)
ENA → Arduino Pin 9 (PWM speed control, enable)

Output A → DC Motor terminal 1
Output A → DC Motor terminal 2

L298N 12V → External 9-12V supply (+)
L298N GND → External supply (-) + Arduino GND (MUST link)
L298N 5V  → Arduino 5V (if jumper removed)

Potentiometer:
Pin 1 → 5V | Pin 2 → A0 | Pin 3 → GND

Pushbutton:
One side → Pin 2 | Other side → GND
(Use INPUT_PULLUP mode)

⚠ ALWAYS connect external GND to Arduino GND!
   Otherwise direction signals don't work.
```

### 5. Algorithm / Steps

```
Step 1: Connect circuit per description
Step 2: Define IN1, IN2, ENA (PWM), POT_PIN, BTN_PIN
Step 3: State variable: bool motorDirection = true;

Step 4: setup():
- Set IN1, IN2, ENA as OUTPUT
- BTN_PIN as INPUT_PULLUP
- Serial begin

Step 5: loop():
- Read potentiometer: int speed = analogRead(POT_PIN)
- Map speed to PWM: int pwmSpeed = map(speed, 0, 1023, 0, 255)

- Check button (debounce!):
  if button pressed → flip motorDirection flag

- Apply direction:
  if motorDirection:
    IN1=HIGH, IN2=LOW → Forward
  else:
    IN1=LOW, IN2=HIGH → Backward

- Apply speed:
  analogWrite(ENA, pwmSpeed)

- Print: "Speed: X% | Direction: FWD/REV"
- delay(50)
```

### 6. Code Section

```cpp id="iot008"
// Experiment 8: DC Motor Speed and Direction Control
// Objective: Control motor via L298N with PWM speed control

// Step 1: Define pin numbers
// IN1, IN2 → direction control
// ENA → PWM for speed (must be a PWM-capable pin!)
// POT_PIN → analog pin for potentiometer
// BTN_PIN → pushbutton for direction toggle

// Step 2: Declare variables
// bool motorDirection = true; (true=forward, false=reverse)
// int currentSpeed; (store mapped PWM value 0-255)
// bool lastButtonState; (for edge detection)

// Step 3: setup()
// - Set motor pins as OUTPUT
// - Set BTN_PIN as INPUT_PULLUP (no need for external resistor!)
// - Initialize Serial
// - Print "DC Motor Control Ready"
// - Start with motor stopped: set ENA to 0

// Step 4: Create function: void setMotorDirection(bool forward)
// if forward:
//   digitalWrite(IN1, HIGH)
//   digitalWrite(IN2, LOW)
// else:
//   digitalWrite(IN1, LOW)
//   digitalWrite(IN2, HIGH)

// Step 5: Create function: void setMotorSpeed(int speed)
// - speed is 0-255 (PWM value)
// - analogWrite(ENA, speed)
// - Print: "PWM: X/255 = Y%"
// - Calculate Y% = (speed * 100) / 255

// Step 6: loop()
// a) Read potentiometer (analogRead) → map to 0-255
// b) Check button for direction toggle:
//    Read current button state
//    If state CHANGED from HIGH to LOW (button pressed)
//      → flip motorDirection
//      → add delay(50) for debounce
//    Save current state as lastButtonState
// c) Call setMotorDirection(motorDirection)
// d) Call setMotorSpeed(mapped_speed)
// e) Print all info to Serial Monitor
// f) delay(50) main loop delay

// ADVANCED CHALLENGES:
// Challenge 1: Soft start/stop - ramp speed gradually from 0 to target
// Challenge 2: Emergency stop if speed < 10 (dead band)
// Challenge 3: Control via Serial input
//   If you type "F" → forward, "R" → reverse, number → set speed
// Challenge 4: Add RPM sensing with hall effect sensor on motor shaft
```

### 7. Output Explanation

- Motor speed changes smoothly with potentiometer rotation
- Button press reverses motor direction (watch shaft spin!)
- Serial Monitor shows real-time: speed percentage and direction
- Motor stops when potentiometer at minimum position

---

## 🧪 Experiment 9: Working with Shields

### 1. Objective

To understand Arduino shields, install and use an Ethernet Shield to enable network connectivity, and to understand shield stacking concepts.

### 2. Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | — |
| Ethernet Shield (W5100) | 1 | Or WiFi Shield |
| Ethernet Cable (RJ45) | 1 | For Ethernet Shield |
| WiFi Shield / ESP8266 | 1 | Alternative |
| Breadboard (optional) | 1 | Additional circuits |
| Jumper Wires | 10 | — |

### 3. Theory

**What is a Shield?**  
An Arduino **shield** is an add-on board that plugs directly onto the Arduino's header pins, expanding its capabilities. Shields are stackable.

**Common Arduino Shields:**

| Shield Name | What It Adds |
|---|---|
| **Ethernet Shield** | Wired internet via RJ45 |
| **WiFi Shield** | Wireless internet |
| **GSM/GPRS Shield** | Cellular network |
| **Motor Shield** | Drive motors (2x DC, 1x stepper) |
| **SD Card Shield** | Local file storage |
| **LCD Shield** | 16×2 LCD + buttons |
| **Sensor Shield** | Easy 3-pin sensor headers |
| **Relay Shield** | Control AC appliances (4 relays) |
| **Prototype Shield** | Custom circuit right on shield |

**Ethernet Shield (W5100):**
- Uses SPI communication (Pins 10–13)
- Pin 4 for SD card CS (if onboard SD used)
- Pin 10 for Ethernet CS
- Library: `Ethernet.h` (built into Arduino IDE)

### 4. Circuit Description

```
Shield Stacking:
Just press Ethernet Shield directly onto Arduino UNO headers

Pin Usage (Shield occupies):
- Pins 10, 11, 12, 13 → SPI (do not use for other things!)
- Pin 4 → SD Card Chip Select
- Pin 10 → Ethernet Chip Select

External:
- Ethernet cable from shield → Router/Switch
- Power via USB or barrel jack (shield powers from Arduino)

⚠ When using Ethernet Shield, avoid digital pins 10-13 for your project!
```

### 5. Algorithm / Steps

```
Step 1: Stack Ethernet Shield on Arduino UNO
Step 2: Connect Ethernet cable to shield and router
Step 3: Install Ethernet library (already included in IDE)
Step 4: Get your network info:
  - MAC address (printed on shield or randomly assigned)
  - IP address (use DHCP or manually assign)

Step 5: In code:
  - Include Ethernet.h
  - Define MAC address byte array
  - Use Ethernet.begin(mac) for DHCP
  - Start an EthernetServer on port 80

Step 6: In loop():
  - Check for incoming HTTP requests
  - Parse the request
  - Send HTML response with sensor data

Step 7: Open browser → type Arduino IP address
Step 8: See your sensor dashboard in browser!
```

### 6. Code Section

```cpp id="iot009"
// Experiment 9: Arduino Ethernet Shield - Simple Web Server
// Objective: Expose sensor data as a web page using Arduino

// Step 1: Include the Ethernet library
// Hint: #include <Ethernet.h>

// Step 2: Define the MAC address of your shield
// Usually printed on a sticker on the shield
// Hint: byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Step 3: Create an EthernetServer on port 80
// Hint: EthernetServer server(80);

// Step 4: setup()
// - Initialize Serial
// - Print "Starting Ethernet..."
// - Use Ethernet.begin(mac) for DHCP address
// - Wait 1 second for connection
// - Print the IP address: Serial.print(Ethernet.localIP())
// - Start the server: server.begin()
// - Print "Server is at " + IP address

// Step 5: loop()
// - Listen for incoming clients:
//   EthernetClient client = server.available()
// - If client connected:
//   → Print "New client connected"
//   → Read and discard HTTP request headers
//     (look for blank line = end of headers)
//   → Send HTTP response:
//     client.println("HTTP/1.1 200 OK");
//     client.println("Content-Type: text/html");
//     client.println("Connection: close");
//     client.println(); (blank line = end of headers)
//   → Send HTML body with sensor data
//     Build a simple HTML page showing:
//     - Current analog reading from A0
//     - Current millis() (uptime)
//     - Temperature (if DHT connected)
//   → client.stop() to end connection

// Step 6: HTML template to send:
// <html><body>
// <h1>Arduino Sensor Dashboard</h1>
// <p>Sensor A0: [value]</p>
// <p>Uptime: [value] ms</p>
// <meta http-equiv='refresh' content='5'> ← auto-refresh every 5s
// </body></html>

// ADVANCED CHALLENGES:
// Challenge 1: Add DHT11 readings to the web page
// Challenge 2: Accept commands via URL:
//   http://[IP]/led=on → turn LED on
//   http://[IP]/led=off → turn LED off
//   Parse the URL and extract command
// Challenge 3: Log sensor readings to SD card on the shield

// WiFi ALTERNATIVE (ESP8266 or WiFi Shield):
// → Similar concept but use WiFi.h instead
// → Use WiFi.begin(SSID, PASSWORD) instead of Ethernet.begin()
// → All other code remains similar
```

### 7. Output Explanation

- Serial Monitor shows "IP address: 192.168.1.X"
- Browser at that IP shows live sensor data HTML page
- Page auto-refreshes every 5 seconds
- Each browser request logs "New client connected" in Serial Monitor

---

## 🧪 Experiment 10: Interfacing Arduino with Cloud

### 1. Objective

To send real sensor data from Arduino to the cloud (using Arduino IoT Cloud or ThingSpeak) over WiFi, and visualize it on a web dashboard.

### 2. Components Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO + ESP8266 | 1 | Or Arduino MKR WiFi |
| DHT11 Temperature Sensor | 1 | For real data |
| LDR | 1 | Light level data |
| Breadboard | 1 | — |
| Jumper Wires | 10 | — |
| WiFi Internet | 1 | 2.4 GHz network |

### 3. Theory

**Cloud IoT Architecture for Arduino:**

```
Sensor Data (temp, humidity, light)
        ↓
Arduino code collects data
        ↓
WiFi module (ESP8266/ESP32) connects to internet
        ↓
Data sent via HTTP POST or MQTT
        ↓
Cloud Platform (ThingSpeak / Arduino IoT Cloud)
        ↓
Dashboard (graphs, charts, alerts)
        ↓
Remote access from anywhere in the world!
```

**ThingSpeak:**
- Free IoT platform from MathWorks (makers of MATLAB)
- Each "channel" has 8 fields (data streams)
- REST API: HTTP GET with API key
- URL format: `https://api.thingspeak.com/update?api_key=XXX&field1=YYY`

**Arduino IoT Cloud:**
- Official Arduino cloud service
- MQTT-based
- "Things" and "Properties" concept
- Auto-generates code for you!
- Free tier: 2 things, 5 dashboards

### 4. Circuit Description

```
DHT11 Sensor:
VCC → 3.3V | GND → GND | DATA → Pin 3

LDR:
5V → [10kΩ resistor] → A0 → [LDR] → GND

ESP8266 (as AT-command WiFi module):
TX → Arduino Pin 10 (SoftwareSerial RX)
RX → Arduino Pin 11 (SoftwareSerial TX) via 1kΩ voltage divider
VCC → 3.3V (separate power recommended)
GND → GND

⚠ ESP8266 runs on 3.3V. NEVER connect to 5V!
⚠ Use voltage divider on TX→RX line: 1kΩ + 2kΩ

ALTERNATIVE: Use ESP8266 as standalone
(Run full Arduino code directly on ESP8266 via Arduino IDE)
This is the RECOMMENDED approach for beginners.
```

### 5. Algorithm / Steps

```
Step 1: Create ThingSpeak account at thingspeak.com
Step 2: Create new Channel
  - Field 1: Temperature
  - Field 2: Humidity
  - Field 3: Light Level
Step 3: Note your Channel ID and Write API Key

Step 4: Connect to WiFi using ESP8266 or Arduino WiFi shield

Step 5: In loop():
  a) Read DHT11: temperature, humidity
  b) Read LDR: light level
  c) Build URL with data
  d) Send HTTP GET request to ThingSpeak
  e) Wait for response (200 = success)
  f) Delay 15 seconds minimum (ThingSpeak free limit)
  g) Print to Serial: what was sent and server response

Step 6: Open ThingSpeak channel in browser
Step 7: Watch real-time graphs update!
```

### 6. Code Section

```cpp id="iot010"
// Experiment 10: Arduino → WiFi → Cloud (ThingSpeak)
// Objective: Upload live sensor data to cloud dashboard

// Step 1: Include required libraries
// For DHT: #include <DHT.h>
// For WiFi: depends on your module:
//   ESP8266: #include <ESP8266WiFi.h> (if using ESP8266 board)
//   WiFi Shield: #include <WiFi.h>
//   SoftwareSerial for AT: #include <SoftwareSerial.h>

// Step 2: Define credentials (keep private in real projects!)
// const char* WIFI_SSID = "YOUR_WIFI_NAME";
// const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
// const char* API_KEY = "YOUR_THINGSPEAK_WRITE_KEY";
// const char* HOST = "api.thingspeak.com";

// Step 3: Define sensor pins and create DHT object

// Step 4: setup()
// - Initialize Serial
// - Initialize DHT
// - Connect to WiFi:
//   WiFi.begin(WIFI_SSID, WIFI_PASS)
//   while (WiFi.status() != WL_CONNECTED) { delay(500); print("." }
//   Print: "WiFi connected! IP: " + WiFi.localIP()

// Step 5: Create function: void sendToCloud(float temp, float hum, int light)
// - Create WiFiClient or HTTPClient object
// - Build the URL string:
//   String url = "/update?api_key=" + String(API_KEY);
//   url += "&field1=" + String(temp);
//   url += "&field2=" + String(hum);
//   url += "&field3=" + String(light);
// - Connect to host on port 80
// - Send HTTP GET request:
//   client.print("GET " + url + " HTTP/1.1");
//   client.println("Host: " + String(HOST));
//   client.println("Connection: close");
//   client.println(); (blank line)
// - Read and print server response
// - Close connection

// Step 6: loop()
// - Read temperature: float temp = dht.readTemperature()
// - Read humidity: float hum = dht.readHumidity()
// - Read light: int light = analogRead(LDR_PIN)
//
// - Validate readings:
//   if (isnan(temp) || isnan(hum)):
//     Print "Sensor read error!"
//     return (skip this iteration)
//
// - Print readings locally:
//   "Temp: X°C | Humidity: Y% | Light: Z"
//
// - Call sendToCloud(temp, hum, light)
//
// - Wait at least 15 seconds!
//   delay(15000) → ThingSpeak free rate limit

// ADVANCED CHALLENGES:
// Challenge 1: Add cloud → Arduino control
//   Read a field from ThingSpeak and control an LED based on value
//   Use HTTP GET to READ from ThingSpeak, not just write

// Challenge 2: Use Arduino IoT Cloud instead of ThingSpeak
//   Create account at create.arduino.cc
//   Follow the wizard to create a "Thing" and properties
//   Use the auto-generated code template

// Challenge 3: Set ThingSpeak alert
//   If temperature > 35°C → ThingSpeak sends email alert
//   Set this up in ThingSpeak ThingHTTP + React

// THINK ABOUT:
// Why do we validate with isnan()?
// What happens if WiFi disconnects? (Add reconnection logic!)
// How would you handle a power outage? (Store readings locally first)
```

### 7. Output Explanation

- Serial Monitor shows WiFi connection status and each data upload
- ThingSpeak dashboard shows 3 live graphs updating every 15 seconds
- Temperature, humidity, and light curves visible over time
- From any device in the world, you can view your sensor's data!

---

[Back to top](#)

---

# References and Further Reading

## Textbooks (Official Course Texts)

| # | Author(s) | Title | Publisher |
|---|---|---|---|
| 1 | Hakima Chaouchi | *The Internet of Things: Connecting Objects to the Web* | Wiley (ISBN: 978-1-84821-140-7) |
| 2 | Olivier Hersent, David Boswarthick, Omar Elloumi | *The Internet of Things: Key Applications and Protocols* | Wiley |
| 3 | Vijay Madisetti, ArshdeepBahga | *Internet of Things: A Hands-on Approach* (1st Ed.) | VPT, 2014 |
| 4 | J. Biron, J. Follett | *Foundational Elements of an IoT Solution* | O'Reilly Media, 2016 |
| 5 | Keysight Technologies | *The IoT: Enabling Technologies and Solutions for Design and Test* | Application Note, 2016 |

## Reference Books

| # | Author(s) | Title | Publisher |
|---|---|---|---|
| 6 | Daniel Minoli | *Building the IoT with IPv6 and MIPv6: The Evolving World of M2M* | Willy (ISBN: 978-1-118-47347-4) |
| 7 | Pethuru Raj, Anupama C. Raman | *The IoT: Enabling Technologies, Platforms, and Use Cases* | CRC Press |

## Online Resources

| Resource | URL |
|---|---|
| NPTEL IoT Course | https://onlinecourses.nptel.ac.in/noc17_cs22/course |
| IoT Protocols Reference | http://www.cse.wustl.edu/~jain/cse570-15/ftp/iot_prot/index.html |
| Arduino Documentation | https://docs.arduino.cc |
| ThingSpeak Platform | https://thingspeak.com |
| Arduino IoT Cloud | https://create.arduino.cc/iot |
| Fritzing (Circuit Diagrams) | https://fritzing.org |
| Tinkercad Circuits (Simulator) | https://tinkercad.com/circuits |

---

## 🎯 Quick Exam Revision Summary

### Unit I Key Points
- **IoT = Sensors + Connectivity + Intelligence + Action**
- **Layers:** Perception → Network → Application (3-layer) or 5-layer model
- **Kevin Ashton** coined "IoT" in 1999
- **IPv6** provides enough addresses for all future IoT devices
- **M2M** = direct machine communication, IoT = internet-connected, smarter, larger-scale

### Unit II Key Points
- **Sensor** converts physical → electrical; **Actuator** converts electrical → physical
- **Arduino UNO:** ATmega328P, 5V, 14 digital + 6 analog pins, 16 MHz
- **RFID Types:** Passive (no battery), Active (battery), Semi-passive
- **WSN Topologies:** Star, Mesh, Tree, Cluster
- **Zigbee vs WiFi:** Zigbee = low power, low data; WiFi = high power, high data

### Unit III Key Points
- **5 V's of Big Data:** Volume, Velocity, Variety, Veracity, Value
- **Hadoop HDFS:** Stores data across nodes; blocks of 128MB, replicated 3×
- **Analytics Types (ascending value):** Descriptive → Diagnostic → Predictive → Prescriptive
- **Local analytics** = low latency, offline; **Cloud analytics** = AI/ML, massive scale

### Unit IV Key Points
- **Smart Home protocols:** Zigbee, Z-Wave, Matter (2022 standard)
- **IIoT = Industry 4.0** = connecting industrial machines to internet
- **GDPR (EU)** = primary data privacy regulation for IoT
- **Mirai Botnet (2016):** Warning for IoT security — 600K devices hijacked
- **Privacy by Design:** Best practice — build privacy in from start

---

*Guide prepared based on official syllabus: MJ DSE-2T: Internet of Things | Credits 03 | Full Marks 75*  
*Practical section based on: MJ DSE-2P: Practical of IoT (Arduino Lab) | Credits 01*

*Last updated: April 2026*



[Back to top](#)

---
