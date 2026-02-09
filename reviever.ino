#include <esp_now.h>
#include <WiFi.h>

typedef struct msg {
  int value;
} msg;

msg data;

void onReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  Serial.print("empfangen: ");
  Serial.println(data.value);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb(onReceive);
}

void loop() {}
