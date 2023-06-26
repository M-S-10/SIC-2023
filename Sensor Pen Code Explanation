## Code Explanation

This code is written for a sensor pen that detects deviations from writing in a straight line using an accelerometer. It provides real-time feedback by illuminating an LED when a deviation is detected.

### Libraries
The code includes the following libraries:

```cpp
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <math.h>
```

These libraries provide the necessary functionality for working with the accelerometer sensor and performing mathematical calculations.

### Constants and Variables
The code defines the following constants and variables:

```cpp
const int ledPin = 13;       // Pin for the red LED
const int buttonPin = 2;     // Pin for the push button

float zPos = 0.0;            // Z position coordinate
unsigned long prevTime = 0;  // Previous time
bool deviationOccurred = false;  // Flag to track deviation occurrence
bool isPowerOn = false;      // Flag to track power state
```

- `ledPin` and `buttonPin` define the Arduino pins used for the LED and push button, respectively.
- `zPos` represents the Z position coordinate.
- `prevTime` stores the previous time value.
- `deviationOccurred` is a boolean flag that tracks whether a deviation has occurred.
- `isPowerOn` is a boolean flag that tracks the power state.

### Accelerometer Initialization
The accelerometer is initialized using the following code:

```cpp
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
```

The `accel` object of type `Adafruit_ADXL345_Unified` is created and initialized with a unique identifier.

### Rotation Conversion Factors
The code defines the following conversion factors for rotated orientation:

```cpp
const float angleRad = 150 * (PI / 180.0);
const float cosAngle = cos(angleRad);
const float sinAngle = sin(angleRad);
```

- `angleRad` stores the angle of rotation in radians.
- `cosAngle` and `sinAngle` store the cosine and sine values of `angleRad`, respectively.

### Setup Function
The `setup()` function is called once when the microcontroller starts. It performs the following tasks:

```cpp
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
```

- It initializes the Serial Monitor for debugging purposes.
- It sets the LED pin as an output and turns off the LED.
- It sets the push button pin as an input with a pull-up resistor.
- It initializes the accelerometer using `accel.begin()`. If the accelerometer is not detected, an error message is printed to the Serial Monitor.

### Loop Function
The `loop()` function is the main part of the code that runs repeatedly. It performs the following tasks:

```cpp
void loop() {
  // Check if the button is pressed to toggle power supply
  if (digitalRead(buttonPin) == LOW) {
    isPowerOn = !isPowerOn;  // Toggle power state
    delay(200);  // Deb

ounce delay
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
```

- It checks if the button is pressed to toggle the power supply.
- If the power is on, it reads the accelerometer values and performs the necessary calculations.
- It rotates the acceleration readings based on the conversion factors.
- It updates the position coordinate (`zPos`) using integration.
- It checks for deviations perpendicular to the writing direction by comparing the absolute value of `accelZ` with a threshold value.
- If a deviation is detected, it turns on the LED and prints the current position coordinate to the Serial Monitor.
- If no deviation is detected, it turns off the LED and resets the deviation flag.
- If the power is off, it turns off the LED and resets the position coordinate to 0.0.
- It includes a delay of 100 milliseconds at the end of each iteration to adjust the loop speed.

That's the explanation of the provided code. It initializes the necessary components, reads accelerometer data, calculates position changes, and detects deviations from writing in a straight line using a sensor pen.
