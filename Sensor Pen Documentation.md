---

## Documentation: Accelerometer-based Deviation Detection System

**Overview:**

The *Accelerometer-based Deviation Detection System* is a hardware and software solution designed to detect deviations in the Z-axis using an ADXL345 accelerometer. It provides real-time monitoring and feedback through an LED indicator. The system calculates the position change based on integrated acceleration readings, allowing for accurate detection of deviations.

**Hardware Components:**

- Arduino board
- ADXL345 accelerometer
- Push button
- LED
- Resistors and wiring connections

**Libraries:**

- `Wire.h`: Allows communication with I2C devices.
- `Adafruit_Sensor.h`: Provides the sensor event structure.
- `Adafruit_ADXL345_U.h`: Enables interaction with the ADXL345 accelerometer.

**Constants:**

- `ledPin`: The pin connected to the LED indicator.
- `buttonPin`: The pin connected to the push button.

**Variables:**

- `zPos`: Represents the calculated Z-axis position coordinate.
- `prevTime`: Tracks the previous time for calculating the time difference.
- `deviationOccurred`: A flag that indicates if a deviation has occurred.
- `isPowerOn`: A flag to track the power state of the system.

**Functions:**

- `setup()`: Initializes the Serial Monitor, LED pin, push button pin, and the ADXL345 sensor.
- `loop()`: Contains the main operations of the program. It reads accelerometer values, calculates the position change, detects deviations, and updates the LED and position variables accordingly.

**Usage:**

The provided code can be utilized in various real-life applications, including:

1. **Motion detection**: The system can detect deviations or abnormal movements in a specific direction, enabling applications like intrusion detection or monitoring of sensitive equipment.
2. **Posture monitoring**: By attaching the accelerometer to a wearable device, the system can track and alert users about incorrect posture or body movements.
3. **Fitness tracking**: The system can monitor body movements during workouts, ensuring proper form and providing feedback on exercise effectiveness.
4. **Industrial safety**: By attaching the system to machinery or equipment, it can detect deviations in movement patterns that may indicate potential malfunctions or safety hazards.
5. **Data collection**: The system can be used to collect data on motion patterns in various scenarios, enabling further analysis and insights.

To adapt the code for specific applications, consider the following modifications:

- Adjust the threshold value (`4.0`) in the `if (abs(accelZ) > 4.0)` statement to set the deviation detection sensitivity.
- Customize the actions taken when a deviation occurs, such as sending notifications, triggering alarms, or logging data.
- Integrate additional sensors or devices to enhance the functionality and broaden the scope of applications.

> Note: This documentation provides a general overview of the code and its potential applications. Further modifications and integration may be necessary to adapt it to specific use cases and requirements.

---
