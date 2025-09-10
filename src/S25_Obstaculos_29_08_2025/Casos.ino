//////////////////////////////////////////////////////////// Caso B VERDE VERDE 1
void EsqVerde1() {
  ContAnterior = Contador;
  Angle = 0;
  dir(91, 41, 8);
  delay(800);
  moverMotor(150);
  digitalWrite(40, 1);
  while (Angle >= -45) { Gyro(1); }

  detenerMotores();
  delay(200);
  dir(41, 91, 8);
  delay(200);

  Angle = 0;
  ContAnterior = Contador;
  delay(63);
  MotorEnc(145, 110);

  detenerMotores();
  delay(200);
  dir(91, 144, 8);
  delay(200);

  Angle = 0;
  moverMotor(150);
  while (Angle <= 46) { Gyro(1); }

  detenerMotores();
  delay(200);
  dir(141, 91, 8);
  delay(200);

  Angle = 0;
  ContAnterior = Contador;
  delay(32);
  MotorEnc(140, 220);
  detenerMotores();
  tone(49, 55, 125);
  delay(63);
  tone(49, 123, 125);
  delay(300);
}

//////////////////////////////////////////////////////////// Caso A  ROJO ROJO 1
void EsqRojo1() {
  ContAnterior = Contador;
  Angle = 0;
  dir(91, 161, 8);
  delay(800);
  moverMotor(150);
  digitalWrite(41, 1);
  while (Angle <= 45) { Gyro(1); }

  detenerMotores();
  delay(200);
  SvD.write(91);
  delay(200);

  Angle = 0;
  ContAnterior = Contador;
  delay(63);
  MotorEnc(150, 160);

  detenerMotores();
  delay(200);
  SvD.write(60);
  delay(200);

  Angle = 0;
  moverMotor(120);
  while (Angle >= -45) { Gyro(1); }

  detenerMotores();
  delay(200);
  SvD.write(91);
  delay(200);

  Angle = 0;
  ContAnterior = Contador;
  delay(32);
  MotorEnc(150, 500);
  detenerMotores();
  tone(49, 55, 125);
  delay(63);
  tone(49, 123, 125);
  delay(563);
}

//////////////////////////////////////////////////////////// Caso C ROJO VERDE 1
void EsqRojoVerde1() {
  ContAnterior = Contador;
  Angle = 0;
  dir(91, 161, 8);
  delay(800);
  moverMotor(150);
  digitalWrite(41, 1);
  while (Angle <= 45) { Gyro(1); }

  detenerMotores();
  delay(200);
  SvD.write(91);
  delay(200);

  Angle = 0;
  MotorEnc(150, 180);

  detenerMotores();
  delay(200);
  SvD.write(60);
  delay(200);

  Angle = 0;
  tone(49, 987, 125);
  moverMotor(120);
  while (Angle >= -45) { Gyro(1); }

  detenerMotores();
  delay(175);
  SvD.write(91);
  delay(200);

  Angle = 0;
  MotorEnc(150, 100);
  detenerMotores();

  delay(100);
  SvD.write(60);
  delay(200);
  Angle = 0;
  moverMotor(120);
  while (Angle >= -49) { Gyro(1); }

  detenerMotores();
  delay(175);
  SvD.write(91);
  delay(200);

  Angle = 0;
  ContAnterior = Contador;
  delay(32);
  MotorEnc(150, 710);
  detenerMotores();
  delay(100);
  SvD.write(131);
  delay(200);
  Angle = 0;
  ContAnterior = Contador;
  delay(32);
  moverMotor(125);
  while (Angle <= 50) { Gyro(1); }
  detenerMotores();
  tone(49, 55, 125);
  delay(63);
  tone(49, 123, 125);
  SvD.write(91);
  Angle = 0;
  ContAnterior = Contador;
  delay(563);
}

////////////////////////////////////////////////////////////  Caso D VERDE ROJO 1
void EsqVerdeRojo1() {

  detenerMotores();
  digitalWrite(41, 1);
  tone(49, 261, 125);
  delay(125);
  tone(49, 329, 125);
  delay(125);
  digitalWrite(41, 0);
  tone(49, 415, 125);
  delay(125);
  digitalWrite(41, 1);
  tone(49, 261, 125);
  delay(125);
  digitalWrite(41, 0);
  tone(49, 329, 125);

  EsqVerde1();


  dir(91, 162, 8);  //c - d

  delay(200);
  Angle = 0;
  moverMotor(180);
  while (Angle <= 86) { Gyro(1); }

  detenerMotores();
  delay(175);

  dir(131, 91, 8);  //d - c
  delay(150);

  distance3 = 99;
  moverMotor(140);
  while (distance3 > 33) {
    SUS3();
  }
  detenerMotores();

  delay(100);
  dir(91, 46, 8);  //c - i
  delay(200);
  Angle = 0;

  delay(32);
  moverMotor(180);
  while (Angle >= -88) { Gyro(1); }
  detenerMotores();
  delay(50);
  tone(49, 123, 125);
  dir(61, 91, 8);  //i - c

  MotorEnc(-130, 630);
  detenerMotores();
  delay(150);

  moverMotor(120);
  PDPM(12, 0, 1.07, 1300, 0, 13);
  detenerMotores();
  Angle = 0;
  delay(100);

  tone(49, 783, 125);
  SvD.write(91);

  distance3 = 50;
  moverMotor(125);
  while (distance2 < 90 && distance1 < 90) { twoSUS(40); }
  tone(49, 123, 125);
  detenerMotores();
  delay(100);

  ContAnterior = Contador;
  Contador = 0;
  delay(63);
 // moverMotor(130);
 // delay(75);
 // while (Contador < 350) {
  //  Derecho();
  //  ContAnterior = Contador;
   // while (Contador <= (ContAnterior + 50)) {}
  //}

  distance3 = 50;
  moverMotor(140);
  while (distance3 > 20) {
    SUS3();
    delay(10);
  }
  detenerMotores();
  tone(49, 329, 125);

  delay(200);
  dir(91, 45, 9);
  delay(100);

  delay(32);
  moverMotor(-175);
  while (Angle <= 88) { Gyro(1); }
  detenerMotores();
  delay(160);
  dir(45,91,9);
  delay(200);
}