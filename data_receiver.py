import serial, csv, time

PORT = "/dev/ttyUSB0"  # Windows: "COM3"
ser = serial.Serial(PORT, 9600, timeout=1)
print("LoRa receiver dashboard started...")

with open("readings.csv", "a", newline="") as f:
    w = csv.writer(f)
    while True:
        line = ser.readline().decode("utf-8", errors="ignore").strip()
        if not line:
            continue
        status, _, dist = line.partition(",")
        w.writerow([time.strftime("%Y-%m-%d %H:%M:%S"), status, dist]); f.flush()
        if status == "DANGER_WATER_LEVEL":
            print(f"!!! DANGER: water {dist} cm from sensor")
        else:
            print(f"OK: {dist} cm")
