#include <Arduino.h>
#include <Servo.h>

Servo servo;

// Status LEDs
int green = 3;
int yellow = 4;
int red = 5;

int servoPosition = 0;

void setup()
{
  servo.attach(2);

  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  // switch to red
  digitalWrite(red, HIGH);

  Serial.begin(9600);
  Serial.println("Starting up...");

  // switch to yellow
  delay(500);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);

  // Move servo to 0
  servo.write(0);
  delay(500);

  // switch to green
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
}

// very basic servo sweep
void loop()
{
  for (servoPosition = 0; servoPosition <= 180; servoPosition += 1)
  {
    servo.write(servoPosition);
    delay(30);
  }
  for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1)
  {
    servo.write(servoPosition);
    delay(30);
  }
}