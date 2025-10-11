#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

Servo hipRight, hipLeft, kneeRight, kneeLeft;

const int trigPin = 8;
const int echoPin = 9;

MPU6050 mpu;
bool systemStarted = false;
bool isDancing = false;
String command = "";

void setup() {
  Serial.begin(9600);
  hipRight.attach(3);
  hipLeft.attach(5);
  kneeRight.attach(6);
  kneeLeft.attach(10);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Wire.begin();
  mpu.initialize();

  standNeutral();
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "start") {
      systemStarted = true;
      standNeutral();
    } else if (command == "stop") {
      systemStarted = false;
      sitDown();
    } else if (systemStarted) {
      if (command == "start walking") walkSteps(10);
      else if (command == "turn left") turnLeft();
      else if (command == "turn right") turnRight();
      else if (command == "u turn") {
        turnRight(); turnRight();
        turnRight(); turnRight();
      }
      else if (command == "dance") isDancing = true;
      else if (command == "stop dance") isDancing = false;
    }
  }

  if (systemStarted) {
    if (detectObstacle()) {
      avoidObstacle();
    }

    if (isDancing) {
      danceRoutine();
    }
  }
}

void standNeutral() {
  hipRight.write(90);
  hipLeft.write(90);
  kneeRight.write(90);
  kneeLeft.write(90);
}

void sitDown() {
  hipRight.write(0);
  hipLeft.write(0);
  kneeRight.write(0);
  kneeLeft.write(0);
}

void walkSteps(int steps) {
  for (int i = 0; i < steps; i++) {
    // Right leg forward
    hipRight.write(60);
    kneeRight.write(120);
    delay(400);
    standNeutral();
    delay(300);

    // Left leg forward
    hipLeft.write(60);
    kneeLeft.write(120);
    delay(400);
    standNeutral();
    delay(300);
  }
}

void turnRight() {
  // Rotate right by alternating foot positions
  hipRight.write(60);
  kneeRight.write(120);
  hipLeft.write(120);
  kneeLeft.write(60);
  delay(500);
  standNeutral();
  delay(300);
}

void turnLeft() {
  hipLeft.write(60);
  kneeLeft.write(120);
  hipRight.write(120);
  kneeRight.write(60);
  delay(500);
  standNeutral();
  delay(300);
}

void danceRoutine() {
  hipRight.write(60);
  kneeRight.write(120);
  delay(300);
  standNeutral();
  delay(300);
  hipLeft.write(60);
  kneeLeft.write(120);
  delay(300);
  standNeutral();
  delay(300);
}

bool detectObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance < 20;
}

void avoidObstacle() {
  Serial.println("Obstacle Detected! Avoiding...");

  // Step 1: Turn right 90° (4x turnRight)
  for (int i = 0; i < 4; i++) {
    turnRight();
  }

  // Step 2: Walk along the obstacle
  int steps = 0;
  while (detectObstacle()) {
    walkSteps(1);
    steps++;
    delay(200);
  }

  // Step 3: Buffer distance (6 steps)
  walkSteps(6);

  // Step 4: Turn left 90°
  for (int i = 0; i < 4; i++) {
    turnLeft();
  }

  // Step 5: Continue walking forward
  walkSteps(steps + 6);
}
