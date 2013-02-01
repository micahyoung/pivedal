#include "Arduino.h"

const int SENSOR_PIN = 2;
const int INTERRUPT_PIN = 0;

const byte PEDAL_DOWN = 1;
const byte PEDAL_UP = 2;
const byte INS_MODE = 3;
const byte NAV_MODE = 4;
volatile byte currentMode;

int pedal_status() {
  return (digitalRead(SENSOR_PIN) == HIGH) ? PEDAL_DOWN : PEDAL_UP;
}

const int QUEUE_SIZE = 2;
volatile byte queue[QUEUE_SIZE];
volatile int queueCount;
void queue_push(byte stat) {
  for (int i = 0; i < QUEUE_SIZE; i++) {
    if (queue[i]) { continue; }
    queue[i] = stat;
    queueCount++;
  }
}

const unsigned int DEBOUNCE_DELAY = 100;
unsigned long lastDebounceTime = 0;
void on_change() {
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    lastDebounceTime = millis();
    queue_push(pedal_status());
  }
}

byte *clear_queue() {
  static byte currentQueue[QUEUE_SIZE];
  memcpy(currentQueue, (byte *)queue, sizeof(*queue));

  for (int i = 0; i < QUEUE_SIZE; i++) {
    queue[i] = NULL;
  }
  queueCount = 0;

  return currentQueue;
}

void send_key(int keyCode) {
  uint8_t keyBuffer[8] = { 0 };

  keyBuffer[0] = 0;
  keyBuffer[2] = keyCode;
  Serial.write(keyBuffer, 8);
  delay(50); //allow host to read
}

const int INS_KEY_CODE = 73;
const int ESC_KEY_CODE = 41;
const int RELEASE_KEY_CODE = 0;
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

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(INTERRUPT_PIN, on_change, CHANGE);
  currentMode = (pedal_status() == PEDAL_DOWN) ? INS_MODE : NAV_MODE;
}

void loop() {
  if (queueCount == 0) { return; }

  byte *currentQueue = clear_queue();

  int pedalEvent;
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
