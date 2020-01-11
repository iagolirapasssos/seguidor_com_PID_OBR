#include <Arduino.h>

void controle(int x, int y, int n){
  /* Tensão de teste: ~12 V e 9800 mA
   * Baterias testadas: Ultrafire e BF 
   * 
   *  Linha reta: Frente e ré
   *  x = 1 => 2 cm +- 1cm 
   *  x = 2 => 3 cm +- 1cm  
   *  x > 2 consiste em um grande erro
   *  
   *  
   * Curvas: direita90 e esquerda90
   * n = 5 => 90 graus
   * n = 10 => 180 graus
   * 
   * Direções: convenção dextrógira
   * x = 0 e y = 1 => Esquerda
   * x = 0 e y = -1 => Direita
   * x = 1 e y = 0 => Frente
   * x = -1 e y = 0 => ré
   */
   int temp = 5;

  if(x == 0 && y == 1) 
  {
    int count2 = 0;
    while(count2 <= n)
    {
        mover(-ve90, vd90);
        pausa(temp);
        mover(0, 0);
        count2+=1;
    } 
  }

  else if(x == 0 && y == -1)
  {
    int count2 = 0;
    while(count2 <= n)
    {
        mover(ve90, -vd90);
        pausa(temp);
        mover(0, 0);
        count2+=1;
    }
  }

  else if(x == 1 && y == 0)
  {
    int count2 = 0;
    while(count2 <= n)
    {
        mover(vf, vf);
        pausa(temp);
        mover(0, 0);
        count2+=1;
    }
  }

  else if(x == -1 && y == 0)
  {
    int count2 = 0;
    while(count2 <= n)
    {
        mover(-vf, -vf);
        pausa(temp);
        mover(0, 0);
        count2+=1;
    }
  }
}

int UltimoError = 0;
int Ilast = 0;
void PID (double kP, double kI, double kD, double PWM, int media) 
{
  int erro = lerSensoresLinha() - media;
  
  P = kP * erro;
  I = Ilast + kI * (I + erro);
  D = kD * (erro - UltimoError);

  ganho = P + I + D;
  
  UltimoError = erro;
  Ilast = I;

  motorE = PWM + ganho; //Motor Esquerdo
  motorD = PWM - ganho; //Motor Direito
  
  mover(motorE, motorD);
  
}
