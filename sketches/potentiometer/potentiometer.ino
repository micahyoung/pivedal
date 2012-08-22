int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int mode = 0;

uint8_t keyBuffer[8] = { 0 };

void setup(){
  Serial.begin(9600);
}

void loop()
{
  switch (mode) {
    case 1:
      if (!isPedalDown()) {
        sendNavModeKeys();
        mode = 2;
      }
      break;
    case 2:
      if (isPedalDown()) {
        sendInsertModeKeys();
        mode = 1;
      }
      break;
    default:
      if (isPedalDown()) {
        mode = 1;
      } else {
        mode = 2;
      }
  }
  
  delay(500);
}

boolean isPedalDown() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue >= 512) {
    return true;
  } else {
    return false;
  }
}

void sendInsertModeKeys() {
  sendKey("Shift");
  sendKey("i");
  sendKey("Release");
}

void sendNavModeKeys() {
  sendKey("Esc");
  sendKey("Release");
  sendKey("Esc");
  sendKey("Release");
}

void sendKey(char Key[])
{
  keyBuffer[0] = 0;

  if (strcmp(Key, "i") == 0) {
    keyBuffer[2] = 12;
  } else if (strcmp(Key, "Shift") == 0) {
    keyBuffer[2] = 229;
  } else if (strcmp(Key, "Esc") == 0) {
    keyBuffer[2] = 41;
  } else if (strcmp(Key, "Release") == 0) {
    keyBuffer[2] = 0;
  }

  Serial.write(keyBuffer, 8);
  delay(100); //allow host to read
}

