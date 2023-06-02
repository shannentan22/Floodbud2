// This File is used to detect the water level within a singular sensor
// This will be used in case we would want to change "Trigger" Values in the actual system


#define POWER_PIN  7

int value = 0; // variable to store the sensor value
int level = 0; // variable to store the water level
int WaterSensor = A5; 

void setup() {
  Serial.begin(9600);
}

void loop() {
    value = analogRead(WaterSensor);
    if (value <= 100){
        Serial.println("Water Level: Empty at Value: ");
        Serial.print(value);
    }
    else if (value > 100 && value <= 300){
        Serial.println("Water Level: Low at Value: ");
        Serial.print(value);
    }
    else if (value > 300 && value <= 330){
        Serial.println("Water Level: Medium at Value: ");
        Serial.print(value);
    }
    else if (value > 330){
        Serial.println("Water Level: High at Value");
        Serial.print(value);
    }

    delay(1000);
}
