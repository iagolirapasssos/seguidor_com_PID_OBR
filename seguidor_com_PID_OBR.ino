#include <Arduino.h>
#include "config.h"
#include "leitura.h"
#include "acao.h"
#include "controle.h"
#include "curvas.h"
#include "funcoes_testes.h"
     
void loop(){
  curvas();
  //PID(kP, kI, kD, PWM, media);
  //Serial.println(lerSensoresLinha());
  //testeErro();
}
