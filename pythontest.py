import sys
from matplotlib import pyplot as plt
from drawnow import drawnow
import random
from threading import Thread
import time

class worker(Thread):
    def __init__(self):
        self.temp = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        
    def run(self):
        self.plotme()
        while True:
            self.temp.append(random.randrange(19, 120))
            # drawnow(self.plotme)
            self.plotme()
            if self.temp.__len__() > 100:
                self.temp.pop(0)
            # time.sleep(0.025)
            plt.clf()
        plt.show()

    def plotme(self):
        plt.ion()
        plt.ylim(0, 150)
        plt.plot(self.temp, 'ro-', label='temp')
        plt.draw()
        plt.pause(1)

t = worker()
t.run()
