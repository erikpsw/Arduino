#define MAX 255    
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
int val = 0;
void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  Serial.begin(9600);
}
float range = 50.0;
void loop() {
    val = analogRead(A0);
    float p = ((float)val) / 1023.0;
    float inter = range * p;
    Serial.println(1000 / (2*inter));
    setColor(MAX, MAX, MAX, inter);
    setColor(0, 0, 0, inter);
}
void setColor(int red, int green, int blue, float inter)
{
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
    delay(inter);
}
