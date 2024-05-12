import argparse

import serial.tools.list_ports
import struct
import matplotlib.pyplot as plt
import numpy as np
import time

parser = argparse.ArgumentParser()
parser.add_argument("--window", help="Časovno okno v sekundah.", type=int, default=60)
args = parser.parse_args()

# Nastavitve
capture_duration = args.window  # trajanje zajema v sekundah
sample_rate = 100

# Povezava s serijskim vmesnikom
ser = serial.Serial([comport.device for comport in serial.tools.list_ports.comports()][0])

# Priprava shranjevanja podatkov
data = {
    'counter': [],
    'timer': [],
    'x': [],
    'y': [],
    'z': []
}

start_time = time.time()
while time.time() - start_time < capture_duration:
    bytes_to_read = ser.inWaiting()
    if bytes_to_read >= 12:
        raw_data = ser.read(12)
        if len(raw_data) == 12:
            try:
                glava, counter, timer, x, y, z = struct.unpack('<6h', raw_data)

                print(f"header: {glava} count: {counter}  timer: {timer} koti:({x}, {y}, {z})")
                # Shranjevanje podatkov
                data['counter'].append(counter)
                data['timer'].append(timer)
                data['x'].append(x)
                data['y'].append(y)
                data['z'].append(z)
            except struct.error as e:
                print(f"Razpakiranje ni uspelo: {e}")

# Zapiranje serijske povezave
ser.close()

# Ustvarjanje časovne osi
time_axis = np.arange(0, capture_duration, 1/sample_rate)[:len(data['counter'])]

# Prikazovanje grafov
plt.figure(figsize=(10, 8))

# Graf za X os
plt.subplot(3, 1, 1)
plt.plot(time_axis, data['x'], label='X os')
plt.title('Kotne hitrosti')
plt.ylabel('Kotna hitrost (X)')
plt.legend()

# Graf za Y os
plt.subplot(3, 1, 2)
plt.plot(time_axis, data['y'], label='Y os')
plt.ylabel('Kotna hitrost (Y)')
plt.legend()

# Graf za Z os
plt.subplot(3, 1, 3)
plt.plot(time_axis, data['z'], label='Z os')
plt.ylabel('Kotna hitrost (Z)')
plt.legend()

plt.tight_layout()
plt.show()
