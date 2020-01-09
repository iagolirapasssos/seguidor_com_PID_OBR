#include <Arduino.h>

int lerSensoresCor()
{  
  long Erro1 = erro1();
  long Erro2 = erro2();
  
  Serial.print(Erro1);
  Serial.print(", ");
  Serial.print(Erro2);
  Serial.print(", ");
  Serial.print(IR3);
  Serial.println("");
  
//Verificar se foi detectado VERDE no lado ESQUERDO
  if(Erro2 > 8 && Erro2 < 11 && Erro1 < 13 && IR3 > 200)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      long Erro1 = erro1();
      long Erro2 = erro2();
      
        if(Erro2 > 8 && Erro2 < 11 && Erro1 < 13 && IR3 > 200)
        {  
          Serial.println("Verde E1");
          LedsAlerta(2, 150);
          delay(500);
          LedsAlerta(4, 0);
          return 1;
        }
  }
//Verificar se foi detectado VERDE no lado DIREITO
  else if(Erro1 > 15 && Erro1 < 18 && Erro2 < 8  && IR3 > 200)
  {
      mover(0, 0);
      pausa(400);
      controle(1, 0, 0);
      long Erro1 = erro1();
      long Erro2 = erro2();
  
      mover(0, 0);
      pausa(500);
      
        if(Erro1 > 15 && Erro1 < 18 && Erro2 < 8  && IR3 > 200)
        {
            Serial.println("Verde D1");
            LedsAlerta(2, 150);
            delay(300);
            LedsAlerta(4, 0);
            return 2;
        }
  }
  //Curva 90 a esquerda
  else if(Erro2 > 50 && Erro2 < 380 && Erro1 < 11 && IR3 < 40)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 > 50 && Erro2 < 380 && Erro1 < 11 && IR3 < 40)
    {
      Serial.println("Curva 90 a esquerda");
      LedsAlerta(3, 150);
      delay(500);
      return 11;
    }
  }
  //Curva 90 a direita
  else if(Erro2 < 8 && Erro1 > 200 && Erro1 < 380 && IR3 < 40)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 < 8 && Erro1 > 200 && Erro1 < 380 && IR3 < 40)
    {
      Serial.println("Curva 90 a direita");
      LedsAlerta(3, 150);
      delay(500);
      return 22;
    }
  }
  //Encruzilhada
  else if(Erro2 > 50 && Erro1 > 200 && IR3 > 300)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 > 50 && Erro1 > 200 && IR3 > 300)
    {
      Serial.println("Encruzilhada");
      LedsAlerta(3, 150);
      delay(500);
      return 111;
    }
  }
  //T
  else if(Erro2 > 50 && Erro1 > 200 && IR3 < 200)
  {
    mover(0, 0);
    pausa(400);
    controle(1, 0, 0);
    mover(0, 0);
    pausa(400);
    
    long Erro1 = erro1();
    long Erro2 = erro2();

    if(Erro2 > 50 && Erro1 > 200 && IR3 < 200)
    {
      Serial.println("T");
      LedsAlerta(3, 150);
      return 120;
    }
  }
  else
  {
    return 999;
  }

  LedsAlerta(4, 0);
}

void curvas()
{
  
int x = lerSensoresCor(); 
//Serial.print("x=");
//Serial.print(x);
//Serial.println("");
  switch (x)
  {
    case 1:
        Serial.println("Verde verde verde Esquerda");
        //Frente
          mover(0, 0);
          pausa(300);
          
          controle(1, 0, 2.0);
          mover(0, 0);
          pausa(300);
        
        //Esquerda 90
          while(1)
          {
            PID(kP, kI, kD, PWM, media);
            if(lerSensoresCor() == 999) break;
          }
          mover(0, 0);
          pausa(250);
        //Ré
          mover(0, 0);
          pausa(250);
          controle(-1, 0, 2);
          mover(0, 0);
          pausa(250);
          break;
    case 2:
        Serial.println("Verde verde verde Direita");
        mover(0, 0);
          pausa(300);
        //Frente
          controle(1, 0, 2);
          mover(0, 0);
          pausa(300);
            
        //Direita 90
          while(1)
          {
            PID(kP, kI, kD, PWM, media);
            if(lerSensoresCor() == 999) break;
          }
          mover(0, 0);
          pausa(250);
          
        //Ré 
          //Ré
          mover(0, 0);
          pausa(250);
          controle(-1, 0, 2);
          mover(0, 0);
          pausa(250);
          break;
     case 11:
          //pção para CURVA em 90 GRAUS para ESQUERDA:
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
       
          //LOOP 1: Ir para frente enquanto a função não retorna 999
          while(1)
          {
            controle(1, 0, 10.0);
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
            if(IR3 > 200) break;
            //if(lerSensoresCor() == 999) break;
          }
          
          mover(0, 0);
          pausa(300);
          break;
     case 22:
     //pção para CURVA em 90 GRAUS para DIREITA:
          
          //Pausa real de 500 ms
          mover(0, 0);
          pausa(500);
       
          //LOOP 1: Ir para frente enquanto a função não retorna 999
          while(1)
          {
            controle(1, 0, 10.0);
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
            if(IR3 > 200) break;
            //if(lerSensoresCor() == 999) break;
          }
          
          mover(0, 0);
          pausa(300);
          break;
     case 999:
          LedsAlerta(4, 150);
          PID(kP, kI, kD, PWM, media);
          break;
    case 111:
          mover(60, 60);
          pausa(200);
          break;
    case 120:
          mover(60, 60);
          pausa(200);
          break;
  }
};
