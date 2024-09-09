#include <Servo.h>

int flexPin1 = A1;
int flexPin2 = A2;
int flexPin3 = A3;
int flexPin4 = A4;
int flexPin5 = A5;
int buzzerPin = 2;

int servoPin = 53; 

int trigPin = 3;
int echoPin = 4;

Servo myServo;

unsigned long startTime = 0;
const unsigned long duration = 3000;  

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  int flexValue1 = analogRead(flexPin1);
  int flexValue2 = analogRead(flexPin2);
  int flexValue3 = analogRead(flexPin3);
  int flexValue4 = analogRead(flexPin4);
  int flexValue5 = analogRead(flexPin5);

  Serial.print("(");
  Serial.print(flexValue1);
  Serial.print(", ");
  Serial.print(flexValue2);
  Serial.print(", ");
  Serial.print(flexValue3);
  Serial.print(", ");
  Serial.print(flexValue4);
  Serial.print(", ");
  Serial.print(flexValue5);
  Serial.println(")");
  
  delay(500);

  int count = 0; 

  // Values Change karni h
  if (flexValue1 > 100) count++;
  if (flexValue2 > 100) count++;
  if (flexValue3 > 100) count++;
  if (flexValue4 > 100) count++;
  if (flexValue5 > 100) count++;

  // If the driver opens his hands

  if (count >= 3) {
    if (startTime == 0) {
      startTime = millis();
    } else if (millis() - startTime >= duration) {
      digitalWrite(buzzerPin, HIGH);  
    }
  } else {
    if (digitalRead(buzzerPin) == HIGH) {
      digitalWrite(buzzerPin, LOW);
      Serial.println("BUZZER_STOP");  
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

  // Servo


  if (distance <= 20) {
    myServo.write(90);  
  } else {
    myServo.write(0);   
  }
  

}
