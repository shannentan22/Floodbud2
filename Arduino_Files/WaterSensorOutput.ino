// This file reads the analog values of the Water Sensor and outputs it in the Serial Monitor
// Simply used to calibrate and monitor sensor values

#define POWER_PIN  7

int value = 0; // variable to store the sensor value
int WaterSensor = A5;

void setup() {
  Serial.begin(9600);
}

void loop() {
    value = analogRead(WaterSensor); // read the analog value from sensor
    Serial.print("Sensor value: ");
    Serial.println(value);

    delay(1000);
}