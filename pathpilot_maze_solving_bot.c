#include <ESP32Servo.h>

// Motor pins
const int IN1 = 27;
const int IN2 = 26;
const int IN3 = 25;
const int IN4 = 33;

// Ultrasonic pins
const int trigPin = 18;
const int echoPin = 19;

// Servo pin
const int servoPin = 13;
Servo myServo;

// PID variables
float targetDistance = 40;  // Ideal distance to keep
float Kp = 1.2, Ki = 0.01, Kd = 0.5;
float integral = 0, previousError = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  myServo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// Basic distance reading
long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  return (duration > 0) ? duration * 0.034 / 2 : -1;
}

// Averaged distance reading
long readAverageDistance(int samples = 5) {
  long total = 0;
  int validSamples = 0;

  for (int i = 0; i < samples; i++) {
    long d = readDistance();
    if (d > 0 && d < 300) {  // Filter out invalid data
      total += d;
      validSamples++;
    }
    delay(20); // Short delay between samples
  }

  return (validSamples > 0) ? total / validSamples : -1;
}

// Movement functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Center scan
  myServo.write(90);
  delay(300);
  long center = readAverageDistance();
  Serial.print("Center (avg): "); Serial.println(center);

  // PID Calculation
  float error = targetDistance - center;
  integral += error;
  float derivative = error - previousError;
  float output = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  output = constrain(output, -255, 255); // Clamp PID output
  Serial.print("Output: "); Serial.println(output);

  // Behavior decision
  if (center == -1) {
    moveForward();  // Sensor failed — assume safe
    delay(600);
    stopMoving();
    delay(200);
  } else if (center > 30) {
    moveForward();  // Safe distance
    delay(600);
    stopMoving();
    delay(200);
  } else if (center < 30) {
    stopMoving();
    delay(200);

    // Side scan
    myServo.write(165);
    delay(400);
    long left = readAverageDistance();

    myServo.write(25);
    delay(400);
    long right = readAverageDistance();

    Serial.print("Left (avg): "); Serial.println(left);
    Serial.print("Right (avg): "); Serial.println(right);

    if (left > right) {
      myServo.write(90);
      delay(30);
      turnLeft();
      delay(270);
      stopMoving();
    } else if (right > left) {
      myServo.write(90);
      delay(30);
      turnRight();
      delay(370);
      stopMoving();
    } else {
      // Dead end
      myServo.write(90);
      delay(30);
      turnRight();
      delay(340);
      stopMoving();
    }
  }

  myServo.write(90); // Reset servo
  delay(100);
}

this is my code. Make appropriate changes to the readme file
