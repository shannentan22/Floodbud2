// This File is used to detect the water level within a singular sensor
// This will be used in case we would want to change "Trigger" Values in the actual system

#define POWER_PIN  7

#define MODERATESENSOR A5
#define HIGHSENSOR A6
#define VERYHIGHSENSOR A7

#define THRESHOLD 100

int moderate_sensor_value = 0; // variable to store WaterSensor1's value
int high_sensor_value = 0; // variable to store WaterSensor1's value
int veryhigh_sensor_value = 0; // variable to store WaterSensor1's value

int level = 0; // variable to store the water level

void setup() {
  Serial.begin(9600);
}

void loop() {
    //moderate_sensor_value = analogRead(MODERATESENSOR);
    //high_sensor_value = analogRead(HIGHSENSOR);
    //veryhigh_sensor_value = analogRead(VERYHIGHSENSOR);
    
    if (moderate_sensor_value < THRESHOLD && level != 1){
        Serial.println("-----START OF READING-----");
        Serial.println("Water Level: Low");
        printValues();
        Serial.println("------END OF READING------");
        level = 1;

        moderate_sensor_value = 101;
    }
    else if (moderate_sensor_value >= THRESHOLD && high_sensor_value < THRESHOLD && veryhigh_sensor_value < THRESHOLD && level != 2) {
        Serial.println("-----START OF READING-----");
        Serial.println("Water Level: Moderate");
        printValues();
        Serial.println("------END OF READING------");
        level = 2;

        high_sensor_value = 101;
    }
    else if (moderate_sensor_value >= THRESHOLD && high_sensor_value >= THRESHOLD && veryhigh_sensor_value < THRESHOLD && level != 3) {
        Serial.println("-----START OF READING-----");
        Serial.println("Water Level: High");
        printValues();
        Serial.println("------END OF READING------");
        level = 3;

        veryhigh_sensor_value = 101;
    }
    else if (moderate_sensor_value >= THRESHOLD && high_sensor_value >= THRESHOLD && veryhigh_sensor_value >= THRESHOLD && level != 4){
        Serial.println("-----START OF READING-----");
        Serial.println("Water Level: Very High");
        printValues();
        Serial.println("------END OF READING------");
        level = 4;
    }
    
    delay(1000);
}

void printValues() {

    Serial.print("Moderate Sensor: ");
    Serial.println(moderate_sensor_value);
    Serial.print("High Sensor: ");
    Serial.println(high_sensor_value);
    Serial.print("Very High Sensor: ");
    Serial.println(veryhigh_sensor_value);
}
