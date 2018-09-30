import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
from matplotlib import style
import datetime
import matplotlib

matplotlib.use('TKAgg')
ser = serial.Serial('/dev/ttyUSB0', baudrate=1200, timeout=2)
print(ser.name)

# sio = io.StringIO()
# sio.flush()
# plt.ion()
style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
ax1.cla()
ax1.set_xlabel('Time')
ax1.set_ylabel('Sensor Input (C)')
# plt.ylim(0, 120)
# plt.xlim(0, 50)
# plt.grid(True)
# plt.ylabel('Temperature')
# # plt.plot(temperature, 'ro-', label='Temp C')
# plt.legend(loc='upper left')
# plt2 = plt.twinx()
# plt.ylim(10,120)
# # plt2.plot(average ,'b^-' , label='Average Temperature')
# plt2.legend(loc='upper right')
plt.ion()  # Set interactive mode ON, so matplotlib will not be blocking the window
plt.show(False)  # Set to false so that the code doesn't stop here


background = fig.canvas.copy_from_bbox(ax1.bbox)
iterations = 0
xs = []
ys = []
ys.append(0)
line1, = ax1.plot(iterations, ys, '.-', alpha=0.8, color="gray", markerfacecolor="red")
fig.show()
fig.canvas.draw()

def animate(i):
    try:
        global iterations
        graph_data = ser.readline().decode('utf-8')
        currenttemp = float(graph_data)
        xs.append(iterations)
        ys.append(currenttemp)
        print(currenttemp)
        if len(ys) > 50:
            ys.pop(0)
            xs.pop(0)
        # ax1.clear()
        # ax1.plot(xs,ys)
        iterations =  iterations + 1
        line1.set_xdata(iterations)
        line1.set_ydata(ys)
        fig.canvas.restore_region(background)    # restore background
        ax1.draw_artist(line1)                   # redraw just the points
        fig.canvas.blit(ax1.bbox) 
    except KeyboardInterrupt:
        print("finished")


while True:
    animate(1)

#ani = animation.FuncAnimation(fig,animate,interval=100)
#plt.show()