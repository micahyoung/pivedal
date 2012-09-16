const int sensorPin = 2;
const int INS_MODE = 1;
const int NAV_MODE = 2;
const int PEDAL_DOWN = 1;
const int PEDAL_UP = 2;

int sensorValue;
int current_mode;
uint8_t keyBuffer[8] = { 0 };

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  switch (current_mode) {
    case INS_MODE:
      if (pedalStatus() == PEDAL_UP) {
        sendNavModeKeys();
        current_mode = NAV_MODE;
      }
      break;
    case NAV_MODE:
      if (pedalStatus() == PEDAL_DOWN) {
        sendInsertModeKeys();
        current_mode = INS_MODE;
      }
      break;
    default:
      if (pedalStatus() == PEDAL_DOWN) {
        current_mode = INS_MODE;
      } else {
        current_mode = NAV_MODE;
      }
  }

  delay(100);
}

int pedalStatus() {
  switch (digitalRead(sensorPin)) {
    case HIGH:
      return PEDAL_DOWN;
      break;
    case LOW:
      return PEDAL_UP;
      break;
  }
}

void sendInsertModeKeys() {
  sendKey("Esc");
  sendKey("Release");
  sendKey("Ins");
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

  if (strcmp(Key, "Ins") == 0) {
    keyBuffer[2] = 73;
  } else if (strcmp(Key, "Esc") == 0) {
    keyBuffer[2] = 41;
  } else if (strcmp(Key, "Release") == 0) {
    keyBuffer[2] = 0;
  }

  Serial.write(keyBuffer, 8);
  delay(100); //allow host to read
}
