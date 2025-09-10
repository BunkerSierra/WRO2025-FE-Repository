#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

volatile int Contador = 0;

const int STBY = 8;

float pid, salida, h, tk, tk_1, error, u_error, I, D;
float Kp = 12, Ki = 0, Kd = 15;  // Kp = 12, Ki = 0, Kd = 15; 150  7.95v

// Motor A
const int PWMA = 12;
const int AIN1 = 10;
const int AIN2 = 11;

Servo SvD;
MPU6050 mpu;

///////////////////////////// Giro
//Angulos
float Gy = 0;
float Angle = 0;
int Grados = 0;

//MPU-6050 da los valores en enteros de 16 bits
//Valores RAW
int16_t GyX, GyY, GyZ = 0;

long tiempo_prev = 0;
float dt = 0;

//SUS
const int triggerPin1 = 31;
const int echoPin1 = 37;

const int echoPin2 = 35;

const int triggerPin3 = 4;
const int echoPin3 = 5;

float distance1 = 0;
float distance2 = 0;
float distance3;

#define PotVel A8
float VelRedu = 1;

int Cont = 0;
int ContAnterior = 0;
bool izq = false;

void dir(int Vi, int Vf, int T) {
  if (Vi < Vf) {
    for (int pos = Vi; pos <= Vf; pos += 1) {
      SvD.write(pos);
      delay(T);
    }
  } else {
    for (int pos = Vi; pos >= Vf; pos -= 1) {
      SvD.write(pos);
      delay(T);
    }
  }
}

void setup() {
  /*while (!Serial) {
    delay(1);
  }*/
  pinMode(3, INPUT_PULLUP);
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(triggerPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), inter, RISING);
  // attachInterrupt(digitalPinToInterrupt(19), Gyro, CHANGE);

  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // Inicializamos motores apagados
  digitalWrite(STBY, LOW);

  SvD.attach(A1);  // Pin 1

  delay(50);

  mpu.initialize();

  // Verifica si la conexión fue exitosa
  if (mpu.testConnection()) {
    Serial.println("MPU-6050 conectado correctamente");
    tone(49, 244, 125);
    delay(625);
  } else {
    Serial.println("Error en la conexión del MPU-6050");
    tone(49, 800, 125);
    delay(625);
  }


  SvD.write(91.5);

  digitalWrite(40, 1);
  delay(200);
  digitalWrite(40, 0);
  delay(200);
  digitalWrite(41, 1);
  delay(200);
  digitalWrite(41, 0);

  delay(500);
  tone(49, 240, 125);
  digitalWrite(45, 1);

  while (digitalRead(23) == 0) {
    //Serial.print(".");
    delay(50);
  }
  //VelRedu = map(A8, 0, 1080, 0.3, 1);
  //Serial.println(VelRedu);
  tone(49, 587, 125);
  digitalWrite(45, 0);

  Serial.begin(9600);
  delay(125);

  inicio(90);
}

////////////////////////////////////////////////////////////////

