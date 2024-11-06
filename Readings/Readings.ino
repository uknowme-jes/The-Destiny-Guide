#include <Servo.h>

int flexPin1 = A1;
int flexPin2 = A2;
int flexPin3 = A3;
int flexPin4 = A4;
int flexPin5 = A5;
int buzzerPin = 50;
int buzzerPinCollision = 51;

int servoPin = 53; 

int trigPin = 3;
int echoPin = 4;
int trigPinCollision = 5;
int echoPinCollision = 6;

int emgPin = A0;
int emgValue = 0;

Servo myServo;

unsigned long startTime = 0;
const unsigned long duration = 3000;  
bool buzzerActive = false; 
unsigned long buzzerStartTime = 0; 
const unsigned long buzzerDuration = 1000; 

unsigned long previousTime = 0;
float previousDistance = 100.0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinCollision, OUTPUT);
  pinMode(echoPinCollision, INPUT);
  pinMode(buzzerPinCollision, OUTPUT);
}

void loop() {
  int flexValue1 = analogRead(flexPin1);
  int flexValue2 = analogRead(flexPin2);
  int flexValue3 = analogRead(flexPin3);
  int flexValue4 = analogRead(flexPin4);
  int flexValue5 = analogRead(flexPin5);

  // Serial.print("(");
  // Serial.print(flexValue1);
  // Serial.print(", ");
  // Serial.print(flexValue2);
  // Serial.print(", ");
  // Serial.print(flexValue3);
  // Serial.print(", ");
  // Serial.print(flexValue4);
  // Serial.print(", ");
  // Serial.print(flexValue5);
  // Serial.println(")");

  delay(500);

  int count = 0; 

  if (flexValue1 > 100) count++;
  if (flexValue2 > 100) count++;
  if (flexValue3 > 100) count++;
  if (flexValue4 > 100) count++;
  if (flexValue5 > 100) count++;

  // If the driver opens his hands
  if (count >= 3) {
    if (startTime == 0) {
      startTime = millis();
    } else if (millis() - startTime >= duration && !buzzerActive) {
      digitalWrite(buzzerPin, HIGH);  
      buzzerActive = true;
      buzzerStartTime = millis(); // Set buzzer start time
    }
  } else {
    if (buzzerActive) {
      digitalWrite(buzzerPin, LOW);
      Serial.println("BUZZER_STOP");  
      buzzerActive = false; // Reset buzzer state
    }
    startTime = 0;
  }

  // Ultrasonic Sensor
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  long durationCollision, distanceCollision;

  digitalWrite(trigPinCollision, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinCollision, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinCollision, LOW);

  durationCollision = pulseIn(echoPinCollision, HIGH);
  distanceCollision = (durationCollision * 0.034) / 2;

  if (distanceCollision < 100) {
    unsigned long currentTime = millis();
    float timeElapsed = (currentTime - previousTime) / 1000.0; 

    if (timeElapsed > 1.0) {
      
      float distanceTraveled = previousDistance - distanceCollision;
      float speed = distanceTraveled / timeElapsed; 

      // minibuzzer add karna h

      if (speed > 25 && !buzzerActive) {
        Serial.println("COLLISION_DETECTED");
        for (;;) {
          digitalWrite(buzzerPinCollision, HIGH);
          delay(500);
          digitalWrite(buzzerPinCollision, LOW);
          delay(200);
        }
      }

      previousTime = currentTime;
      previousDistance = distanceCollision;
    }
  } else {
    if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
      digitalWrite(buzzerPin, LOW); 
      buzzerActive = false; // Reset buzzer state
    }
  }

  // Servo Control
  if (distance <= 20) {
    Serial.print("Moving a little aside... Object detected to the right");
    myServo.write(90);  
  } else {
    myServo.write(0);   
  }

  // EMG Sensor ----------------------------------------------

  emgValue = analogRead(emgPin);
  
  if (emgValue <= 50) {
    Serial.println("Signs of fatigue detected. Verifying through camera.")
  }
  

}


