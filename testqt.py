import numpy
from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import random
### START QtApp #####
# you MUST do this once (initialize things)
app = QtGui.QApplication([])
####################

win = pg.GraphicsWindow(title="Signal from serial port")  # creates a window
# creates empty space for the plot in the window
temp = win.addPlot(title="Temperature")
avgtemp = win.addPlot(title="Avg Temperature")
# create an empty "plot" (a curve to plot)
tempcurve = temp.plot()
avgtempcurve = avgtemp.plot()
windowWidth = 100                       # width of the window displaying the curve
# create array that will contain the relevant time series
Xm = linspace(0, 0, windowWidth)
#Am = linspace(0,0,windowWidth)
Am = numpy.array([0])
ptr = -windowWidth                      # set first x position

# Realtime data plot. Each time this function is called, the data display is updated


def update():
    global tempcurve, avgtempcurve, ptr, Xm, Am

    Am = numpy.append(Am, random.randint(1, 120))
    Am[:-1] = Am[1:] 

    ptr += 1                              # update x position for displaying the curve
    tempcurve.setData(Am)                     # set the curve with this data
    # set x position in the graph to 0
    tempcurve.setPos(ptr, 0)

    QtGui.QApplication.processEvents()    # you MUST process the plot now

### MAIN PROGRAM #####
# this is a brutal infinite loop calling your realtime data plot
# while True:
#     update()
try:
    while True:
        update()
except KeyboardInterrupt:
    print("finished")
finally:
    pg.QtGui.QApplication.exec_() 


### END QtApp ####
#pg.QtGui.QApplication.exec_()  # you MUST put this at the end
##################
