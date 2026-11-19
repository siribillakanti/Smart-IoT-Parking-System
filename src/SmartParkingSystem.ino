#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------------- PIN DEFINITIONS ----------------

// Parking slot IR sensors
const int slotSensors[6] = {2, 3, 4, 5, 6, 7};

// Vehicle detection at entrance
const int entranceSensor = 8;

// Servo
const int servoPin = 9;

// ---------------- LCD ----------------

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- SERVO ----------------

Servo gateServo;

const int GATE_CLOSED = 0;
const int GATE_OPEN = 90;

// ---------------- SENSOR SETTINGS ----------------

// Most IR obstacle sensors give LOW when an object is detected.
// If your sensor behaves opposite to this, change LOW to HIGH.
const int VEHICLE_DETECTED = LOW;

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(9600);

  // Configure parking sensors
  for (int i = 0; i < 6; i++) {
    pinMode(slotSensors[i], INPUT_PULLUP);
  }

  // Configure entrance sensor
  pinMode(entranceSensor, INPUT_PULLUP);

  // Servo
  gateServo.attach(servoPin);
  gateServo.write(GATE_CLOSED);

  // LCD
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM READY");

  delay(2000);

  lcd.clear();
}

// ---------------- MAIN LOOP ----------------

void loop() {

  int occupied = 0;
  int empty = 0;
  int firstEmptySlot = -1;

  // Check all six parking slots
  for (int i = 0; i < 6; i++) {

    bool vehiclePresent = (digitalRead(slotSensors[i]) == VEHICLE_DETECTED);

    if (vehiclePresent) {
      occupied++;
    }
    else {
      empty++;

      // Remember the first available slot
      if (firstEmptySlot == -1) {
        firstEmptySlot = i;
      }
    }
  }

  // Display current parking status
  displayParkingStatus(occupied, empty);

  // Check whether a vehicle is waiting at the entrance
  bool vehicleAtEntrance =
      (digitalRead(entranceSensor) == VEHICLE_DETECTED);

  if (vehicleAtEntrance) {

    Serial.println("Vehicle detected at entrance.");

    if (empty > 0) {

      Serial.print("Available slot: ");
      Serial.println(firstEmptySlot + 1);

      // Tell driver which slot to use
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("SLOT AVAILABLE");

      lcd.setCursor(0, 1);
      lcd.print("GO TO SLOT ");
      lcd.print(firstEmptySlot + 1);

      delay(500);

      // Open gate
      openGate();

      // Wait while vehicle passes
      delay(2000);

      // Close gate
      closeGate();

      delay(200);

    }
    else {

      // All six slots occupied
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("PARKING FULL");

      lcd.setCursor(0, 1);
      lcd.print("PLEASE WAIT");

      Serial.println("Parking Full.");

      // Keep gate closed
      gateServo.write(GATE_CLOSED);

      delay(2000);
    }
  }

  delay(300);
}

// ---------------- DISPLAY STATUS ----------------

void displayParkingStatus(int occupied, int empty) {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("FULL:");
  lcd.print(occupied);

  lcd.setCursor(8, 0);
  lcd.print("EMPTY:");
  lcd.print(empty);

  if (empty > 0) {

    // Find first available slot
    int availableSlot = -1;

    for (int i = 0; i < 6; i++) {

      if (digitalRead(slotSensors[i]) != VEHICLE_DETECTED) {
        availableSlot = i + 1;
        break;
      }
    }

    lcd.setCursor(0, 1);
    lcd.print("NEXT: SLOT ");
    lcd.print(availableSlot);

  }
  else {

    lcd.setCursor(0, 1);
    lcd.print("PARKING FULL");
  }
}

// ---------------- OPEN GATE ----------------

void openGate() {

  Serial.println("Opening gate...");

  gateServo.write(GATE_OPEN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GATE OPEN");
  lcd.setCursor(0, 1);
  lcd.print("PLEASE ENTER");

  delay(200);
}

// ---------------- CLOSE GATE ----------------

void closeGate() {

  Serial.println("Closing gate...");

  gateServo.write(GATE_CLOSED);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GATE CLOSED");
  lcd.setCursor(0, 1);
  lcd.print("DRIVE SAFELY");

  delay(200);
}
