# Smart IoT-Based Parking System

An Arduino-based smart parking prototype that monitors six parking bays using infrared (IR) sensors, displays occupancy information on a 16×2 I2C LCD, identifies the next available bay, and controls an entrance barrier using a servo motor.

> **Project status:** Physical prototype and Arduino implementation documented. The current implementation uses local sensor inputs and local display/servo control; cloud connectivity, remote monitoring, reservations, and payments are future enhancements, not implemented features.

## Project at a glance

- **Controller:** Arduino Uno
- **Parking capacity:** 6 bays
- **Parking detection:** 6 IR obstacle sensors
- **Entrance detection:** 1 IR obstacle sensor
- **Display:** 16×2 I2C LCD (configured at address `0x27`)
- **Gate actuator:** Servo motor
- **Firmware:** Arduino C/C++
- **Libraries:** `Wire`, `LiquidCrystal_I2C`, and `Servo`

## Physical prototype

The project was assembled as a miniature parking layout with marked parking bays, sensor modules, controller wiring, an LCD, and a servo-operated entrance barrier.

![Physical prototype overview](assets/prototype/prototype-overview-1.png)

More photographs are available in [`assets/prototype/`](assets/prototype/).

## Features implemented in the submitted firmware

1. Reads six parking-slot IR sensors.
2. Counts occupied and vacant slots.
3. Finds the first vacant slot in slot-number order.
4. Displays occupied/vacant counts and the next available slot on the LCD.
5. Detects a vehicle at the entrance.
6. If at least one slot is vacant, displays the suggested slot and operates the servo gate.
7. If all six slots are occupied, displays `PARKING FULL` and commands the gate to remain closed.
8. Prints entrance and gate events to the Serial Monitor at 9600 baud.

## System architecture

```text
6 parking-slot IR sensors ─┐
                           ├──> Arduino Uno ───> 16×2 I2C LCD
Entrance IR sensor ────────┘         │
                                     └──────────> Servo gate
```

The parking sensors and entrance sensor provide digital inputs to the Arduino. The Arduino calculates availability and drives the LCD and servo outputs.

## Pin connections

The table below reflects the submitted `.ino` source code. Verify the physical wiring against this mapping before rebuilding the circuit.

| Component | Arduino Uno connection | Purpose |
|---|---:|---|
| Parking sensor 1 | D2 | Slot 1 occupancy |
| Parking sensor 2 | D3 | Slot 2 occupancy |
| Parking sensor 3 | D4 | Slot 3 occupancy |
| Parking sensor 4 | D5 | Slot 4 occupancy |
| Parking sensor 5 | D6 | Slot 5 occupancy |
| Parking sensor 6 | D7 | Slot 6 occupancy |
| Entrance sensor | D8 | Detect vehicle at entrance |
| Servo signal | D9 | Open/close gate |
| LCD SDA | A4 | I2C data |
| LCD SCL | A5 | I2C clock |
| LCD power | 5V and GND | Power |
| IR sensor power | 5V and GND | Power and common reference |

The firmware uses `INPUT_PULLUP` and assumes a detected vehicle produces `LOW`. Some IR modules have different output behavior or wiring; check the actual module before changing the `VEHICLE_DETECTED` constant.

## Hardware requirements

- Arduino Uno
- 6 IR obstacle sensor modules for parking bays
- 1 IR obstacle sensor module for entrance detection
- 16×2 LCD with I2C backpack
- Servo motor suitable for the model gate
- Jumper wires and suitable power supply
- Physical parking-lot base/model and barrier arm
- USB cable and computer for programming/Serial Monitor

**Power note:** A servo can draw current spikes. Use a suitable regulated supply for the servo when required by its specifications, and connect the supply ground to Arduino ground. Do not assume the Arduino 5V pin can safely power every servo under load.

## Software requirements

- Arduino IDE
- Arduino AVR Boards support for Arduino Uno
- `Servo` library (normally included with the Arduino IDE)
- `LiquidCrystal_I2C` library compatible with the `lcd.init()` API used in the source

`Wire` is part of the Arduino core.

## Build and upload

1. Install the Arduino IDE and Arduino Uno board support.
2. Install a compatible `LiquidCrystal_I2C` library.
3. Open [`src/SmartParkingSystem.ino`](src/SmartParkingSystem.ino).
4. Select **Arduino Uno** and the correct serial port.
5. Connect the circuit using the pin table above.
6. Verify/compile, then upload the sketch.
7. Open Serial Monitor at **9600 baud**.

The LCD address is configured as `0x27`. If the display does not initialize, confirm the backpack address and library compatibility.

## Operating logic

1. The Arduino initializes the sensors, servo, Serial connection, and LCD.
2. It reads each of the six parking sensors and calculates occupied and vacant counts.
3. It identifies the first vacant slot (lowest slot number) and updates the LCD.
4. When the entrance sensor detects a vehicle, the firmware checks the available-slot count.
5. If a slot is available, the LCD shows the suggested slot and the servo is commanded open, then closed after a timed interval.
6. If no slots are available, the LCD shows `PARKING FULL` and the gate is commanded closed.

## Demo and supporting material

- [Physical prototype demonstration video](assets/demo/physical-prototype-demo.mp4)
- [Project presentation (PDF)](assets/presentation/project-presentation.pdf)
- [Prototype photographs](assets/prototype/)
- [Code review and known limitations](docs/code-review.md)
- [Project documentation](docs/project-documentation.md)
- [Project report (student ID numbers redacted)](docs/project-report-redacted.pdf)

## Known limitations and review notes

This repository preserves the submitted firmware. It has not been represented as a freshly compiled or hardware-retested build in this repository. Before a future release, review the following:

- The entrance logic is level-triggered: if the entrance sensor remains active, the gate sequence can run again after the loop delay. Edge detection or a vehicle-passage state machine would make this more robust.
- Several `lcd.clear()` calls occur during the loop and can cause visible flicker.
- The gate uses fixed delays rather than confirming that a vehicle has fully passed.
- The firmware chooses the first available slot; it does not reserve that slot or confirm that the arriving vehicle parks there.
- IR sensor range and active output polarity depend on the specific modules and calibration.
- The source uses `INPUT_PULLUP`; confirm this is appropriate for the sensor modules' digital outputs.
- The physical wiring should be checked against the source-code pin map. The code is the source of truth for the documented firmware mapping in this repository.

## Future enhancements (not currently implemented)

- ESP32/Wi-Fi connectivity and cloud-based occupancy monitoring
- Web or mobile dashboard
- Slot reservation and entry/exit tracking
- Vehicle identification / number-plate recognition
- Parking analytics and historical occupancy data
- Non-blocking gate control and entrance debounce/state management

## Team

Academic group project developed by:

- Billakanti Siri
- K. Bhavana
- M. Geethika
- Nuguri Siri

Koneru Lakshmaiah University — B.Tech, II Year, AY 2026–27.

## Repository contents

```text
Smart-IoT-Parking-System/
├── src/
│   └── SmartParkingSystem.ino
├── docs/
│   ├── code-review.md
│   └── project-documentation.md
├── assets/
│   ├── demo/
│   ├── presentation/
│   └── prototype/
├── README.md
└── .gitignore
```

---

**Note:** This is an educational physical prototype. The repository distinguishes the functionality present in the submitted firmware from proposed future IoT/cloud features.
