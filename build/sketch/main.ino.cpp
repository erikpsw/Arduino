#include <Arduino.h>
#line 1 "e:\\programming\\Arduino\\Hello_world\\main\\main.ino"
#line 1 "e:\\programming\\Arduino\\Hello_world\\main\\main.ino"
/************************************************/
// 湖南创乐博智能科技有限公司
#include <Servo.h>
/************************************************/
Servo myservo; // create servo object to control a servo
/************************************************/
#define MAX 255    
int val = 0;
float range = 180.0;

#line 11 "e:\\programming\\Arduino\\Hello_world\\main\\main.ino"
void setup();
#line 19 "e:\\programming\\Arduino\\Hello_world\\main\\main.ino"
void loop();
#line 11 "e:\\programming\\Arduino\\Hello_world\\main\\main.ino"
void setup()
{
  myservo.attach(9); // attach the servo on pin 9 to servo object
  myservo.write(0); // back to 0 degrees 
  delay(1000); // wait for a second
  Serial.begin(9600); // initialize the serial communication as 9600 bps
}
/*************************************************/
void loop()
{
  val = analogRead(A0); // read the value from the potentiometer
  float p = ((float)val) / 1023.0; // normalize the value to a range of 0 to 1
  float inter = range * p; // scale the value to the desired range
  Serial.println(1000 / (2 * inter)); // print the scaled value
  myservo.write(inter); // set the servo position based on the scaled value
  delay(1000); // wait for a second
}
/**************************************************/
