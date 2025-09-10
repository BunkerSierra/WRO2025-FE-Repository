///////////////////////////////////////////////////////////////
void SUS3() {
  digitalWrite(triggerPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin3, LOW);
  long duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;
}


////////////////////////////////////////////////////////////////
void Gyro(bool A) {

  if (A == true) {
    ContAnterior = Contador;
  }

  //Ratios de conversion
  float A_R = 16384.0;  // 32768/2
  float G_R = 131.0;    // 32768/250

  //Conversion de radianes a grados 180/PI
  float RAD_A_DEG = 57.295779;

  String valores = "";

  //Leer los valores del Giroscopio
  Wire.beginTransmission(0x68);  //Direccion I2C de la IMU
  //delay(2);
  Wire.write(0x43);
  //delay(2);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);       //A partir del 0x43, se piden 6 registros
  GyX = Wire.read() << 8 | Wire.read();  //Cada valor ocupa 2 registros
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  //Calculo del angulo del Giroscopio
  Gy = GyZ / G_R;

  dt = (millis() - tiempo_prev) / 1000.0;
  tiempo_prev = millis();

  //Integración respecto del tiempo para calcular el YAW
  Angle = (Angle + Gy * dt) - 0.001;

  /*valores = "Grado: " + String(Angle);
  Serial.println(valores);*/
  if (A == true) {
    while (Contador <= (ContAnterior + 7)) {}
  }
}


/////////////////////////////////////////////////////////////////
void GiroHGrado(float KP, float KI, float KD, float r) {
  float PID, H, TK, TK_1, Error, U_Error, I, D;

  while (Angle != r) {

    Gyro(1);

    TK = millis();
    h = TK - TK_1;
    Error = r - Angle;

    I = I + (Error * h);
    D = (Error - U_Error) / h;
    PID = (Error * KP) + (I * KI) + (D * KD);
    U_Error = Error;
    TK_1 = TK;

    constrain(PID, -120, 140);
    moverMotor(PID);
  }
}


///////////////////////////////////////////////////////////
void twoSUS(int T) {
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print("distancia 1 es: ");
  Serial.println(distance1);
  delay(T);

  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  Serial.print("distancia 2 es: ");
  Serial.println(distance2);
  delay(T);
}


/////////////////////////////////////////////////
void Derecho() {

  Gyro(0);

  tk = millis();
  h = tk - tk_1;

  error = 0 - Angle;

  I = I + (error * h);
  D = (error - u_error) / h;
  pid = (error * Kp) + (I * Ki) + (D * Kd);
  u_error = error;
  tk_1 = tk;

  constrain(pid, -20, 40);
  SvD.write(91 + (pid));
}


////////////////////////////////////////////////////
void MotorEnc(int velocidad, int pulsos) {
  Contador = 0;
  delay(5);

  digitalWrite(STBY, HIGH);
  if (velocidad > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, constrain(velocidad, 0, 255));
    while (Contador <= pulsos) {}

  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, constrain(-velocidad, 0, 255));
    while (Contador <= pulsos) {}
  }

  detenerMotores();
}


////////////////////////////////////////////////////
void moverMotor(int velocidad) {
  digitalWrite(STBY, HIGH);
  if (velocidad > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    velocidad = -velocidad;
  }
  analogWrite(PWMA, constrain(velocidad, 0, 255));
}



/////////////////////////////////////////////////// Función para detener ambos motores
void detenerMotores() {
  analogWrite(PWMA, 0);
  digitalWrite(STBY, LOW);  // Standby para ahorrar energía
}



/////////////////////////////////////////////////// No usar
void Salida() {
  /*
  moverMotor(AIN1, AIN2, PWMA, -100);
  while (distance3 <= 7) { SUS3(); }
  detenerMotores();*/

  Angle = 0;
  dir(91, 161, 8);
  tone(49, 698, 125);
  delay(100);
  digitalWrite(STBY, HIGH);
  moverMotor(100);
  while (Angle <= 23) {
    Gyro(1);
  }

  Angle = 0;
  dir(161, 61, 8);
  tone(49, 698, 125);
  delay(100);
  digitalWrite(STBY, HIGH);
  moverMotor(-100);
  while (Angle >= -23) { Gyro(1); }
}

void inter() {
  Contador++;
}


void PDPM(float KP, float KI, float KD, int p, bool d, int r) {
  int ContAnterior2 = 0;
  float PID, H, TK, TK_1, Error = 0, U_Error, I, D;

  ContAnterior2 = Contador;
  delay(2);
  while (Contador <= (ContAnterior2 + p)) {

    twoSUS(30);

    TK = millis();
    h = TK - TK_1;
    if (d == true) {
      Error = r - distance1;
    } else {
      Error = distance2 - r;
    }
    I = I + (Error * h);
    D = (Error - U_Error) / h;
    PID = (Error * KP) + (I * KI) + (D * KD);
    U_Error = Error;
    TK_1 = TK;

    constrain(PID, -20, 40);
    SvD.write(91 + (PID));
  }
}