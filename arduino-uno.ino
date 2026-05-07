#define MOTOR_BAL_1 0
#define MOTOR_BAL_2 1
#define MOTOR_FORWARD 2
#define SERVO_FLAP 3
#define IR_BACK_1 A0
#define IR_BACK_2 A1
#define IR_TOP A2 // assumed pin
#define ULTRASONIC_FRONT_TRIG 8
#define ULTRASONIC_FRONT_ECHO 9
#define ULTRASONIC_BOTTOM_TRIG 10
#define ULTRASONIC_BOTTOM_ECHO 11
#define MOTOR_BACK 4
#include <Servo.h>
Servo flapServo;
// === Constants ===
const int obstacleThreshold = 20; // in cm
int flapNeutral = 90;
int flapOffset = 60; // stronger angle for direction change
unsigned long lastFlapChange = 0;
bool flapState = false;
// === Setup ===
void setup() {
 pinMode(MOTOR_BAL_1, OUTPUT);
 pinMode(MOTOR_BAL_2, OUTPUT);
 pinMode(MOTOR_FORWARD, OUTPUT);
 pinMode(MOTOR_BACK, OUTPUT);
 pinMode(IR_BACK_1, INPUT);
 pinMode(IR_BACK_2, INPUT);
 pinMode(IR_TOP, INPUT);
 pinMode(ULTRASONIC_FRONT_TRIG, OUTPUT);
 pinMode(ULTRASONIC_FRONT_ECHO, INPUT);
 pinMode(ULTRASONIC_BOTTOM_TRIG, OUTPUT);
 pinMode(ULTRASONIC_BOTTOM_ECHO, INPUT);
 flapServo.attach(SERVO_FLAP);
 flapServo.write(flapNeutral);
 Serial.begin(9600);
}
// === Utility Functions ===
long readUltrasonicCM(int trigPin, int echoPin) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 long duration = pulseIn(echoPin, HIGH, 20000); // 20ms timeout
 if (duration == 0) return 999;
 return duration * 0.034 / 2;
}
void moveForward() {
 digitalWrite(MOTOR_FORWARD, HIGH);
 digitalWrite(MOTOR_BACK, LOW);
}
void moveBackward() {
 digitalWrite(MOTOR_FORWARD, LOW);
 digitalWrite(MOTOR_BACK, HIGH);
}
void stopMotors() {
 digitalWrite(MOTOR_FORWARD, LOW);
 digitalWrite(MOTOR_BACK, LOW);
}
// === Main Loop ===
void loop() {
 long distFront = readUltrasonicCM(ULTRASONIC_FRONT_TRIG,
ULTRASONIC_FRONT_ECHO);
 long depth = readUltrasonicCM(ULTRASONIC_BOTTOM_TRIG,
ULTRASONIC_BOTTOM_ECHO);
 bool irBackDetected = digitalRead(IR_BACK_1) == LOW ||
digitalRead(IR_BACK_2) == LOW;
 bool irTopDetected = digitalRead(IR_TOP) == LOW;
 bool frontObstacle = (distFront > 0 && distFront <
obstacleThreshold);
 Serial.print("Front Distance: "); Serial.print(distFront);
Serial.println(" cm");
 Serial.print("Depth: "); Serial.print(depth); Serial.println(" cm");
 if (frontObstacle || irBackDetected) {
 Serial.println("Obstacle at front or back → Moving Back");
 moveBackward();
 delay(300);
 stopMotors();
 } else if (irTopDetected) {
 Serial.println("Obstacle at top → Moving Forward");
 moveForward();
 delay(300);
 stopMotors();
 } else {
 Serial.println("Path clear → Proceeding with timed direction
change");
 moveForward();
 if (millis() - lastFlapChange > 5000) {
 if (!flapState) {
 flapServo.write(flapNeutral + flapOffset);
 flapState = true;
 lastFlapChange = millis();
 } else if (millis() - lastFlapChange > 2000) {
 flapServo.write(flapNeutral - flapOffset);
 flapState = false;
 lastFlapChange = millis();
 }
 }
 }
 delay(100);
