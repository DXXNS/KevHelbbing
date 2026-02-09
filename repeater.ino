#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMac[] = {0xD4, 0x8A, 0xFC, 0xA3, 0x59, 0xB8}; // main receiver MAC

typedef struct msg {
  int value;
} msg;

msg data;

void onReceive(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  if(len == sizeof(msg)) {
    memcpy(&data, incomingData, sizeof(data));
    Serial.print("Relay: ");
    Serial.println(data.value);

    esp_now_send(receiverMac, (uint8_t*)&data, sizeof(data));
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Fehler beim Initialisieren von ESP-NOW");
    return;
  }

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, receiverMac, 6);
  peer.channel = 0;
  peer.encrypt = false;
  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Fehler beim Hinzufügen des Peers");
  }

  esp_now_register_recv_cb(onReceive);
}

void loop() {}
