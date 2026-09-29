// Receiver: ESP32 + Ra-02 + buzzer (GPIO 25)
#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2
#define BUZZER 25

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) { Serial.println("LoRa init failed"); while (1); }
  Serial.println("Receiver ready");
}

void loop() {
  if (LoRa.parsePacket()) {
    String packet = "";
    while (LoRa.available()) packet += (char)LoRa.read();
    Serial.println(packet);  // Python script reads this line
    digitalWrite(BUZZER, packet.startsWith("DANGER_WATER_LEVEL") ? HIGH : LOW);
  }
}
