# Project documentation: Smart IoT-Based Parking System

## Abstract

The Smart IoT-Based Parking System is a small-scale parking-management prototype intended to reduce the effort required to identify vacant parking spaces. Six infrared sensors monitor individual parking bays. An Arduino Uno reads the sensor states, calculates the number of occupied and vacant bays, and displays the status and first available bay on a 16×2 I2C LCD. A separate entrance sensor detects an approaching vehicle, while a servo motor operates a model entrance barrier when space is available. When all six bays are occupied, the display reports that parking is full and the gate is commanded to remain closed.

The current implementation demonstrates local sensing, microcontroller-based processing, display, and actuator control. Cloud connectivity, remote monitoring, reservations, digital payments, and vehicle identification are possible future extensions and are not part of the current implementation.

## Problem statement

Drivers in busy parking areas may spend time searching for vacant spaces. Manual inspection can be inefficient and may provide no continuously updated indication of availability. This prototype explores automated slot detection and local display of parking availability.

## Objectives

- Monitor six parking bays independently.
- Classify each bay as occupied or vacant using an IR sensor.
- Calculate occupied and vacant counts.
- Identify and display the first available bay.
- Detect a vehicle approaching the entrance.
- Operate a servo-controlled model gate when at least one bay is vacant.
- Display a full-capacity message when no bay is available.

## System components

| Component | Quantity | Role |
|---|---:|---|
| Arduino Uno | 1 | Reads sensors and controls outputs |
| IR obstacle sensor modules | 7 | Six slot sensors and one entrance sensor |
| 16×2 I2C LCD | 1 | Displays parking information |
| Servo motor | 1 | Operates the model gate |
| Jumper wires and power supply | As required | Electrical connections and power |
| Physical model | 1 | Represents parking bays and entrance |

## Functional workflow

1. Initialize the Arduino, LCD, sensors, and servo.
2. Read the six slot sensors.
3. Count occupied and vacant slots.
4. Identify the first vacant slot in ascending slot order.
5. Display the counts and next slot on the LCD.
6. Read the entrance sensor.
7. If a vehicle is detected and a bay is vacant, display the suggested bay and run the gate servo sequence.
8. If all bays are occupied, display `PARKING FULL` and keep the gate commanded closed.
9. Repeat monitoring.

## Circuit pin map

| Signal | Arduino Uno pin |
|---|---:|
| Slot 1–6 sensors | D2–D7 respectively |
| Entrance sensor | D8 |
| Servo signal | D9 |
| LCD SDA | A4 |
| LCD SCL | A5 |

The firmware uses LCD address `0x27` and assumes active-LOW sensor detection. Check the actual modules and wiring before reproducing the circuit.

## Results represented by the prototype

The submitted project materials describe and photograph a physical miniature parking layout with multiple marked bays, IR sensor modules, an Arduino controller, an LCD, and a servo-operated entrance barrier. The submitted firmware implements occupancy counting, first-vacant-slot selection, LCD status messages, entrance detection, and a full-parking branch. A demonstration video and photographs are included in the repository as supporting evidence.

## Limitations

- The prototype monitors six bays only.
- Sensor performance depends on placement, range, and calibration.
- The current firmware uses fixed delays for gate operation.
- It does not reserve a bay or verify that a vehicle parks in the suggested bay.
- No cloud connection, remote dashboard, mobile application, online reservation, digital payment, or number-plate recognition is implemented.

## Future scope

Potential extensions include an ESP32-based network connection, remote dashboard, reservation workflow, vehicle identification, multi-floor support, and parking-usage analytics.

## Team

- Billakanti Siri
- K. Bhavana
- M. Geethika
- Nuguri Siri

Koneru Lakshmaiah University — B.Tech II Year, AY 2026–27.
