#include <WiFi.h>
#include <esp_now.h>

uint8_t repeaterMac[] = {0xA0, 0xA3, 0xB3, 0x97, 0x81, 0x00};

typedef struct msg {
  int value;
} msg;

msg data;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peer;
  memset(&peer, 0, sizeof(peer));
  memcpy(peer.peer_addr, repeaterMac, 6);
  peer.channel = 1; // alle auf Kanal 1
  peer.encrypt = false;
  esp_now_add_peer(&peer);
}

void loop() {
  data.value = random(0, 100);
  esp_now_send(repeaterMac, (uint8_t*)&data, sizeof(data));
  Serial.println(data.value);
  delay(1000);
}
