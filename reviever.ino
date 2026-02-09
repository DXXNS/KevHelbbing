#include <WiFi.h>
#include <esp_now.h>

typedef struct msg {
  int value;
} msg;

msg data;

void onReceive(uint8_t *mac_addr, uint8_t *incomingData, uint8_t len) {
  if(len == sizeof(msg)) {
    memcpy(&data, incomingData, sizeof(data));
    Serial.print("Empfangen: ");
    Serial.println(data.value);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Fehler beim Initialisieren von ESP-NOW");
    return;
  }

  // registriere Callback
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO); // 1.0.6 benötigt Role
  esp_now_register_recv_cb(onReceive);
}

void loop() {}
