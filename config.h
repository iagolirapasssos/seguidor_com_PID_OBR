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
double UltimoError = 0.0;
double motorD, motorE;
double P, I = 0.0, D, ganho;

//Velocidade (PWM) da ponte H: 12 V
int vd = 80;    //Direita
int ve = 80;    //Esquerda
int vf = 90;    //Frente
int vr = 90;    //Ré
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
  int kI = 0.8;//0.1;
  int kD = 60.0;//1.0;
  int PWM = 60;
  int media = 100;
