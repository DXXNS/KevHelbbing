

# ESP-NOW Projekt

Dieses Projekt zeigt ein einfaches ESP-NOW Netzwerk mit drei ESP32-Geräten: **Sender → Repeater → Receiver**.  
ESP-NOW ist ein schnelles, verbindungsloses Protokoll von Espressif, ähnlich wie leichtes WLAN ohne Router.

---

## 🔴 Sender

**Funktion:**  
Sendet jede Sekunde zufällige Werte an den Repeater über ESP-NOW.

**Bibliotheken:**

- `WiFi.h` – WiFi-Station-Modus & MAC-Adresse  
- `esp_now.h` – ESP-NOW Funktionen (initialisieren, senden, empfangen, Peers verwalten)

**MAC-Adresse des Empfängers:**  
Eindeutige MAC-Adresse des Repeaters.

**Datenstruktur:**

```cpp
typedef struct msg {
  int value;
} msg;
```

**Setup:**

* Serielle Schnittstelle starten
* WiFi-Station-Modus aktivieren (`WIFI_STA`)
* Sender MAC ausgeben
* ESP-NOW initialisieren
* Peer (Repeater) hinzufügen

**Loop:**

* Zufallswert erzeugen (`0-99`)
* Daten senden
* Wert im Serial Monitor ausgeben
* 1 Sekunde warten

**Zusammenfassung:**

* ESP32 initialisiert ESP-NOW
* Sendet kontinuierlich Werte an Repeater
* Anwendungsbeispiel: Sensorwerte drahtlos an einen zentralen ESP32 senden

---

## ⚫ Repeater

**Funktion:**
Empfängt Daten vom Sender, zeigt sie im Serial Monitor und leitet sie an den finalen Receiver weiter.

**Bibliotheken:**

* `WiFi.h`
* `esp_now.h`

**MAC-Adresse des Empfängers:**
MAC-Adresse des finalen Receivers.

**Datenstruktur:**

```cpp
typedef struct msg {
  int value;
} msg;
```

**Callback bei Empfang:**

* Prüft Datenlänge
* Kopiert empfangene Daten
* Zeigt Wert im Serial Monitor
* Leitet Daten an Receiver weiter (`esp_now_send`)

**Setup:**

* Serielle Schnittstelle starten
* WiFi-Station-Modus aktivieren
* Repeater MAC anzeigen
* ESP-NOW initialisieren
* Peer (Receiver) hinzufügen
* Callback für Empfang registrieren

**Loop:**
Leer (ereignisgesteuert)

**Zusammenfassung:**

* Repeater empfängt Sender-Daten
* Leitet Daten an Receiver weiter
* Anwendungsbeispiel: Sensornetzwerk mit Relay

---

## 🔵 Receiver

**Funktion:**
Empfängt Daten über ESP-NOW und zeigt sie im Serial Monitor an. Keine Weiterleitung.

**Bibliotheken:**

* `WiFi.h`
* `esp_now.h`

**Datenstruktur:**

```cpp
typedef struct msg {
  int value;
} msg;
```

**Callback bei Empfang:**

* Prüft Datenlänge
* Kopiert Daten
* Zeigt empfangene Werte im Serial Monitor an

**Setup:**

* Serielle Schnittstelle starten
* WiFi-Station-Modus aktivieren
* MAC-Adresse ausgeben
* ESP-NOW initialisieren
* Callback registrieren

**Loop:**
Leer (ereignisgesteuert)

**Zusammenfassung:**

* Finaler Empfänger im ESP-NOW Netzwerk
* Zeigt Daten vom Sender oder Repeater an
* Anwendungsbeispiel: Sensornetzwerk, Endgerät

---

## 🔄 Datenfluss

```
Sender (🔴) → Repeater (⚫) → Receiver (🔵)
```

* Sender generiert Werte
* Repeater empfängt und leitet weiter
* Receiver zeigt Werte an

---

## 📌 Hinweise

* Alle Geräte müssen **im selben WiFi-Kanal** sein
* ESP-NOW funktioniert **ohne Router**
* MAC-Adressen müssen korrekt eingetragen werden
* Debug-Ausgaben im Serial Monitor anzeigen

---


