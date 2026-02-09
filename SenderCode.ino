#include <WiFi.h>
#include <esp_now.h>

uint8_t repeaterMac[] = {0xA0, 0xA3, 0xB3, 0x97, 0x81, 0x00}; // MAC vom Repeater

typedef struct msg {
  int value;
} msg;

msg data;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Fehler beim Initialisieren von ESP-NOW");
    return;
  }

  esp_now_peer_info_t peer;
  memset(&peer, 0, sizeof(peer));
  memcpy(peer.peer_addr, repeaterMac, 6);
  peer.channel = 0;
  peer.encrypt = false;
  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Fehler beim Hinzufügen des Peers");
  }
}

void loop() {
  data.value = random(0, 100);
  esp_err_t result = esp_now_send(repeaterMac, (uint8_t*)&data, sizeof(data));
  if(result == ESP_OK){
    Serial.print("Gesendet: ");
    Serial.println(data.value);
  } else {
    Serial.println("Senden fehlgeschlagen");
  }
  delay(1000);
}
