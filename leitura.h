#include <Arduino.h>

double lerSensoresLinha()
{
  int x1 = analogRead(sensorDireita);
  int x2 = analogRead(sensorDireitaMeio);
  int x3 = analogRead(Meio);
  int x4 = analogRead(sensorEsquerda);
  int x5 = analogRead(sensorEsquerdaMeio);

  return ((x1 + x2 + x3 + x4 + x5)/5);
};

void sensoresIR()
{
  IR1 = analogRead(sensorDireita);
  IR2 = analogRead(sensorDireitaMeio);
  IR3 = analogRead(Meio);
  IR4 = analogRead(sensorEsquerda);
  IR5 = analogRead(sensorEsquerdaMeio);
};

long SensoresDeCor()
{
  long C1 = analogRead(SensorCorDireita);
  long C2 = analogRead(SensorCorEsquerda);

  return (C1 + C2)/2;
};

long erro1(){
  sensoresIR();
  return abs(IR1 - IR2); //Sensores IR Direita  
}

long erro2(){
  sensoresIR();
  return abs(IR4 - IR5); //Sensores IR Esquerda
}
