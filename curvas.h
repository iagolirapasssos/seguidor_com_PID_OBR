#include <Arduino.h>

int lerSensoresCor()
{  
      
  long Erro1 = erro1(); //Sensores da direita
  long Erro2 = erro2(); //Sensores da esquerda
  
//Verificar se foi detectado VERDE no lado ESQUERDO
  if(Erro2 > ErrosVerdeEsquerda[0] && Erro2 < ErrosVerdeEsquerda[1] && 
     Erro1 > ErrosVerdeEsquerda[2] && Erro1 < ErrosVerdeEsquerda[3] && IR3 > 100)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      mover(0, 0);
      pausa(400);
      
      long Erro1 = erro1();
      long Erro2 = erro2();
      
        if(Erro2 > ErrosVerdeEsquerda[0] && Erro2 < ErrosVerdeEsquerda[1] && 
           Erro1 > ErrosVerdeEsquerda[2] && Erro1 < ErrosVerdeEsquerda[3] && IR3 > 100)
        {  
          Serial.println("Verde E1");
          LedsAlerta(2, 500);
          delay(500);
          //LedsAlerta(4, 0);
          return 1;
        }
  }
//Verificar se foi detectado VERDE no lado DIREITO
  else if(Erro2 > ErrosVerdeDireita[0] && Erro2 < ErrosVerdeDireita[1] && 
          Erro1 > ErrosVerdeDireita[2] && Erro1 < ErrosVerdeDireita[3] && IR3 > 100)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      mover(0, 0);
      pausa(400);
      
      long Erro1 = erro1();
      long Erro2 = erro2();
      
        if(Erro2 > ErrosVerdeDireita[0] && Erro2 < ErrosVerdeDireita[1] && 
           Erro1 > ErrosVerdeDireita[2] && Erro1 < ErrosVerdeDireita[3] && IR3 > 100)
        {
            Serial.println("Verde D1");
            LedsAlerta(2, 500);
            delay(500);
            //LedsAlerta(4, 0);
            return 2;
        }
  }
  
  //Curva 90 a ESQUERDA
  else if(Erro2 > Erros90Esquerda[0] && Erro2 < Erros90Esquerda[1] && 
          Erro1 > Erros90Esquerda[2] && Erro1 < Erros90Esquerda[3] && IR3 < 40)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      mover(0, 0);
      pausa(400);
      
      long Erro1 = erro1();
      long Erro2 = erro2();
  
      if(Erro2 > Erros90Esquerda[0] && Erro2 < Erros90Esquerda[1] && 
            Erro1 > Erros90Esquerda[2] && Erro1 < Erros90Esquerda[3] && IR3 < 40)
      {
          Serial.println("Curva 90 a esquerda");
          LedsAlerta(3, 150);
          delay(500);
          return 11;
      }
  }
  
  //Curva 90 a DIREITA
  else if(Erro2 > Erros90Direita[0] && Erro2 < Erros90Direita[1] && 
          Erro1 > Erros90Direita[2] && Erro1 < Erros90Direita[3] && IR3 < 40)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      mover(0, 0);
      pausa(400);
      
      long Erro1 = erro1();
      long Erro2 = erro2();
  
      if(Erro2 > Erros90Direita[0] && Erro2 < Erros90Direita[1] && 
         Erro1 > Erros90Direita[2] && Erro1 < Erros90Direita[3] && IR3 < 40)
      {
          Serial.println("Curva 90 a direita");
          LedsAlerta(3, 150);
          delay(500);
          return 22;
      }
  }
  
  //Encruzilhada
  else if(Erro2 > ErrosEncruzilhada[0] && Erro1 > ErrosEncruzilhada[2] && IR3 > 100)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 > ErrosEncruzilhada[0] && Erro1 > ErrosEncruzilhada[2] && IR3 > 100)
    {
      Serial.println("Encruzilhada");
      LedsAlerta(3, 500);
      delay(500);
      return 111;
    }
  }
  //T
  else if(Erro2 > ErrosT[0] && Erro1 > ErrosT[2] && IR3 < 200)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 > ErrosT[0] && Erro1 > ErrosT[2] && IR3 < 200)
    {
      Serial.println("T");
      LedsAlerta(3, 500);
      return 120;
    }
  }
  else
  {
    return 999;
  }

  LedsAlerta(4, 0);
}

void curvas90Direita()
{
  //pção para CURVA em 90 GRAUS para DIREITA:
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
       
          //LOOP 1: Ir para frente enquanto a função não retorna 999
          while(1)
          {
            controle(1, 0, m1);
            if(lerSensoresCor() == 999) break;
          }
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
        
        /*LOOP 2: No loop 1 o robô foi deslocado para frente em x metros.
         *Agora faremos com que o robô vire para a direita até que o 
         *sensor do meio (IR3) detecte preto.
         */
          while(1)
          {
            //PID(kP, kI, kD, PWM, media);
            controle(0, -1, 0.0);
            sensoresIR();
            if(IR3 > 180) {
              mover(0, 0);
              pausa(400); 
              break; 
            }
            //if(lerSensoresCor() == 999) break;
          }

        //Voltar um pouco
          mover(0, 0);
          pausa(400);
          controle(-1, 0, 4.0);
          mover(0, 0);
          pausa(400);
}

void curvas90Esquerda()
{
  //pção para CURVA em 90 GRAUS para ESQUERDA:
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
       
          //LOOP 1: Ir para frente enquanto a função não retorna 999
          while(1)
          {
            controle(1, 0, m2);
            if(lerSensoresCor() == 999) break;
          }
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
        
        /*LOOP 2: No loop 1 o robô foi deslocado para frente em x metros.
         *Agora faremos com que o robô vire para a esquerda até que o 
         *sensor do meio (IR3) detecte preto.
         */
          while(1)
          {
            //PID(kP, kI, kD, PWM, media);
            controle(0, 1, 0.0);
            sensoresIR();
            if(IR3 > 180) {
              mover(0, 0);
              pausa(400); 
              break; 
            }
            //if(lerSensoresCor() == 999) break;
          }
          
        //Voltar um pouco
          mover(0, 0);
          pausa(400);
          controle(-1, 0, 4.0);
          mover(0, 0);
          pausa(400);
}

void curvas()
{

switch (lerSensoresCor())
{
case 1:
    curvas90Esquerda();
    break;
case 2:
    curvas90Direita();
    break;
case 11:
    curvas90Esquerda();
    break;
case 22:
    curvas90Direita();
    break;
case 111:
    mover(60, 60);
    pausa(200);
    break;
case 120:
    mover(60, 60);
    pausa(200);
    break;
case 999:
    //LedsAlerta(4, 150);
    PID(kP, kI, kD, PWM, media);
    break;
}};
