#include <ESP32Servo.h>

// ================= SERVO PINS =================

#define HEAD_SERVO_PIN        13
#define LEFT_ARM_SERVO_PIN    14
#define RIGHT_ARM_SERVO_PIN   12

Servo headServo;
Servo leftArmServo;
Servo rightArmServo;

// ================= SETUP =================

void setup()
{
  Serial.begin(115200);

  // Attach servos
  headServo.attach(HEAD_SERVO_PIN, 500, 2400);
  leftArmServo.attach(LEFT_ARM_SERVO_PIN, 500, 2400);
  rightArmServo.attach(RIGHT_ARM_SERVO_PIN, 500, 2400);

  // Initial position
  headServo.write(90);
  leftArmServo.write(0);
  rightArmServo.write(0);

  delay(1000);

  Serial.println("Servo Test Started");
}

// ================= LOOP =================

void loop()
{
  // ==========================================
  // HEAD MOVEMENT
  // ==========================================

  Serial.println("Head Left");
  headServo.write(0);
  delay(1000);

  Serial.println("Head Center");
  headServo.write(180);
  delay(1000);

  Serial.println("Head Right");
  headServo.write(90);
  delay(1000);

  Serial.println("Head Center");
  headServo.write(0);
  delay(1000);


  // ==========================================
  // LEFT ARM
  // ==========================================

  Serial.println("Left Arm Up");
  leftArmServo.write(90);
  delay(1000);

  Serial.println("Left Arm Down");
  leftArmServo.write(0);
  delay(1000);


  // ==========================================
  // RIGHT ARM
  // ==========================================

  Serial.println("Right Arm Up");
  rightArmServo.write(90);
  delay(1000);

  Serial.println("Right Arm Down");
  rightArmServo.write(0);
  delay(1000);


  // ==========================================
  // WELCOME GESTURE
  // ==========================================

  Serial.println("WELCOME GESTURE");

  headServo.write(90);

  leftArmServo.write(90);
  rightArmServo.write(90);

  delay(1000);

  // Wave / greeting movement

  for (int i = 0; i < 3; i++)
  {
    Serial.println("Greeting...");

    leftArmServo.write(60);
    rightArmServo.write(120);

    delay(400);

    leftArmServo.write(90);
    rightArmServo.write(90);

    delay(400);
  }

  // Return arms down

  leftArmServo.write(0);
  rightArmServo.write(0);

  delay(2000);
}