/* 
 *  Written by Rupak Poddar
 *  www.youtube.com/RupakPoddar
 *  www.github.com/RupakPoddar
 *  This code does not support speed control. For speed control, download the "BluetoothCarWithSpeedControl.ino" sketch.
*/
// #include "SoftPWM.h"
#include<SoftwareSerial.h>
#include <Servo.h>


#define MOTOR_1A 7   // Connect motor driver input 1 to pin 11
#define MOTOR_1B 6   // Connect motor driver input 2 to pin 10
#define MOTOR_2A 12     // Connect motor driver input 3 to pin 9
#define MOTOR_2B 8     // Connect motor driver input 4 to pin 6
#define TX 2                 // Connect Bluetooth module Tx to pin 2
#define RX 3                 // Connect Bluetooth module Rx to pin 3
#define PWMmotor1 5
#define PWMmotor2 11

Servo clawservo,armservo;
int pos = 0;

int valuePWM1=120; // speed motor 1 
int valuePWM2=150; // speed motor 2

SoftwareSerial BTmodule(TX, RX);

void setup() {
  Serial.begin(9600);
  BTmodule.begin(9600);
  BTmodule.setTimeout(10);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT); 
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  clawservo.attach(13);
  // servo1.attach(10);
  armservo.attach(9);
}

void loop() {
  String readString;
  // myservo.detach();
  while(BTmodule.available()) {
    readString = BTmodule.readString();
    Serial.print("Received: ");
    Serial.println(readString);
  }
  // myservo.detach();
                                                                                       // FORWARD
  if(readString == "f"){
    // myservo.detach();
    // pinMode(PWMmotor2, OUTPUT);
    digitalWrite(MOTOR_1A, LOW);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, HIGH);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM1);
    analogWrite(PWMmotor2, valuePWM1);
  }
                                                                                       // BACKWARD
  if(readString == "b"){
    // myservo.detach();
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, LOW);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, HIGH);
    analogWrite(PWMmotor1, valuePWM1);
    analogWrite(PWMmotor2, valuePWM1);
  }
                                                                                       // LEFT
  if(readString == "l"){
    // myservo.detach();
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, LOW);
    digitalWrite(MOTOR_2A, HIGH);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM2);
    analogWrite(PWMmotor2, valuePWM2);
  }
                                                                                       // RIGHT
  if(readString == "r"){
    // myservo.detach();
    digitalWrite(MOTOR_1A, LOW);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, HIGH);
    analogWrite(PWMmotor1, valuePWM2);
    analogWrite(PWMmotor2, valuePWM2);
  }
                                                                                       // STOP
  if(readString == "s"){
    // myservo.detach();
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM2);
    analogWrite(PWMmotor2, valuePWM2);
  }
                                                                                       // LED ON
  if(readString == "aux1"){
    pos += 20;
    clawservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
  //                                                                                      // LED OFF
  if(readString == "aux2"){
    pos -= 20;  
    clawservo.write(pos);
    delay(15);
  }
  if(readString == "aux3"){
    pos += 20;  
    armservo.write(pos);
    delay(15);
  }
  if(readString == "aux4"){
    pos -= 20;  
    armservo.write(pos);
    delay(15);
  }
}