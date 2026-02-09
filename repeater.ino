#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMac[] = {0xD4, 0x8A, 0xFC, 0xA3, 0x59, 0xB8}; // main receiver MAC


typedef struct msg {
  int value;
} msg;

msg data;

void onReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));

  Serial.print("relay: ");
  Serial.println(data.value);

  esp_now_send(receiverMac, (uint8_t*)&data, sizeof(data));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, receiverMac, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  esp_now_register_recv_cb(onReceive);
}

void loop() {}
