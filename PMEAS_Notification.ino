#include <SoftwareSerial.h>

#define BUTTON_PIN 4
#define LED_PIN 2
#define BUZZER_PIN 3
#define LED2_PIN 5
#define BUZZER2_PIN 6

SoftwareSerial SIM900A(9, 10); // 9 as Rx || 10 as Tx

void setup()
{
  SIM900A.begin(9600);  // GSM Module Baud rate - communication speed
  Serial.begin(9600);   // Baud rate of Serial Monitor in the IDE app
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  Serial.println("Text Message Module Ready & Verified");
  delay(100);
}

void SendMessage()
{
  SIM900A.println("AT+CMGF=1");                     // Text Mode initialization
  delay(1000);
  SIM900A.println("AT+CMGS=\"+919618531821\"\r");  // Receiver's Mobile Number
  delay(1000);
  SIM900A.println("PATIENT MEDICAL EMERGENCY ALERT SYSTEM"); // Message content
  delay(100);
  SIM900A.println((char)26); // character 26 is used to indicate the end of the message content
  delay(1000);
}

void SendCall()
{
  Serial.println("Calling through GSM Modem");

  // set the data rate for the SoftwareSerial port
  SIM900A.begin(9600);
  delay(2000);
  SIM900A.println("ATD8978722723;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  Serial.println("Called ATD8978722723");
  // print response over serial port
  if (SIM900A.available())
    Serial.write(SIM900A.read());
}

void loop()
{
  byte buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW)
  {
    Serial.println("Button is pressed");

    // Blink LEDs and sound buzzers as long as the button is pressed
    while (digitalRead(BUTTON_PIN) == LOW)
    {
      digitalWrite(LED_PIN, HIGH);     // Turn on the LED 1
      digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer 1
      digitalWrite(LED2_PIN, HIGH);    // Turn on the LED 2
      digitalWrite(BUZZER2_PIN, HIGH); // Turn on the buzzer 2
      delay(500);                      // Wait for 500ms
      digitalWrite(LED_PIN, LOW);      // Turn off the LED 1
      digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer 1
      digitalWrite(LED2_PIN, LOW);     // Turn off the LED 2
      digitalWrite(BUZZER2_PIN, LOW);  // Turn off the buzzer 2
      delay(500);                      // Wait for 500ms
    }

    // Send SMS if the button was held for more than 10 seconds
    if (millis() > 10000)
    {
      SendCall();
      SendMessage();
    }
  }

  delay(100);

  if (SIM900A.available() > 0) // checks if there is any data available to be read from the SoftwareSerial object
    Serial.write(SIM900A.read()); // monitor the response from the GSM module for debugging or verification purposes
}