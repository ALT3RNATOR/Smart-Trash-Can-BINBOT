#include <Servo.h>

Servo servo;     
int trigPin1 = 5;  // Trig pin for lid control sensor
int echoPin1 = 6;  // Echo pin for lid control sensor
int trigPin2 = 9;  // Trig pin for waste level sensor
int echoPin2 = 10;  // Echo pin for waste level sensor
int servoPin = 7;

long duration1, dist1;  // Variables for lid control sensor
long duration2, dist2;  // Variables for waste level sensor

// Dustbin dimensions
const float dustbinHeight = 25.0;  // Height of the dustbin in cm
const float dustbinDiameter = 22.0;  // Diameter of the dustbin in cm
const float dustbinRadius = dustbinDiameter / 2.0;  // Radius of the dustbin in cm

// Constants for weight calculation
const float densityOfTrash = 60.0;  // Density of trash in kg/m^3
const float pi = 3.14159265359;  // Value of pi

float depthOfTrash, trashVolume, weightOfTrash;  // Variables for calculating trash volume and weight

void setup() {
    Serial.begin(9600);
    servo.attach(servoPin);
    
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    servo.write(90);  // Close the lid on startup
    delay(1);
    servo.detach();
}

void measureDistance(int trigPin, int echoPin, long &duration, long &dist) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist = (duration / 2) / 29.1;  // Convert duration to distance in cm
}

void calculateWeight() {
    // Calculate the depth of the trash inside the dustbin
    depthOfTrash = dustbinHeight - dist2;

    // If the depth of trash is greater than zero, calculate volume and weight
    if (depthOfTrash > 0) {
        trashVolume = pi * pow(dustbinRadius / 100, 2) * (depthOfTrash / 100);  // Volume in m^3
        weightOfTrash = densityOfTrash * trashVolume;  // Weight in kg
    } else {
        weightOfTrash = 0;
    }
}

void loop() {
    // Measure distance from lid control sensor
    measureDistance(trigPin1, echoPin1, duration1, dist1);

    // If an object is within 50 cm, open the lid
    if (dist1 < 20) {
        servo.attach(servoPin);
        delay(1);
        servo.write(0);  // Open the lid
        delay(3000);  // Keep the lid open for 3 seconds
        servo.write(90);  // Close the lid
        delay(1000);
        servo.detach();
    }

    // Measure distance from waste level sensor
    measureDistance(trigPin2, echoPin2, duration2, dist2);

    // Calculate the weight of the trash
    calculateWeight();

    // Display waste level in the Serial Monitor
    if (dist2 > dustbinHeight - 10) {  // Almost empty
        Serial.println("Waste Level: LOW");
    } else if (dist2 > dustbinHeight - 25 && dist2 <= dustbinHeight - 10) {  // Medium level
        Serial.println("Waste Level: MEDIUM");
    } else if (dist2 <= dustbinHeight - 25) {  // Near full
        Serial.println("Waste Level: HIGH");
    }

    Serial.print("Weight of Trash: ");
    Serial.print(weightOfTrash);
    Serial.print(" kg, Waste Level Sensor Distance: ");
    Serial.print(dist2);
    Serial.println(" cm");

    delay(500);  // Delay to avoid rapid triggering
}
