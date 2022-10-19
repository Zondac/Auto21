# -*- coding: utf-8 -*-
"""
Created on Wed Oct 19 08:34:36 2022

@author: Windows User
"""

import serial
import time
arduino = serial.Serial(port='COM6', baudrate=115200, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:
    num = input("Choose how many players 1, 2, 3 or 4. \n ") # Taking input from user
    value = write_read(num)
    print(value) # printing the value