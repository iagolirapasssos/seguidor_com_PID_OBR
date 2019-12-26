#include "Arduino.h"
#include "config.h"
#include "acao.h"

void setup() {
  //Comunicação serial
  Serial.begin(9600);

  //Ponte H
  pinMode(MotorDireitoFrente, OUTPUT);
  pinMode(MotorDireitoTras, OUTPUT);
  pinMode(MotorEsquerdoFrente, OUTPUT);
  pinMode(MotorEsquerdoTras, OUTPUT);

  //Sensores de linha
  pinMode(sensorDireita, INPUT);
  pinMode(sensorDireitaMeio, INPUT);
  pinMode(Meio, INPUT);
  pinMode(sensorEsquerda, INPUT);
  pinMode(sensorEsquerdaMeio, INPUT);

  //Leds de alerta
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedAzul, OUTPUT);
}

     
void loop() {
  //PID(kP, kI, kD, PWM, media);
 // curvas();
 lerSensoresCor();
   Serial.print("IR1: ");
   Serial.print(IR1);
   Serial.print(", ");
   Serial.print("IR2: ");
   Serial.print(IR2);
   Serial.print(", ");
   Serial.print("IR3: ");
   Serial.print(IR3);
   Serial.print(", ");
   Serial.print("IR4: ");
   Serial.print(IR4);
   Serial.print(", ");
   Serial.print("IR5: ");
   Serial.print(IR5);
   Serial.println("");
  //lerSensoresCor();
  }
