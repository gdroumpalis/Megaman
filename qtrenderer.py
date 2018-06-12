from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial

# Create object serial port
portName = "/dev/ttyUSB0"                     
baudrate = 1200
ser = serial.Serial(portName,baudrate)

### START QtApp #####
app = QtGui.QApplication([])


win = pg.GraphicsWindow(title="Signal from serial port") # creates a window
p = win.addPlot(title="Realtime Temperature plot")  # creates empty space for the plot in the window
currenttemp = p.plot()                        # create an empty "plot" (a curve to plot)
averagetemp = p.plot()

windowWidth = 500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series  
Avm = linspace(0,0,windowWidth)   
ptr = -windowWidth                      # set first x position

# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global currenttemp, ptr, Xm    
    #Xm[:-1] = Xm[1:]                      # shift data in the temporal mean 1 sample left
    if len(Xm) > 40:
        del Xm[0]
    value = ser.readline().decode('utf-8')                # read line (single value) from the serial port
    Xm[-1] = float(value)                 # vector containing the instantaneous values      
    Avm = (sum(Xm)/len(Xm))
    ptr += 1                              # update x position for displaying the curve
    currenttemp.setData(Xm)                     # set the curve with this data
    currenttemp.setPos(ptr,0)                   # set x position in the graph to 0
    averagetemp.setData(Avm)
    averagetemp.setPos(currenttemp.getPos())
    QtGui.QApplication.processEvents()    # you MUST process the plot now

### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True: update()

### END QtApp ####
pg.QtGui.QApplication.exec_() # you MUST put this at the end
##################