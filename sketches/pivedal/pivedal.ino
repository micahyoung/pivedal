const int sensorPin = 2;
const int INS_MODE = 1;
const int NAV_MODE = 2;

int sensorValue;
int mode;
uint8_t keyBuffer[8] = { 0 };

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  switch (mode) {
    case INS_MODE:
      if (!isPedalDown()) {
        sendNavModeKeys();
        mode = NAV_MODE;
      }
      break;
    case NAV_MODE:
      if (isPedalDown()) {
        sendInsertModeKeys();
        mode = INS_MODE;
      }
      break;
    default:
      if (isPedalDown()) {
        mode = INS_MODE;
      } else {
        mode = NAV_MODE;
      }
  }

  delay(100);
}

boolean isPedalDown() {
  sensorValue = digitalRead(sensorPin);

  if (sensorValue == HIGH) {
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

void sendKey(char Key[]) {
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
