///////////////////////////////////////////////////////////////
long duration3 = 0;
void SUS3() {
  digitalWrite(triggerPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;
  //Serial.println(distance3);
}

void calibrateGyroZ() {
  float sum = 0;
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    mpu.update();
    sum += mpu.getGyroZ();
    delay(5);
  }
  gyroZOffset = sum / CALIBRATION_SAMPLES;
  Serial.print("Gyro Z Offset: ");
  Serial.println(gyroZOffset, 6);
}

void GradoZ() {
  mpu.update();

  if (calibrated) {
    unsigned long currentTime = millis();
    float deltaTime = (currentTime - lastTime) / 1000.0;  // Tiempo en segundos
    lastTime = currentTime;

    if (deltaTime > 0.1) deltaTime = 0.01;  // Limitar deltaTime máximo

    // Obtener velocidad angular Z (grados/segundo) y aplicar offset
    float gyroZRate = mpu.getGyroZ() - gyroZOffset;

    // INTEGRAR para obtener el ángulo: ángulo = velocidad angular × tiempo
    yaw += gyroZRate * deltaTime;

    // Mantener el yaw en el rango 0-360 grados
    if (yaw <= -360) yaw = 0;
    if (yaw >= 360) yaw = 0;
  }

  delay(10);  // Pequeña pausa para estabilidad
}

///////////////////////////////////////////////////////////
long duration1 = 0;
long duration2 = 0;
void twoSUS(int T) {
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print("d1: ");
  Serial.println(distance1);

  delay(T);

  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  Serial.print("d2: ");
  Serial.println(distance2);
  delay(T);
}


/////////////////////////////////////////////////
void Derecho(float Kp, float Ki, float Kd) {
  SvD.write(92);
  float pid = 0, error = 0, u_error = 0, I = 0, D = 0;
  unsigned long lastPIDTime = millis();
  unsigned long ciclos = 1;
  Contador = 0;
  distance3 = 52;

  // Resetear el integrador al inicio
  I = 0;
  u_error = 0;
 
    SUS3();

    GradoZ();
    error = (0 + global)- yaw;

    // Calcular delta time apropiado para PID
    unsigned long currentTime = millis();
    float deltaTime = (currentTime - lastPIDTime) / 1000.0;
    lastPIDTime = currentTime;

    // Limitar deltaTime para evitar problemas
    if (deltaTime > 0.1 || deltaTime <= 0) {
      deltaTime = 0.01;
    }

    // Término integral CORREGIDO (sin división por ciclos)
    I = I + (error * deltaTime);

    // Limitar el término integral para evitar windup
    I = constrain(I, -50, 50);

    // Término derivativo
    D = (error - u_error) / deltaTime;

    // Calcular PID
    pid = (error * Kp) + (I * Ki) + (D * Kd);
    u_error = error;
    ciclos++;

    constrain(pid, -20, 40);
    Serial.println(pid);
    SvD.write(91.5 + (pid));

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

void Giros(int d, int V) {
  detenerMotores();
  delay(100);
  tone(49, 3520, 125);
  if (d == 1) SvD.write(161);
  else { SvD.write(61); }
  delay(300);
  GradoZ();

  moverMotor(V);
  if (d == 1) {
    float AO = yaw + 71.5;
    while (yaw < AO) {
      GradoZ();
    }
  } else if (d == 2) {
    float AO = yaw - 68.5;
    while (yaw > AO) {
      GradoZ();
    }
  }

  detenerMotores();
  delay(150);
  SvD.write(91.5);
  delay(200);
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

void inter() {
  Contador++;
}

void PDPM(float KP, float KI, float KD, int p, bool d, int r) {
  int ContAnterior2 = 0;
  long PID, H, TK, TK_1, Error = 0, U_Error, I, D, duration1 = 0, duration2 = 0;

  ContAnterior2 = Contador;
  delay(2);
  while (Contador <= (ContAnterior2 + p)) {

    TK = millis();
    H = TK - TK_1;
    if (d == true) {

      digitalWrite(triggerPin1, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin1, LOW);
      duration1 = pulseIn(echoPin1, HIGH);
      distance1 = duration1 * 0.034 / 2;
      delay(1);

      if (distance1 != 0) {
        Error = r - distance1;
      } else {
        digitalWrite(45, 1);
      }

    } else {

      digitalWrite(triggerPin1, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin1, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
      distance2 = duration2 * 0.034 / 2;
      delay(1);

      if (distance2 != 0) {
        Error = distance2 - r;
      } else {
        digitalWrite(45, 1);
      }
    }
    I = I + (Error * H);
    D = (Error - U_Error) / H;
    PID = (Error * KP) + (I * KI) + (D * KD);
    U_Error = Error;
    TK_1 = TK;

    constrain(PID, -15, 35);
    SvD.write(91 + (PID));
  }
  digitalWrite(45, 0);
}

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
