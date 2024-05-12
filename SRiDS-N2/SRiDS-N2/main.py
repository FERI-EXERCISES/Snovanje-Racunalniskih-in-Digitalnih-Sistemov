import serial.tools.list_ports
import argparse
import time

# print(list(serial.tools.list_ports.comports()))
# print([comport.device for comport in serial.tools.list_ports.comports()])

def send_command(ser, command):
    ser.write((command + '\n').encode('ascii'))
    time.sleep(0.1)  # Delay for command processing

def control_led(ser, pattern):
    # Primer: pattern = "XOXO"
    commands = []
    if pattern[0] == 'O':
        commands.append('LED_12_ON')
    else:
        commands.append('LED_12_OFF')

    if pattern[1] == 'O':
        commands.append('LED_13_ON')
    else:
        commands.append('LED_13_OFF')

    if pattern[2] == 'O':
        commands.append('LED_14_ON')
    else:
        commands.append('LED_14_OFF')

    if pattern[3] == 'O':
        commands.append('LED_15_ON')
    else:
        commands.append('LED_15_OFF')

    # Optimize command list
    if commands == ['LED_12_ON', 'LED_13_ON', 'LED_14_ON', 'LED_15_ON']:
        commands = ['LED_ON']
    elif commands == ['LED_12_OFF', 'LED_13_OFF', 'LED_14_OFF', 'LED_15_OFF']:
        commands = ['LED_OFF']

    for cmd in commands:
        send_command(ser, cmd)

def monitor_state(ser):
    last_state = ""
    try:
        while True:
            send_command(ser, 'STANJE')
            current_state = ser.read(ser.inWaiting()).decode().replace('LED_', '').replace('_ON', 'O').replace('_OFF', 'X').replace(' ', '').replace('12', '').replace('13', '').replace('14', '').replace('15', '')
            if current_state != last_state:
                print(current_state)
                last_state = current_state
            time.sleep(0.1)  # 10 Hz frequency
    except KeyboardInterrupt:
        pass

if __name__ == '__main__':
    # COM3
    ser = serial.Serial('COM3')

    

    parser = argparse.ArgumentParser(description='STM32 Control Program')
    parser.add_argument('--led', help='Control LED state, e.g., XOXO')
    parser.add_argument('--animacija', choices=['on', 'off'], help='Control animation state')
    parser.add_argument('--stanje', action='store_true', help='Monitor LED states')
    args = parser.parse_args()

    if args.led:
        control_led(ser, args.led)
    elif args.animacija:
        if args.animacija.lower() == 'on':
            send_command(ser, 'ANIMACIJA_ON')
        elif args.animacija.lower() == 'off':
            send_command(ser, 'ANIMACIJA_OFF')
    elif args.stanje:
        monitor_state(ser)
    else:
        parser.print_help()

    ser.close()


