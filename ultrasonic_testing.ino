// trigger and echo pins initialization.
const int trigPin = A3;
const int echoPin = A2;

void setup() {
  // initialize serial communication to see output in terminal and setup pins.
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  long duration, inches, cm;

  // send ultrasonic signals.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // calculate distance based on duration.
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  centimeters = microsecondsToCentimeters(duration);

  // confirm that ultrasonic sensor working correctly.
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(centimeters);
  Serial.println("cm");
  delay(1000);
}

// formula to get inches.
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

// formula to get centimeters.
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}