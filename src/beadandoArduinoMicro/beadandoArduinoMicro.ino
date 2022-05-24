#include <Servo.h>

#define led 2 // digital out
#define rLed 8 // digtal out
#define motorEnable1 3 // pwm out
#define motorIn1 4 // digital out
#define motorIn2 7 // digital out
#define horn 5 // pwm out
#define steeringPin 6 // pwm out
#define usEcho 9 // digital out
#define usTrigger 10// digital in

// motor
#define n 0 // egyhelyben
#define f 1 // előre
#define b 2 // hátra

// kanyarodás
#define m 0 // középen
#define l 1 // bal
#define r 2 // jobb

bool hornState;
bool radarState;

Servo steering;
int motorSpeed;
int motorState;
int steeringState;

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  motorSpeed = 0;
  motorState = n;
  steeringState = m;
  hornState = false;
  radarState = false;
  pinMode(motorEnable1, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(horn, OUTPUT);
  pinMode(usEcho, INPUT);
  pinMode(usTrigger, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  pinMode(rLed, OUTPUT);
  steering.attach(steeringPin);
  
  change();
}

int counter = 0;
void loop() {
  
  
  if (Serial1.available()) {
    String line = Serial1.readString();
    interpret(line);
    change();
  }
  if (motorState == b) {
    float distance = measureDistance();
    if (distance != 0) {
      if (counter > distance * 5) {
        counter = 0;
        radarState = !radarState;
        setHorn();
      }
      else {
        counter++;
        Serial.println(counter);
      }
    }
    else {
      radarState = false;
      setHorn();
      counter = 0;
    }
  }
  else counter = 0;
}

void interpret(String line) {
  char c = line[0];
  switch (c) {
    case 'F':
      if (motorState == f) motorState = n;
      else {
        motorState = f;
        radarState = false;
      }
      break;
    case 'B':
      if (motorState == b) {
        motorState = n; radarState = false; 
      }
      else motorState = b; 
      break;
    case 'R':
      if (steeringState == r) steeringState = m;
      else steeringState = r; 
      break;
    case 'L':
      if (steeringState == l) steeringState = m;
      else steeringState = l; 
      break;
    case 'H':
      hornState = !hornState; 
      break;
    default:
      int value = line.toInt();
      if (value == 0) motorSpeed = 0;
      else motorSpeed = map(value, 0, 100, 150, 255);
      break;
  }
}

void change() {
  // motor irányáért felelős
  switch (motorState) {
    case n:
      setStop();
      break;
    case f:
      setForward();
      break;
    case b:
      setBackward();
      break;
  }

  // kormányzásért felelős
  switch (steeringState) {
    case m:
      setMiddle();
      break;
    case l:
      setLeft();
      break;
    case r:
      setRight();
      break;
  }

  setHorn();
}

void setHorn() {
  if (hornState || radarState) {
    if (hornState && radarState) {
      analogWrite(horn, 200);
    }
    else {
      analogWrite(horn, 50);
    }
  }
  else {
    analogWrite(horn, 0);
  }
}

float measureDistance() {
  digitalWrite(usTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(usTrigger, LOW);
  float duration_us = pulseIn(usEcho, HIGH, 20000);
  float distance_cm = duration_us * 0.017;
  return distance_cm;
}

void setRight() {
  steering.write(45);
}

void setMiddle() {
  steering.write(90);
}

void setLeft() {
  steering.write(135);
}

void setForward() {
  digitalWrite(motorEnable1, LOW);
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  setMotorSpeed();
  digitalWrite(rLed, LOW);
}

void setBackward() {
  digitalWrite(motorEnable1, LOW);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  setMotorSpeed();
  digitalWrite(rLed, HIGH);
}

void setStop() {
  digitalWrite(motorEnable1, LOW);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(rLed, LOW);
}

void setMotorSpeed() {
  // megj.: 150-255 a megengedett sebesség. mert különben nem megy
  // megj.: a motorSpeed változót külön kell beállítani
  analogWrite(motorEnable1, motorSpeed);
}
