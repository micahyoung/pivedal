uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t keyA[8] = { 0, 0, 4, 0, 0, 0, 0 };

void setup(){
  Serial.begin(9600);
  delay(2000);
}

void loop()
{
  uint8_t ledStatus;

  /* Send an 'a' every second */
  Serial.write(keyA, 8);
  ledStatus = Serial.read();
  delay(100); // Give the host time to read the key
  Serial.write(keyNone, 8);
  delay(1000);
}

