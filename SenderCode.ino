#include <esp_now.h>
#include <WiFi.h>

uint8_t repeaterMac[] = {0x24, 0x6F, 0x28, 0x11, 0x22, 0x33}; // repeater MAC also mac addresse vom lö repeaterle

typedef struct msg {
  int value;
} msg;

msg data;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, repeaterMac, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);
}

void loop() {
  data.value = random(0, 100);
  esp_now_send(repeaterMac, (uint8_t*)&data, sizeof(data));
  delay(1000);
}
