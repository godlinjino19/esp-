#include <ESP32Servo.h>

#define HEAD_SERVO_PIN 13
#define RIGHT_HAND_SERVO_PIN 12
#define LEFT_HAND_SERVO_PIN 14


#define RPWM_1 25
#define LPWM_1 26


#define RPWM_2 32
#define LPWM_2 33

#define EN_PIN 27

Servo headServo;
Servo leftHandServo;
Servo rightHandServo;

void setup() {

  Serial.begin(115200);
  

  
  headServo.attach(HEAD_SERVO_PIN, 500, 2400);
  leftHandServo.attach(LEFT_HAND_SERVO_PIN, 500, 2400);
  rightHandServo.attach(RIGHT_HAND_SERVO_PIN, 500, 2400);

  // Motor Pins
  pinMode(RPWM_1, OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  pinMode(RPWM_2, OUTPUT);
  pinMode(LPWM_2, OUTPUT);

  pinMode(EN_PIN, OUTPUT);

  digitalWrite(EN_PIN, HIGH);

  Serial.println("Robot Ready");
}

void loop() {


  Serial.println("Head Left");
  headServo.write(0);
  delay(1000);

  Serial.println("Head Center");
  headServo.write(90);
  delay(1000);

  Serial.println("Head Right");
  headServo.write(180);
  delay(1000);


  Serial.println("Right  Hand Up");
  leftHandServo.write(90);
  delay(1000);

  Serial.println("Right Hand Down");
  leftHandServo.write(0);
  delay(1000);


  Serial.println("Left Hand Up");
  rightHandServo.write(90);
  delay(1000);

  Serial.println("Left  Hand Down");
  rightHandServo.write(0);
  delay(1000);


  Serial.println("Motors Forward");

  //driveMotor1(128, true);
  //driveMotor2(128, true);

  delay(2000);

  stopMotors();

  delay(1000);


  Serial.println("Motors Reverse");

  //driveMotor1(255, false);
  //driveMotor2(255, false);

  delay(2000);

  stopMotors();

  delay(2000);
}


void driveMotor1(int speed, bool forward)
{
  speed = constrain(speed,0,255);

  if(forward)
  {
    analogWrite(LPWM_1,0);
    analogWrite(RPWM_1,speed);
  }
  else
  {
    analogWrite(RPWM_1,0);
    analogWrite(LPWM_1,speed);
  }
}



void driveMotor2(int speed, bool forward)
{
  speed = constrain(speed,0,255);

  if(forward)
  {
    analogWrite(LPWM_2,0);
    analogWrite(RPWM_2,speed);
  }
  else
  {
    analogWrite(RPWM_2,0);
    analogWrite(LPWM_2,speed);
  }
}



void stopMotors()
{
  Serial.println("Motors Stopped");

  analogWrite(RPWM_1,0);
  analogWrite(LPWM_1,0);
  analogWrite(RPWM_2,0);
  analogWrite(LPWM_2,0);
}