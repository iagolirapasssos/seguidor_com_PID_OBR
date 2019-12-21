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


/*
   * Tabela de valores de kP, kI e kD para 
   * ddps diferentes da bateria
   * 
   * +--------------+----+----+----+-----+--------------------+
   * |    ddp (V)   | kP | kI | kD | PWM | Média dos sensores |
   * +--------------+----+----+----+-----+--------------------+
   * |12.20 - 12.50 |1.20|0.80|60.0| 60  |        100         |
   * +--------------+----+----+----+-----+--------------------+
   * |10.50 - 11.93 |1.20|0.80|10.0| 60  |        100         |
   * +--------------+----+----+----+-----+--------------------+
   */
  int kP = 1.2;
  int kI = 0.8;//0.1;
  int kD = 60.0;//1.0;
  int PWM = 60;
  int media = 100;
     
void loop() {
  PID(kP, kI, kD, PWM, media);
}
