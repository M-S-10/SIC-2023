#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <math.h>

// Constants
const int ledPin = 13;       // Pin for the red LED
const int buttonPin = 2;     // Pin for the push button

// Variables
float zPos = 0.0;            // Z position coordinate
unsigned long prevTime = 0;  // Previous time
bool deviationOccurred = false;  // Flag to track deviation occurrence
bool isPowerOn = false;      // Flag to track power state

// Initialize accelerometer
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// Conversion factor for rotated orientation
const float angleRad = 150 * (PI / 180.0);  // Convert angle to radians
const float cosAngle = cos(angleRad);
const float sinAngle = sin(angleRad);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Turn off LED initially

  // Initialize push button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize accelerometer
  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  // Set the initial reference time
  prevTime = millis();
}

void loop() {
  // Check if the button is pressed to toggle power supply
  if (digitalRead(buttonPin) == LOW) {
    isPowerOn = !isPowerOn;  // Toggle power state
    delay(200);  // Debounce delay
  }

  // Check the power state
  if (isPowerOn) {
    // Read accelerometer values
    sensors_event_t event;
    accel.getEvent(&event);

    // Rotate acceleration readings and convert to position change
    float accelY = event.acceleration.y * cosAngle - event.acceleration.z * sinAngle;
    float accelZ = event.acceleration.y * sinAngle + event.acceleration.z * cosAngle;

    // Calculate time difference
    unsigned long currentTime = millis();
    float deltaTime = (currentTime - prevTime) / 1000.0;  // Convert to seconds

    // Update position coordinate using integration
    zPos += (accelZ * deltaTime * deltaTime) / 2.0;

    // Check for deviation perpendicular to the writing direction
    if (abs(accelZ) > 4.0) {
      digitalWrite(ledPin, HIGH);  // Turn on LED to indicate deviation
      if (!deviationOccurred) {
        // Print position coordinate if deviation just occurred
        Serial.print("Deviation occurred! Z position: ");
        Serial.println(zPos);
        deviationOccurred = true;
      }
    } else {
      digitalWrite(ledPin, LOW);   // Turn off LED
      deviationOccurred = false;   // Reset deviation flag
    }

    // Update previous time
    prevTime = currentTime;
  } else {
    // Turn off LED and reset position when power is off
    digitalWrite(ledPin, LOW);
    zPos = 0.0;
  }

  delay(100);  // Adjust delay as needed
}