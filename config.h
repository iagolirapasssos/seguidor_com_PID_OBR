#include <Arduino.h>

//Sensores IR de linha
#define sensorDireita A2
#define sensorDireitaMeio A1
#define Meio A0
#define sensorEsquerda A4
#define sensorEsquerdaMeio A3

//Ponte H
#define MotorDireitoFrente 3
#define MotorDireitoTras 2
#define MotorEsquerdoFrente 4
#define MotorEsquerdoTras 5

//Leds de alerta
#define LedVermelho 12
#define LedVerde 11
#define LedAzul 10

//Sensore IR
int IR1, IR2, IR3, IR4, IR5;

//Sensores de cor
#define SensorCorDireita A9
#define SensorCorEsquerda A8

//Constantes
double motorD, motorE;
double P, I = 0.0, D, ganho = 0.0;

//Velocidade (PWM) da ponte H: 12 V
int vd = 80;    //Direita
int ve = 80;    //Esquerda
int vf = 100;    //Frente
int vr = 100;    //Ré
int vd90 = 100; //Direita 90
int ve90 = 100; //Esquerda 90

//PID
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
  int kI = 0.8; //0.01;
  int kD = 0.0; //40.0;
  int PWM = 60;
  int media = 100;

/*ERROS:
   * Declaração de dois vetores com valores
   * mínimos e máximos dos erros.
   * 
   * Ordem dos valores: {Erro2min, Erro2max, Erro1min, Erro1max}
   */

  int ErrosVerdeEsquerda[4] = {5, 16, 4, 9};
  int ErrosVerdeDireita[4] = {0, 3, 0, 4};
  int Erros90Esquerda[4] = {20, 1023, 4, 9};
  int Erros90Direita[4] = {0, 3, 20, 1023};
  int ErrosEncruzilhada[4] = {0, 20, 0, 20};
  int ErrosT[4] = {0, 20, 0, 20};

  //Constantes para seguir em frente nas curvas em 90
  int m1 = 10; 
  int m2 = 10;

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
};
