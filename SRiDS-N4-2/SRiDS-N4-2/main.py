import serial.tools.list_ports
import struct
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import argparse

# Obdelava argumentov ukazne vrstice
parser = argparse.ArgumentParser()
parser.add_argument("--live", nargs='?', const=10, type=int, help="Podaj čas za prikaz grafa v realnem času", default=None)
args = parser.parse_args()

if args.live is None:
    parser.print_help()
    exit(1)

capture_duration = args.live

ser = serial.Serial([comport.device for comport in serial.tools.list_ports.comports()][0])

class SensorData:
    def __init__(self, x, y, z, time, ix):
        self.x = x
        self.y = y
        self.z = z
        self.time = time
        self.ix = ix

data_array = []

end_time = None

def Update(frame):
    global end_time
    start_time = None
    current_time = time.time()
    while ser.in_waiting:
        raw_data = ser.read(12)
        if len(raw_data) == 12:
            if start_time is None:
                start_time = current_time

            glava, counter, timer, x, y, z = struct.unpack('<6h', raw_data)
            print(f"header: {glava} count: {counter}  timer: {timer} koti:({x}, {y}, {z})")

            data_array.append(SensorData(x, y, z, current_time, counter))

            # Brisemo stare
            while data_array and current_time - data_array[0].time > capture_duration:
                data_array.pop(0)

            if end_time and current_time >= end_time:
                return

    X_data = [data.x for data in data_array]
    Y_data = [data.y for data in data_array]
    Z_data = [data.z for data in data_array]
    Time_data = [data.time for data in data_array]
    Counter_data = [data.ix for data in data_array]

    line1.set_data(Counter_data, X_data)
    line2.set_data(Counter_data, Y_data)
    line3.set_data(Counter_data, Z_data)
    ax1.relim()
    ax1.autoscale_view()

    return line1, line2, line3

# Ustvarjanje grafov
fig, ax1 = plt.subplots(1, 1, figsize=(12, 6))
line1, = ax1.plot([], [], label='X os')
line2, = ax1.plot([], [], label='Y os')
line3, = ax1.plot([], [], label='Z os')

ax1.set_ylabel('Vrednosti osi')
ax1.set_title('Kotne hitrosti')
ax1.legend()

plt.tight_layout()

ani = FuncAnimation(fig, Update, interval=30)
plt.show()
