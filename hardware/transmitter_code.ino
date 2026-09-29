// Transmitter: ESP32 + Ra-02 (SX1278, 433 MHz) + HC-SR04
// Library: "LoRa" by Sandeep Mistry (Arduino Library Manager)
#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2
#define TRIG 26
#define ECHO 27   // through a voltage divider (5V -> 3.3V)

const float DANGER_CM = 30.0;  // sensor-to-water distance below this = danger

float readDistanceCm() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long t = pulseIn(ECHO, HIGH, 30000);
  if (t == 0) return -1;
  return t * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) { Serial.println("LoRa init failed"); while (1); }
  Serial.println("Transmitter ready");
}

void loop() {
  float d = readDistanceCm();
  String msg = (d > 0 && d < DANGER_CM) ? "DANGER_WATER_LEVEL" : "OK";
  msg += "," + String(d, 1);
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
  Serial.println("Sent: " + msg);
  delay(5000);
}
