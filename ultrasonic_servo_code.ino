#include <Servo.h>

// Pin definitions
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

// Distance threshold in centimeters
const int distanceThreshold = 20;

// Servo positions (0 to 180 degrees)
const int servoClosedPos = 0;
const int servoOpenPos = 90;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(servoClosedPos); // Start at default position
}

void loop() {
  long duration;
  int distance;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Actuate servo based on distance
  if (distance > 0 && distance < distanceThreshold) {
    myServo.write(servoOpenPos);  // Move to open position
  } else {
    myServo.write(servoClosedPos); // Move back to closed position
  }

  delay(200); // Delay between measurements
}