void inicio(int dis) {
  Angle = 0;
  
  moverMotor(150);
  while (distance2 < dis && distance1 < dis) { twoSUS(40); }

  tone(49, 783, 125);
  SvD.write(91.5);

  distance3 = 100;
  moverMotor(120);
  while (distance3 >= 64) {
    SUS3();
    delay(10);
  }
  detenerMotores();

  tone(49, 110, 125);

  if (distance1 > 90) {
    izq = true;
  } else if (distance2 > 90) {
    izq = false;
  }

  digitalWrite(40, 1);
  delay(500);
  dir(91, 161, 8);
  delay(100);
  moverMotor(180);
  //Serial.println("Der");                      DERECHA
  while (Angle <= 87) { Gyro(1); }

  detenerMotores();
  tone(49, 3951, 125);
  delay(500);
  dir(161, 91, 8);

  delay(500);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {

  Serial.write('Z');

  deteccion('D');
  delay(10000000000000);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void deteccion(char caso) {

  delay(200);
  MotorEnc(-150, 245);
  detenerMotores();

  if (Serial.available() > 0 || caso != NULL) {

    char toSend = (char)Serial.read();
    if (toSend == 'N') {

    } else if (toSend == 'B' || caso == 'B') {  ////////////// Caso B VERDE VERDE
      detenerMotores();
      digitalWrite(41, 1);
      tone(49, 987, 125);
      delay(125);
      digitalWrite(41, 0);
      tone(49, 880, 125);
      delay(125);
      digitalWrite(41, 1);
      tone(49, 698, 125);
      delay(125);
      digitalWrite(41, 0);
      tone(49, 987, 125);
      delay(125);
      tone(49, 880, 125);

      EsqVerde1();

      MotorEnc(150, 1520);
      tone(49, 110, 125);

      inicio(111);

    }
    //////////////////////////////////////// Abajo

    else if (toSend == 'A' || caso == 'A') {  ////////////  Caso A  ROJO ROJO

      detenerMotores();
      digitalWrite(40, 1);
      tone(49, 698, 125);
      delay(125);
      digitalWrite(40, 0);
      tone(49, 880, 125);
      delay(125);
      digitalWrite(40, 1);
      tone(49, 987, 125);
      delay(125);
      digitalWrite(40, 0);
      tone(49, 698, 125);
      delay(125);
      tone(49, 880, 125);

      EsqRojo1();

      ContAnterior = Contador;
      delay(63);
      moverMotor(120);

      /////////////////////////////////////////////////
      PDPM(12, 0, 1, 900, 0, 12);
      SvD.write(91.5);
      Angle = 0;
      /////////////////////////////////////////////////

      detenerMotores();
      delay(200);

      moverMotor(120);
      while (distance2 < 90 && distance1 < 90) { twoSUS(40); }
      tone(49, 783, 125);
      MotorEnc(120, 320);
      tone(49, 110, 125);

      if (distance1 > 90) {
        izq = true;
      } else if (distance2 > 90) {
        izq = false;
      }
    }

    else if (toSend == 'C' || caso == 'C') {  ///////////// Caso C ROJO VERDE
      detenerMotores();
      digitalWrite(40, 1);
      tone(49, 987, 125);
      delay(125);
      tone(49, 880, 125);
      delay(125);
      digitalWrite(40, 0);
      tone(49, 698, 125);
      delay(125);
      digitalWrite(41, 1);
      tone(49, 880, 125);
      delay(125);
      digitalWrite(41, 0);
      tone(49, 987, 125);

      EsqRojoVerde1();
    }

    else if (toSend == 'D' || caso == 'D') {  ///////////// Caso D VERDE ROJO

      EsqVerdeRojo1();

      tone(49, 329, 125);
    }
  }
}


/*
  while (true) {}

  ///////////////////////////////////////
  SUS3();
  moverMotor(AIN1, AIN2, PWMA, 150);
  detenerMotores();
  tone(49, 3951, 125);
  delay(200);

  Angle = 0;
  dir(91, 49, 8);
  delay(125);
  moverMotor(AIN1, AIN2, PWMA, -130);
  while (Angle <= 45) { Gyro(1); }
  detenerMotores();
  tone(49, 110, 125);

  delay(125);
  dir(49, 91, 8);
  delay(125);
  Angle = 0;
  ContAnterior = Contador;
  moverMotor(AIN1, AIN2, PWMA, -130);
  while (Contador <= (ContAnterior + 320)) { Derecho(); }
  detenerMotores();

  delay(125);
  Angle = 0;
  dir(91, 49, 8);
  delay(125);
  moverMotor(AIN1, AIN2, PWMA, -130);
  while (Angle <= 45) { Gyro(1); }
  detenerMotores();
  tone(49, 110, 125);

  /////////////////////////////////////////
  while (true) {}

  delay(35);*/