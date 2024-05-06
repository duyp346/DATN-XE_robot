
void ReceivePI()
{
  if(Serial.available()) {
  str_fire = Serial.readStringUntil('\n');
  fireVal = (str_fire.toInt()); 
  }
}

void check()                          // Can be used to simulate Metal Detecting or to rotate Ping Sensor
{ 
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(5); 
  digitalWrite(trig, LOW); 
  // Đo độ rộng xung HIGH ở chân echo.
  thoigian = pulseIn(echo, HIGH);

  khoangcach = thoigian / 2 / 29.412;
  Serial.println(khoangcach);
} 

void daplua()
{
  while(step2 == 1){
    digitalWrite(pump,HIGH);
    bluetooth();
    if (blueToothVal == 5){
      digitalWrite(pump,LOW);
      step2 = 0;
      break;
    }
    ReceivePI();
  }
}
