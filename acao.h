#include <Arduino.h>

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

//Função para obter pausas reais
unsigned long pausa(int tempo){
unsigned long time_now = 0;
  time_now = millis();
   
   
    while(millis() < time_now + tempo){
        //Espera em ms
    }
}

double lerSensoresLinha()
{
  int x1 = analogRead(sensorDireita);
  int x2 = analogRead(sensorDireitaMeio);
  int x3 = analogRead(Meio);
  int x4 = analogRead(sensorEsquerda);
  int x5 = analogRead(sensorEsquerdaMeio);

  return ((x1 + x2 + x3 + x4 + x5)/5);
}

void sensoresIR()
{
  IR1 = analogRead(sensorDireita);
  IR2 = analogRead(sensorDireitaMeio);
  IR3 = analogRead(Meio);
  IR4 = analogRead(sensorEsquerda);
  IR5 = analogRead(sensorEsquerdaMeio);
}

long SensoresDeCor()
{
  long C1 = analogRead(SensorCorDireita);
  long C2 = analogRead(SensorCorEsquerda);

  return (C1 + C2)/2;
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
   int temp = 20;

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
        mover(0,0);
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

long erro1(){
  sensoresIR();
  return abs(IR1 - IR2); //Sensores IR Direita  
}

long erro2(){
  sensoresIR();
  return abs(IR4 - IR5); //Sensores IR Esquerda
}

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
  
  //Verde esquerdo
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
  //Verde direita
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
    long Erro1 = erro1();
    long Erro2 = erro2();

    mover(0, 0);
    pausa(500);
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
    long Erro1 = erro1();
    long Erro2 = erro2();

    mover(0, 0);
    pausa(500);
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
    long Erro1 = erro1();
    long Erro2 = erro2();

    mover(0, 0);
    pausa(500);
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
    long Erro1 = erro1();
    long Erro2 = erro2();

    mover(0, 0);
    pausa(500);
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
        //Frente
          mover(0, 0);
          pausa(500);

          while(1)
          {
            controle(1, 0, 10.0);
            if(lerSensoresCor() == 999) break;
          }
          mover(0, 0);
          pausa(500);
        
        //Esquerda 90
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
          
//        //Ré
//          mover(0, 0);
//          pausa(250);
//          controle(-1, 0, 2);
//          mover(0, 0);
//          pausa(250);
          break;
     case 22:
          mover(0, 0);
          pausa(500);
        //Frente
          controle(1, 0, 10.0);
          mover(0, 0);
          pausa(300);
            
        //Direita 90
          while(1)
          {
            controle(0, -1, 0.0);
            sensoresIR();
            if(IR3 > 200) break;
            //PID(kP, kI, kD, PWM, media);
            //if(lerSensoresCor() == 999) break;
          }
          mover(0, 0);
          pausa(300);
          
        //Ré
          mover(0, 0);
          pausa(250);
          controle(-1, 0, 2);
          mover(0, 0);
          pausa(250);
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
}
