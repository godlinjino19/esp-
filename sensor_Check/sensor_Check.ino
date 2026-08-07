#include <ESP32Servo.h>

// ==================== IR Sensors ====================
#define IR1 34
#define IR2 35

// ==================== PIR Sensors ===================
#define PIR1 15
#define PIR2 2

// ==================== Ultrasonic Sensor 1 ===========
#define TRIG1 4
#define ECHO1 19

// ==================== Ultrasonic Sensor 2 ===========
#define TRIG2 21
#define ECHO2 22

// ==================== Left Motor Driver ============
#define LEFT_RPWM 25
#define LEFT_LPWM 26

// ==================== Right Motor Driver ===========
#define RIGHT_RPWM 12
#define RIGHT_LPWM 14

// ==================== Servo Motors =================
#define RIGHT_SERVO_PIN 33
#define LEFT_SERVO_PIN 32

Servo rightServo;
Servo leftServo;
