#include <Arduino.h>

//Função para obter pausas reais
unsigned long pausa(int tempo){
unsigned long time_now = 0;
  time_now = millis();
   
   
    while(millis() < time_now + tempo){
        //Espera em ms
    }
}

void LedsAlerta(int RGB, int power)
{
  switch (RGB)
  {
    case 1:
      analogWrite(LedVermelho, power);
      break;
    case 2:
      analogWrite(LedVerde, power);
      break;
    case 3:
      analogWrite(LedAzul, power);
      break;
    case 4:
      digitalWrite(LedVermelho, LOW);
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAzul, LOW);
      break;
  }
}

void mover(int a, int b) {
  if (a > 0) {
    analogWrite(MotorEsquerdoFrente, a);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else if (a == 0) {
    analogWrite(MotorEsquerdoFrente, 1);
    analogWrite(MotorEsquerdoTras, 1);
  }
  else {
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, abs(a));
  }
  if (b > 0) {
    analogWrite(MotorDireitoFrente, b);
    analogWrite(MotorDireitoTras, 0);
  }
  else if (b == 0) {
    analogWrite(MotorDireitoFrente, 1);
    analogWrite(MotorDireitoTras, 1);
  }
  else {
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, abs(b));
  }
}
