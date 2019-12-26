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
    default:
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

long lerSensoresCor()
{
  sensoresIR();
  
  //long C1 = analogRead(SensorCorDireita);
  //long C2 = analogRead(SensorCorEsquerda);
  //long  Erro = abs(C1 - C2);
  //int xE = IR4 + IR5;
  //int xD = IR1 + IR2;

  //Serial.print(IR3);
  //Serial.print(", ");
  //Serial.print(xD);
  //Serial.print(", ");
  //Serial.println(Erro);
  //Serial.println("");
  
  //Verde esquerdo
  if(IR1 > 0 && IR1 < 25 &&
     IR2 > 0 && IR2 <= 30 &&
     IR4 > 0 && IR4 < 30 &&
     IR5 > 30 && IR5 < 40)
  {
    return 1;
  } 
  else if(
     IR1 > 0 && IR1 < 25 &&
     IR2 > 200 &&
     IR4 > 0 && IR4 < 30 &&
     IR5 > 30 && IR5 < 40)
  {
    return 1;
  }
  else if(
     IR1 > 0 && IR1 <= 25 &&
     IR2 > 0 && IR2 <= 30 &&
     IR4 > 30 && IR4 < 40 &&
     IR5 > 30 && IR5 < 40)
  {
    return 1;
  }
  //Verde direita
  else if(IR1 > 0 && IR1 < 25 &&
     IR2 > 30 && IR2 < 60 &&
     IR4 > 0 && IR4 < 30 &&
     IR5 > 0 && IR5 < 30)
  {
    return 2;
  } 
  else if(IR1 > 0 && IR1 < 25 &&
     IR2 > 30 && IR2 < 60 &&
     IR4 > 0 && IR4 < 30 &&
     IR5 > 200)
  {
    return 2;
  }
  else if(IR1 > 25 && IR1 < 30 &&
     IR2 > 30 && IR2 < 60 &&
     IR4 > 0 && IR4 < 30 &&
     IR5 > 0 && IR5 < 30)
  {
    return 2;
  }
}


void mover(int a, int b) {
  if (a > 0) {
    analogWrite(MotorEsquerdoFrente, a);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else if (a == 0) {
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, 0);
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
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, 0);
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
   int temp = 30;

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


void PID (double kP, double kI, double kD, double PWM, int media) 
{
  int erro = lerSensoresLinha() - media;
  
  P = kP * erro;
  I = kI * (I + erro);
  D = kD * (erro - UltimoError);

  ganho = P + I + D;
  
  UltimoError = erro;

  motorE = PWM - ganho; //Motor Esquerdo
  motorD = PWM + ganho; //Motor Direito

  mover(motorE, motorD);
  
}


void curvas()
{
  sensoresIR();
  int xE = IR4 + IR5;
  int xD = IR1 + IR2;
 
  switch (lerSensoresCor())
  {
    case 1:
        mover(0, 0);
        pausa(500);
        controle(1, 0, 1.0);
        mover(0, 0);
        pausa(500);
     if(lerSensoresCor() == 1)
      {
        LedsAlerta(2, 150);
        pausa(500);
        //Frente
          mover(0, 0);
          pausa(500);
          controle(1, 0, 5.0);
          mover(0, 0);
          pausa(500);
        //Esquerda 90
          controle(0, 1, 15);
          mover(0, 0);
          pausa(500);
      }
      break;
      
    case 2:
      //Frente
        mover(0, 0);
        pausa(500);
        controle(1, 0, 1.0);
        mover(0, 0);
        pausa(500);
      
      if(lerSensoresCor() == 2)
      {
        LedsAlerta(2, 150);
        pausa(500);
        //Frente
          mover(0, 0);
          pausa(500);
          controle(1, 0, 4.0);
          mover(0, 0);
          pausa(500);
        //Esquerda 90
          controle(0, -1, 15);
          mover(0, 0);
          pausa(500);
      }
      break;
     default:
      LedsAlerta(4, 150);
      //PID(kP, kI, kD, PWM, media);
      break;
  }
}
