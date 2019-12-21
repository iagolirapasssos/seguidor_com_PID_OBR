//Sensores IR de linha
#define sensorDireita A2
#define sensorDireitaMeio A1
#define Meio A0
#define sensorEsquerda A4
#define sensorEsquerdaMeio A3

//Ponte H
#define MotorDireitoFrente 3
#define MotorDireitoTras 2
#define MotorEsquerdoFrente 4
#define MotorEsquerdoTras 5

//Leds de alerta
#define LedVermelho 12
#define LedVerde 11
#define LedAzul 10

//Sensores de cor
#define SensorCorDireita A9
#define SensorCorEsquerda A8

//Constantes
double lastError = 0;
double motorD, motorE;
double P, I = 0.0, D, ganho;


void setup() {
  //Comunicação serial
  Serial.begin(9600);

  //Ponte H
  pinMode(MotorDireitoFrente, OUTPUT);
  pinMode(MotorDireitoTras, OUTPUT);
  pinMode(MotorEsquerdoFrente, OUTPUT);
  pinMode(MotorEsquerdoTras, OUTPUT);

  //Sensores de linha
  pinMode(sensorDireita, INPUT);
  pinMode(sensorDireitaMeio, INPUT);
  pinMode(Meio, INPUT);
  pinMode(sensorEsquerda, INPUT);
  pinMode(sensorEsquerdaMeio, INPUT);

  //Leds de alerta
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedAzul, OUTPUT);
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

void mover(int a, int b) {
  if (a > 0) {
    //a=a*2.55;
    //a=a+compensacao;
    analogWrite(MotorEsquerdoFrente, a);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else if (a == 0) {
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else {

    //a=a*-2.55;
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, abs(a));
  }
  if (b > 0) {
    // b=b*2.55;
    analogWrite(MotorDireitoFrente, b);
    analogWrite(MotorDireitoTras, 0);
  }
  else if (b == 0) {
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, 0);
  }
  else {
    //b=b*-2.55;
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, abs(b));
  }
}


void PID (double kP, double kI, double kD, double tP, int media) 
{
  int erro = lerSensoresLinha() - media;


  P = kP * erro;
  I = kI * (I + erro);
  D = kD * (erro - lastError);

  ganho = P + I + D;

  lastError = erro;

  motorE = tP + ganho; //Motor Esquerdo
  motorD = tP - ganho; //Motor Direito

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
void loop() {
  int kP = 1.20;
  int kI = 0.8;//0.1;
  int kD = 60.0;//1.0;
  LedsAlerta(1, 150);
  delay(300);
  LedsAlerta(4, 150);

  LedsAlerta(2, 150);
  delay(300);
  LedsAlerta(4, 150);

  LedsAlerta(3, 150);
  delay(300);
  LedsAlerta(4, 150);
  //Serial.println(analogRead(SensorCorEsquerda));
  //PID(kP, kI, kD, 60, 93);
  //Serial.println(lerSensoresLinha());
  //Serial.println(analogRead(Meio));
}
