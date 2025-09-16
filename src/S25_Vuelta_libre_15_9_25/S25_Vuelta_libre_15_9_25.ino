#include <Servo.h>
#include <Wire.h>
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

// Variables para el yaw
float yaw = 0.0;
unsigned long lastTime = 0;
float gyroZOffset = 0.0;

// Para calibración
bool calibrated = false;
const int CALIBRATION_SAMPLES = 500;

volatile int Contador = 0;

const int STBY = 8;

// Motor A
const int PWMA = 12;
const int AIN1 = 10;
const int AIN2 = 11;

Servo SvD;

//SUS
const int triggerPin1 = 31;
const int echoPin1 = 37;

const int echoPin2 = 35;

const int triggerPin3 = 53;
const int echoPin3 = 52;

float distance1 = 0;
float distance2 = 0;
float distance3 = 0;

int Cont = 0;
bool izq = false;

float global = 0;
int CV = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(triggerPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  attachInterrupt(digitalPinToInterrupt(3), inter, RISING);

  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // Inicializamos motores apagados
  digitalWrite(STBY, LOW);

  SvD.attach(A1);  // Pin 1
  delay(50);
  tone(49, 293, 125);
  delay(50);

  SvD.write(92);
  byte status = mpu.begin();
  Serial.print("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) {}

  Serial.println("Calibrando, no mover el sensor...");
  mpu.calcOffsets();  // Calibración interna de la librería
  calibrateGyroZ();   // Calibración adicional específica para Z

  Serial.println("¡Calibración completada!");
  lastTime = millis();
  calibrated = true;

  tone(49, 1000, 125);

  twoSUS(40);
  if (distance1 != 0) {
    digitalWrite(40, 1);
    tone(49, 1760, 125);
    delay(200);
    digitalWrite(40, 0);
    delay(200);
  } else {
    tone(49, 4186, 125);
    delay(125);
    tone(49, 4186, 125);
    delay(125);
    while (true) {}
  }
  if (distance2 != 0) {
    digitalWrite(41, 1);
    tone(49, 1975, 125);
    delay(200);
    digitalWrite(41, 0);
    delay(200);
  } else {
    tone(49, 4186, 125);
    delay(125);
    tone(49, 4186, 125);
    delay(125);
    while (true) {}
  }

  delay(400);
  tone(49, 240, 125);
  digitalWrite(45, 1);

  while (digitalRead(23) == 0) {
    delay(50);
  }

  tone(49, 587, 125);
  digitalWrite(45, 0);

  delay(125);
  SvD.write(91);
  delay(400);
  distance3 = 53;
}

//////////////////////////////////////////////// Bucle principal
void loop() {  // 90 grados = 76.5 grados yaw
  SDLG();
  if (CV == 12) {
    MotorEnc(140,1275);
    delay(300);
    detenerMotores();
    delay(10000000000000000000000000000);
  }
}

////////////////////////////////////////// Función para saber a que lado girar
void SDLG() {
  SUS3();
  Serial.println(distance3);
  delay(10);
  if (distance3 <= 58) {
    detenerMotores();
    SvD.write(91);
    delay(225);
    CV++;
    if (CV == 4 || CV == 8 || CV == 12) {
      global = 0;
      yaw = 0;
    }
    twoSUS(20);
    if (distance2 > distance1) {
      Giros(1, 120);
      global = global + 71.5;
    } else {
      Giros(2, 120);
      global = global - 68.5;
    }
  } else {
    moverMotor(180);
    Derecho(2.96, 0, 0.35);
  }
}

void Estacionarse() {
  detenerMotores();
  tone(49, 3322, 375);
  delay(375);
  MotorEnc(-120, 300);
  moverMotor(120);

  if (izq == true) {
    while (distance1 > 90) {
      twoSUS(30);
      delay(30);
    }
  } else {
    while (distance2 > 90) {
      twoSUS(30);
      delay(30);
    }
  }
  detenerMotores();
  tone(49, 4186, 125);

  MotorEnc(150, 1200);

  tone(49, 2093, 125);
  detenerMotores();

  tone(49, 261, 125);
  delay(125);
  tone(49, 293, 125);
  delay(125);
  tone(49, 329, 375);
  delay(375);
  while (true) {}
}