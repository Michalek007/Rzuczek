import serial

# s_write = serial.Serial('COM5', 921600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
s_read = serial.Serial('COM6', 921600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)


def get_data():
    data = s_read.read_all().split('\n')
    values = {'temp': data[0], 'press': data[0], 'absl': data[0]}
    return values
