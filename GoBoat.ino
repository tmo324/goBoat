#include "IRremote.h"
#include <SoftwareSerial.h>
#include <dht.h>

#include <Wire.h>
#include <Servo.h>
#define address 0x1E //0011110b, I2C 7bit address of HMC5883

byte servoPin = 7; // thruster
Servo servo;

dht DHT;
char key;

int In1 = 7;
int In2 = 6;
int In3 = 5;
int In4 = 4;

int redPin = 10;
int greenPin = 9;
int bluePin = 8;

#define DHT11_PIN 11


void setup()
{
  Serial.begin(57600);
  Serial.println("Boat Turned On");

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println("Testing here");
}



void loop()
{
  if (Serial.available()) {
    key = (char)Serial.read();
    switch (key) {

      case 'w':
        Serial.println("Printing w");
        forward();
        setColor(0, 255, 0); // Green Color
        break;

      case 's':
        Serial.println("Printing s");
        backward();
        setColor(255, 255, 255); // White Color
        break;

      case 'a':
        Serial.println("Printing LEFT");
        left();
        break;

      case 'd':
        Serial.println("Printing RIGHT");
        right();
        break;

      case 'o':
        Serial.println("Going straight");
        straight();
        break;

      case 'p':
        Serial.println("Stopping everthing");
        stopEverything();
        setColor(255, 0, 0); // Red Color
        break;

      case "t":
        checkDHT()
    }
  }
}






////////////NAVITAGION FUNCTIONS BEGIN HERE/////////////////////////
//////////////////////////////////////////////////////////////////
void forward() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}
void backward() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
}

void straight() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void stopEverything() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void right() {
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void left() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void checkDHT() {
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("°C");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println("%");
}


void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
