#include <Arduino.h>
#include "config.h"
#include "leitura.h"
#include "acao.h"
#include "controle.h"
#include "curvas.h"

     
void loop(){
  //Serial.println(lerSensoresLinha());
  curvas();
  //PID(kP, kI, kD, PWM, media);
 //lerSensoresCor();
 //LedsAlerta(4, 150);
}
