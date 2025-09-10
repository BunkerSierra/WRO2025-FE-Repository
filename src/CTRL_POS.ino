#define EncoderA 2
#define EncoderB 3
#define M1 5
#define M2 6

#define pot A0

volatile int pos = 0;
long lastT = 0;
float lastE = 0;
float integralE = 0;
float kp = 0.9, ki = 0.001, kd = 0.025;

void setup() {
  Serial.begin(9600);
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);
  pinMode(pot, INPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(EncoderA), RE, RISING);
}

void loop() {
  avanzar(-1200);
  delay(1000);
  retroceder(1200);
  delay(1000);
}
void reset() {
  pos = 0;
  lastT = 0;
  lastE = 0;
  integralE = 0;
}

void avanzar(int pulsos) {
  int sp = pulsos;
  while (pos > sp) {
    long currentT = micros();
    float deltaT = ((float)(currentT - lastT)) / 1.0e6;
    lastT = currentT;

    int error = sp - pos;
    float deDt = (error - lastE) / (deltaT);
    integralE = integralE + error * deltaT;

    float PID = (kp * error) + (kd * deDt) + (ki * integralE);

    float pwm = fabs(PID);
    if (pwm > 255) {
      pwm = 255;
    }

    int dir = 1;
    if (PID < 0) {
      dir = -1;
    }

    motorC(dir, pwm);

    lastE = error;
    Serial.print(sp);
    Serial.print(" ");
    Serial.print(pos);
    Serial.println();
  }
}
void retroceder(int pulsos) {
  int sp = pulsos;
  while (pos < sp) {
    long currentT = micros();
    float deltaT = ((float)(currentT - lastT)) / 1.0e6;
    lastT = currentT;

    int error = sp - pos;
    float deDt = (error - lastE) / (deltaT);
    integralE = integralE + error * deltaT;

    float PID = (kp * error) + (kd * deDt) + (ki * integralE);

    float pwm = fabs(PID);
    if (pwm > 255) {
      pwm = 255;
    }

    int dir = 1;
    if (PID < 0) {
      dir = -1;
    }

    motorC(dir, pwm);

    lastE = error;
    Serial.print(sp);
    Serial.print(" ");
    Serial.print(pos);
    Serial.println();
  }
}

void motorC(int dir, int enable) {
  if (dir == 1) {
    analogWrite(M1, enable);
    analogWrite(M2, 0);
  }
  else if (dir == -1) {
    analogWrite(M1, 0);
    analogWrite(M2, enable);
  }
  else {
    analogWrite(M1, 0);
    analogWrite(M2, 0);
  }
}

void RE() {
  int b = digitalRead(EncoderB);
  if (b > 0) {
    pos++;
  }
  else {
    pos--;
  }
}
