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
ax1.set_xlim([0, 60])
ax1.set_ylim([0, 120])
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

iterations = 0
xs = []
ys = []

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
        ax1.clear()
        ax1.plot(xs,ys)
        iterations =  iterations + 1

    except KeyboardInterrupt:
        print("finished")
        

ani = animation.FuncAnimation(fig,animate,interval=100)
plt.show()