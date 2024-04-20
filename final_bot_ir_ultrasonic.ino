#include <AFMotor.h>

// define all the motors.
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define PIN_TRACKING_LEFT A1
#define PIN_TRACKING_RIGHT A0
#define PIN_TRIG A3
#define PIN_ECHO A2

void setup() {
  // initialize serial communication to see output in terminal and setup pins.
  Serial.begin(9600);

  // increase PWM frequency for the motors.
  //TCCR0B = TCCR0B & 0b11111000 | 0b00000010;
  //TCCR2B = TCCR2B & 0b11111000 | 0b00000010;

  // setup pins and sensor tracking value.
  pinsSetup();
  getTrackingSensorVal();
  getUltrasonicSensorVal();
}

void loop() {
  // initialize sensors and values.
  u8 trackingSensorVal = 0;
  u8 ultrasonicSensorVal = 0;
  trackingSensorVal = getTrackingSensorVal();
  ultrasonicSensorVal = getUltrasonicSensorVal();

  // no object less than 6 inches in front of robot.
  if (ultrasonicSensorVal == 3) {
    switch (trackingSensorVal) {
      case 3: // stop.
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        break;
      case 0: // move forward.
        motor1.setSpeed(200);
        motor2.setSpeed(200);
        motor3.setSpeed(200); 
        motor4.setSpeed(200); 
        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);
        break;
      case 1: // turn right.
        motor1.setSpeed(200);
        motor2.setSpeed(200);
        motor3.setSpeed(200);
        motor4.setSpeed(200);
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        break;
      case 2: // turn left.
        motor1.setSpeed(200);
        motor2.setSpeed(200);
        motor3.setSpeed(200);
        motor4.setSpeed(200);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        break;
      default:
        break;
    }
  }

  // object less than 6 inches in front of robot.
  if (ultrasonicSensorVal == 0) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}

// returns 00 stop, 01 right, 10 left, or 11 straight based on the current condition of the sensors.
u8 getTrackingSensorVal() {
  u8 trackingSensorVal = 0;
  trackingSensorVal = (digitalRead(PIN_TRACKING_LEFT) == 1 ? 1 : 0) << 1 | (digitalRead(PIN_TRACKING_RIGHT) == 1 ? 1 : 0) << 0;
  return trackingSensorVal;
}

// returns 00 stop or 11 straight based on current condition of ultrasonic sensor.
u8 getUltrasonicSensorVal() {
  u8 ultrasonicSensorVal = 0;
  long duration, inches;

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);

  // convert the time into respective distance.
  inches = microsecondsToInches(duration);

  // if there is object less than 6 inches in front, then stop.
  if (inches <= 6) {
    ultrasonicSensorVal = 0b00;
  } else {
    ultrasonicSensorVal = 0b11;
  }

  return ultrasonicSensorVal;
}

// setup the left and right pin tracking.setup the trig and echo pin.
void pinsSetup() {
  pinMode(PIN_TRACKING_LEFT, INPUT);
  pinMode(PIN_TRACKING_RIGHT, INPUT);
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
}

// conversion to inches.
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

// conversion to centimeters.
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}