import serial
import time

# s_write = serial.Serial('COM5', 921600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
s_read = serial.Serial('COM6', 921600, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)

while True:
    print(s_read.read_all())
    # print(s_read.read(100))
    time.sleep(0.01)
    # s_write.write(b"DUPA")
