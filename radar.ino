// Radar System Using Ultrasonic Sensor and Arduino
// Author: Lakki Thejesh Kumar
// Project: Mini Project - B.E. ECE (AI & ML)
// Vel Tech Rangarajan Dr. Sagunthala R&D Institute

#include <Servo.h>

// Pin definitions
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int SERVO_PIN = 6;

Servo radarServo;

long duration;
int distance;
int angle;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  radarServo.attach(SERVO_PIN);
  delay(1000);
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (angle = 0; angle <= 180; angle++) {
    radarServo.write(angle);
    delay(30);
    distance = measureDistance();
    printData(angle, distance);
  }

  // Sweep from 180 to 0 degrees
  for (angle = 180; angle >= 0; angle--) {
    radarServo.write(angle);
    delay(30);
    distance = measureDistance();
    printData(angle, distance);
  }
}

int measureDistance() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  int dist = duration * 0.034 / 2;

  // Limit range to 40cm
  if (dist > 40) dist = 40;

  return dist;
}

void printData(int ang, int dist) {
  // Send data to Processing IDE for radar display
  Serial.print(ang);
  Serial.print(",");
  Serial.print(dist);
  Serial.print(".");
}
