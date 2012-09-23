const int sensorPin = 2;
const int interruptPin = 0;

const byte PEDAL_DOWN = 1;
const byte PEDAL_UP = 2;
const byte INS_MODE = 1;
const byte NAV_MODE = 2;
volatile byte currentMode;

const int QUEUE_SIZE = 2;
volatile byte queue[QUEUE_SIZE];
volatile int queueCount;

const int INS_KEY_CODE = 73;
const int ESC_KEY_CODE = 41;
const int RELEASE_KEY_CODE = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  attachInterrupt(interruptPin,  on_change, CHANGE);
  currentMode = (pedal_status() == PEDAL_DOWN) ? INS_MODE : NAV_MODE;
}

long lastDebounceTime = 0;
const int DEBOUNCE_DELAY = 100;
void on_change() {
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    lastDebounceTime = millis();
    queue_push(pedal_status());
  }
}

void queue_push(byte stat) {
  for (int i = 0; i < QUEUE_SIZE; i++) {
    if (queue[i]) { continue; }
    queue[i] = stat;
    queueCount++;
  }
}

int pedal_status() {
  switch (digitalRead(sensorPin)) {
    case HIGH:
      return PEDAL_DOWN;
      break;
    case LOW:
      return PEDAL_UP;
      break;
  }
}

void loop() {
  if (queueCount == 0) { return; }
  int pedalEvent;
  
  byte currentQueue[QUEUE_SIZE];
  memcpy(currentQueue, (byte *)queue, sizeof(*queue) );
  for (int i = 0; i < QUEUE_SIZE; i++) {
    queue[i] = NULL;
  }
  queueCount = 0;

  for (int i = 0; i < QUEUE_SIZE; i++) {
    if (!currentQueue[i]) { continue; }
    pedalEvent = currentQueue[i];

    switch (pedalEvent) {
      case PEDAL_UP:
        if (currentMode == INS_MODE) {
          send_nav_mode_keys();
          currentMode = NAV_MODE;
        }
        break;
      case PEDAL_DOWN:
        if (currentMode == NAV_MODE) {
          send_insert_mode_keys();
          currentMode = INS_MODE;
        }
        break;
    }
  }
}

void send_insert_mode_keys() {
  send_key(ESC_KEY_CODE);
  send_key(RELEASE_KEY_CODE);
  send_key(INS_KEY_CODE);
  send_key(RELEASE_KEY_CODE);
}

void send_nav_mode_keys() {
  send_key(ESC_KEY_CODE);
  send_key(RELEASE_KEY_CODE);
  send_key(ESC_KEY_CODE);
  send_key(RELEASE_KEY_CODE);
}

void send_key(int keyCode) {
  uint8_t keyBuffer[8] = { 0 };

  keyBuffer[0] = 0;
  keyBuffer[2] = keyCode;
  Serial.write(keyBuffer, 8);
  delay(100); //allow host to read
}
