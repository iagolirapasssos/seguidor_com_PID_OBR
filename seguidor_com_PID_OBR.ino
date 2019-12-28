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

     
void loop(){
  //Serial.println(lerSensoresLinha());
  curvas();
  PID(kP, kI, kD, PWM, media);
 //lerSensoresCor();
  }
