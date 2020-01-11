#include <Arduino.h>

void testeErro()
{
  long Erro1 = erro1(); //Sensores da direita
  long Erro2 = erro2(); //Sensores da esquerda

  Serial.print("Erro1: ");
  Serial.print(Erro1);
  Serial.print(", Erro2: ");
  Serial.print(Erro2);
  Serial.print(", IR3: ");
  Serial.print(IR3);
  Serial.print(", Média IRs: ");
  Serial.print(lerSensoresLinha());
  Serial.println("");
};
