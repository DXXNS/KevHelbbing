#include <esp_now.h>
#include <WiFi.h>

uint8_t repeaterMac[] = {0xA0, 0xA3, 0xB3, 0x97, 0x81, 0x00}; // MAC vom Repeater

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
