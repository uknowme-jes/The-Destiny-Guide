int flexsensor = A0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(flexsensor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  int Value;
  Value = analogRead(flexsensor);
  Serial.print("sensor");
  Serial.println(Value);

  delay(500);

}
