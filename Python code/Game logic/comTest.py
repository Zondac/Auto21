import serial
import time

arduino = serial.Serial(port='/dev/ttyACM1', baudrate=115200, timeout=.1)

def write(x):
    
    arduino.write(x.encode('utf-8'))
    time.sleep(0.05)

def read():
    
    data = arduino.readline().decode('utf-8').rstrip()
    while len(data) < 1:
         data = arduino.readline().decode('utf-8').rstrip()
    return data

def wr(x):
    write(x)
    return read()