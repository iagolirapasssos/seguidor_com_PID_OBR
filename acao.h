
double lerSensoresLinha()
{
  int x1 = analogRead(sensorDireita);
  int x2 = analogRead(sensorDireitaMeio);
  int x3 = analogRead(Meio);
  int x4 = analogRead(sensorEsquerda);
  int x5 = analogRead(sensorEsquerdaMeio);

  return ((x1 + x2 + x3 + x4 + x5)/5);
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


void PID (double kP, double kI, double kD, double PWM, int media) 
{
  int erro = lerSensoresLinha() - media;


  P = kP * erro;
  I = kI * (I + erro);
  D = kD * (erro - UltimoError);

  ganho = P + I + D;

  UltimoError = erro;

  motorE = PWM + ganho; //Motor Esquerdo
  motorD = PWM - ganho; //Motor Direito

  mover(motorE, motorD);
  
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
    default:
      digitalWrite(LedVermelho, LOW);
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAzul, LOW);
      break;
  }
}
