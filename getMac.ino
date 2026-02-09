#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);

  String mac = WiFi.macAddress();
  Serial.print("mac: ");
  Serial.println(mac);
}

void loop() {}
