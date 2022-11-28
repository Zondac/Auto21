import serial
import time
try:
    try:
        arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
    except:
        arduino = serial.Serial(port='/dev/ttyACM1', baudrate=115200, timeout=.1)
except:
    print("arduino not found")

def write(x):
    arduino.write(x.encode('utf-8'))
    time.sleep(0.05)
    arduino.flush()

def read():
    data = arduino.readline().decode('utf-8').rstrip()
    arduino.flush()
    while len(data) < 1:
         data = arduino.readline().decode('utf-8').rstrip()     
    arduino.flush()
    return data

def wr(x):
    write(x)
    return read()