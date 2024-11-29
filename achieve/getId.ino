/***************************************************
 * 湖南创乐博智能科技有限公司
 * name: Sound Controlled Servo
 * function: Control the angle of a servo motor based on the sound sensor input.
 * When the sound sensor detects a sound level above a certain threshold, the servo motor will move to a specific angle.
 ********************************************************/

#include <Servo.h>

const int ledPin = 13; // pin13 built-in led
const int soundPin = A0;  // sound sensor attach to A0
Servo myservo; // create servo object to control a servo

void setup()
{
  pinMode(ledPin, OUTPUT); // set ledPin as OUTPUT
  Serial.begin(9600); // initialize the serial communication as 9600 bps
  myservo.attach(9); // attach the servo on pin 9 to servo object
  myservo.write(0); // back to 0 degrees 
  delay(1000); // wait for a second
}

void loop()
{
  int value = analogRead(soundPin); // read the value of sound sensor
  Serial.println(value); // print it

  if (value > 600) // if the value of sound sensor is greater than 600
  {
    digitalWrite(ledPin, HIGH); // turn on the led
    myservo.write(90); // move servo to 90 degrees
    delay(200); // delay 200ms
  }
  else
  {
    digitalWrite(ledPin, LOW); // turn off the led
    myservo.write(0); // move servo back to 0 degrees
  }
}