// pin initialization.
#define PIN_TRACKING_LEFT A1
#define PIN_TRACKING_RIGHT A0

void setup() {
  // initialize serial communication to see output in terminal and setup pins.
  Serial.begin(9600);
  pinMode(PIN_TRACKING_LEFT, INPUT);
  pinMode(PIN_TRACKING_RIGHT, INPUT);
  getTrackingSensorVal();
}

void loop() {
  // initialize sensors and values.
  u8 trackingSensorVal = 0;
  trackingSensorVal = getTrackingSensorVal();

  // confirm if ir sensor is operating correctly.
  Serial.print("The value is: ");
  Serial.println(trackingSensorval);
  delay(1000);
}

// returns 00 stop, 01 right, 10 left, or 11 straight based on the current condition of the sensors.
u8 getTrackingSensorVal() {
  u8 trackingSensorVal = 0;
  trackingSensorVal = (digitalRead(PIN_TRACKING_LEFT) == 1 ? 1 : 0) << 1 | (digitalRead(PIN_TRACKING_RIGHT) == 1 ? 1 : 0) << 0;
  return trackingSensorVal;
}