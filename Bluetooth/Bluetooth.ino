/* 
 *  Written by Rupak Poddar
 *  www.youtube.com/RupakPoddar
 *  www.github.com/RupakPoddar
 *  This code does not support speed control. For speed control, download the "BluetoothCarWithSpeedControl.ino" sketch.
*/

#include<SoftwareSerial.h>
#define LED 13              // Connect light to pin 13 (Optional)
#define BUZZER 12        // Connect buzzer to pin 12 (Optional)
#define MOTOR_1A 7   // Connect motor driver input 1 to pin 11
#define MOTOR_1B 6   // Connect motor driver input 2 to pin 10
#define MOTOR_2A 9     // Connect motor driver input 3 to pin 9
#define MOTOR_2B 8     // Connect motor driver input 4 to pin 6
#define TX 2                 // Connect Bluetooth module Tx to pin 2
#define RX 3                 // Connect Bluetooth module Rx to pin 3
#define PWMmotor1 5
#define PWMmotor2 10

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
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  String readString;
  
  while(BTmodule.available()) {
    readString = BTmodule.readString();
    Serial.print("Received: ");
    Serial.println(readString);
  }
                                                                                       // FORWARD
  if(readString == "f"){
    digitalWrite(MOTOR_1A, LOW);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, HIGH);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM1);
    analogWrite(PWMmotor2, valuePWM1);
  }
                                                                                       // BACKWARD
  if(readString == "b"){
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, LOW);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, HIGH);
    analogWrite(PWMmotor1, valuePWM1);
    analogWrite(PWMmotor2, valuePWM1);
  }
                                                                                       // LEFT
  if(readString == "l"){
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, LOW);
    digitalWrite(MOTOR_2A, HIGH);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM2);
    analogWrite(PWMmotor2, valuePWM2);
  }
                                                                                       // RIGHT
  if(readString == "r"){
    digitalWrite(MOTOR_1A, LOW);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, HIGH);
    analogWrite(PWMmotor1, valuePWM2);
    analogWrite(PWMmotor2, valuePWM2);
  }
                                                                                       // STOP
  if(readString == "s"){
    digitalWrite(MOTOR_1A, HIGH);
    digitalWrite(MOTOR_1B, HIGH);
    digitalWrite(MOTOR_2A, LOW);
    digitalWrite(MOTOR_2B, LOW);
    analogWrite(PWMmotor1, valuePWM1);
    analogWrite(PWMmotor2, valuePWM1);
  }
                                                                                       // LED ON
  if(readString == "LED_ON"){
    digitalWrite(LED, HIGH);
  }
                                                                                       // LED OFF
  if(readString == "LED_OFF"){
    digitalWrite(LED, LOW);
  }
                                                                                       // SOUND
  if(readString == "SOUND"){
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
                                                                                       // AUX
  if(readString.substring(0, 3) == "aux"){
    int auxVal = readString.substring(3).toInt();
    
    // Print the value of aux button pressed, ranging from 1-8
    Serial.print("Aux ");
    Serial.println(auxVal);
  }
}