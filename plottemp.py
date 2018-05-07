import serial
import string
import io
import matplotlib.pyplot as plt
from drawnow import *
import datetime

def plotdata():
    plt.ylim(0, 120)
    plt.xlim(0, 50)
    plt.grid(True)
    plt.ylabel('Temperature')
    plt.plot(temperature, 'ro-', label='Temp C')
    plt.legend(loc='upper left')
    plt2 = plt.twinx()
    plt.ylim(10,120)
    plt2.plot(average ,'b^-' , label='Average Temperature')
    plt2.legend(loc='upper right')

def closingports():
    sio.close()
    ser.close()


ser = serial.Serial('/dev/ttyUSB0', baudrate=1200, timeout=2)
print(ser.name)

sio = io.StringIO()
sio.flush()
plt.ion()

temperature = []
average = []

def findlength():
    if len(temperature) == 0:
        return float(1)
    else:
        return float(len(temperature))


try:
    file = open("log.txt","w+")
    while True:
        data = ser.readline().decode('utf-8')
        nodigit = data.translate(string.digits)
        currenttemp = float(nodigit)
        print(f" current:{currenttemp} average:{sum(temperature)/ findlength()}")
        file.write(f"time={datetime.datetime.now()} current:{currenttemp} average:{sum(temperature)/ findlength()}\n")
        temperature.append(currenttemp)
        average.append(sum(temperature)/ findlength())
        drawnow(plotdata)
        if temperature.__len__() > 50:
            temperature.pop(0)
            average.pop(0)
except KeyboardInterrupt:
    print("finished")
finally:
    closingports()
    file.close()
