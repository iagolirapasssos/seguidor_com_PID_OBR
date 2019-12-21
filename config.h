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

//Sensores de cor
#define SensorCorDireita A9
#define SensorCorEsquerda A8

//Constantes
double UltimoError = 0.0;
double motorD, motorE;
double P, I = 0.0, D, ganho;
