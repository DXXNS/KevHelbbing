#include <WiFi.h>
#include <esp_now.h>

typedef struct msg {
  int value;
} msg;

msg data;

void onReceive(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  if(len == sizeof(msg)) {
    memcpy(&data, incomingData, sizeof(data));
    Serial.print("Empfangen am Receiver: ");
    Serial.println(data.value);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}

void loop() {}
