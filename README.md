# LoRa Disaster Warning System

**Community Disaster Early Warning System using LoRa/IoT**

**Description:** A low-cost prototype that uses low-power radio (LoRa) to send early warnings of natural disasters to remote or rural areas, without internet or mobile network.

**Technologies and tools:** IoT, LoRa modules, Embedded C, Python

A low-cost, offline flood early-warning system built with LoRa and ESP32. It sends water-level alerts over long distances with no internet or mobile network.

## How it works
1. **Sensor node** measures the distance from an ultrasonic sensor to the water surface every 5 seconds.
2. It sends the reading over LoRa (433 MHz). If the water gets closer than the threshold, the message is `DANGER_WATER_LEVEL`.
3. **Receiver node** picks up the packet, sounds a buzzer on danger, and prints the data over serial.
4. A Python script logs every reading to `readings.csv` and prints alerts.

## Hardware
- 2x ESP32 dev boards
- 2x Ra-02 (SX1278) LoRa modules, with antennas
- 1x HC-SR04 ultrasonic sensor
- 1x buzzer, 1k and 2k resistors, jumper wires, breadboard

## Wiring (both boards, Ra-02 at 3.3V only)
| Ra-02 | ESP32 |
|---|---|
| 3.3V | 3V3 |
| GND | GND |
| SCK | GPIO 18 |
| MISO | GPIO 19 |
| MOSI | GPIO 23 |
| NSS | GPIO 5 |
| RST | GPIO 14 |
| DIO0 | GPIO 2 |

**Sensor node:** HC-SR04 VCC to VIN (5V), GND to GND, TRIG to GPIO 26, ECHO to GPIO 27 through a divider (ECHO, 1k, GPIO 27, 2k, GND).
**Receiver node:** buzzer + to GPIO 25, - to GND.

Attach the antenna before powering the Ra-02.

## Setup
1. Install ESP32 board support and the **LoRa** library (Sandeep Mistry) in Arduino IDE.
2. Upload `hardware/transmitter_code.ino` and `hardware/receiver_code.ino`.
3. `pip install pyserial`, then run `python dashboard/data_receiver.py` (set the serial port inside).

## Configuration
Change `DANGER_CM` in the transmitter code to match your sensor mounting height.

## Project structure
```
LoRa_Disaster_Warning_System/
├── hardware/
│   ├── transmitter_code.ino
│   └── receiver_code.ino
├── dashboard/
│   └── data_receiver.py
└── README.md
```

## Future work
- Add a real water-level probe for outdoor use
- Solar power and a weatherproof enclosure
- Multiple sensor nodes with IDs
- Range testing results
