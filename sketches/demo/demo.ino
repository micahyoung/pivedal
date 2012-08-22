uint8_t buf[8] = { 0 };

void setup(){
  Serial.begin(9600);
}

void loop()
{
  sendInsertModeKeys();
  delay(1000);

  sendNavModeKeys();
  delay(1000);
}

void sendInsertModeKeys() {
  sendShiftKey();
  delay(100);
  sendIKey();
  delay(100);
  releaseKey();
}

void sendNavModeKeys() {
  sendEscKey();
  delay(100);
  releaseKey();
}

void sendShiftKey()
{
  buf[0] = 0;
  buf[2] = 229;
  Serial.write(buf, 8);
}

void sendIKey()
{
  buf[0] = 0;
  buf[2] = 12;
  Serial.write(buf, 8);
}

void sendEscKey()
{
  buf[0] = 0;
  buf[2] = 41;
  Serial.write(buf, 8);
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}


