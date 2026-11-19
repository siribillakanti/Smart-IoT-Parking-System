# Firmware review notes

## Submitted implementation summary

The submitted sketch uses six digital inputs (`D2`–`D7`) for parking-slot sensors, `D8` for the entrance sensor, `D9` for the servo signal, and I2C on `A4`/`A5` for the LCD. It assumes `LOW` means a vehicle is detected and configures the sensor pins as `INPUT_PULLUP`.

The main loop counts occupied and vacant bays, finds the first vacant bay, refreshes the LCD, and responds to the entrance sensor. If capacity remains, it displays the first vacant bay and operates the servo from 0° to 90° and back. If all six bays are occupied, it displays a full message and commands the servo closed.

## Items to verify before calling the firmware production-ready

1. **Repeated entrance triggering:** The entrance condition is checked as a level, not a one-time transition. A sensor held active can cause repeated gate cycles. Consider edge detection and a state machine.
2. **Vehicle passage confirmation:** The gate closes after a fixed delay. There is no separate sensor confirming that the vehicle has cleared the barrier.
3. **LCD refresh:** Repeated `lcd.clear()` calls can cause flicker. Update only changed fields or refresh at a controlled interval.
4. **Sensor electrical behavior:** Confirm the sensor output polarity and whether `INPUT_PULLUP` is appropriate for the exact IR modules used.
5. **Power integrity:** Confirm the servo's current requirement and use a suitable supply with common ground.
6. **LCD compatibility:** The exact `LiquidCrystal_I2C` library variant matters because different libraries expose different initialization APIs.
7. **Slot assignment:** The first vacant bay is suggested, but the system does not reserve it or verify that the vehicle occupies that specific bay.

## Validation status

The source was reviewed statically against the project description and pin mapping. A successful Arduino IDE compile and a fresh hardware test have **not** been claimed as part of this repository preparation.
