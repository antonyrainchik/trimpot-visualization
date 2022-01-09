int oldVal = 0;

void setup() {
  Serial.begin(9600); 
  
  
}
void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  if (sensorValue == oldVal || sensorValue == oldVal - 1 || sensorValue == oldVal + 1 || sensorValue <= oldVal - 50 || sensorValue >= oldVal + 50){}
  else{
    oldVal = sensorValue;
    Serial.println(sensorValue);
    delay(1);
  }
  
}
