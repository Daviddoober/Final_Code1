#include <SR04.h>
#include <Servo.h>

// === SERVO SETUP ===
Servo RIGHTservo;
Servo LEFTservo;

int Left_servo_pin = 9;
int Right_servo_pin = 10;

int L_servo_stop = 89;
int R_servo_stop = 91;
int servo_slow = 5;

// === ULTRASONIC SETUP ===
int TRIG_PIN = 11;
int ECHO_PIN = 12;
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long DistanceValue;

// === RGB LED PINS ===
int redPin = 7;
int greenPin = 6;
int bluePin = 5;

void setup() {
  RIGHTservo.attach(Right_servo_pin);
  LEFTservo.attach(Left_servo_pin);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  // Read ultrasonic distance
  DistanceValue = sr04.Distance();
  Serial.print(DistanceValue);
  Serial.print(" cm  ");

  // === CONDITIONAL ACTIONS ===

  // STOP: object between 9–11 cm
  if (DistanceValue >= 9 && DistanceValue <= 11) {
    Serial.println("Stop");
    RIGHTservo.write(R_servo_stop);
    LEFTservo.write(L_servo_stop);
    setColor(255, 0, 0); // Red
    delay(500);
  }

  // FORWARD: object between 11–100 cm
  else if (DistanceValue > 11 && DistanceValue <= 100) {
    Serial.println("Forward");
    RIGHTservo.write(R_servo_stop - servo_slow);
    LEFTservo.write(L_servo_stop + servo_slow);
    setColor(0, 255, 0); // Green
    delay(100);
  }

  // BACKWARD: object closer than 9 cm
  else if (DistanceValue < 9) {
    Serial.println("Backward");
    RIGHTservo.write(R_servo_stop + servo_slow);
    LEFTservo.write(L_servo_stop - servo_slow);
    setColor(0, 0, 255); // Blue
    delay(100);
  }

  // SEEKING: object too far or not seen
  else {
    Serial.println("Seeking");
    RIGHTservo.write(R_servo_stop - servo_slow);
    LEFTservo.write(L_servo_stop - servo_slow);
    setColor(255, 0, 255); // Purple
    delay(200);
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
