# importing the required modules
import math
import matplotlib.pyplot as graf
import sys
import pathlib

graf_title = 'All linear equations'
INTERACTIVE = False

def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


def traffic_green_value(sensorValue, max_value = 255):
    # points are represented as (x,y)
    p1=(0,max_value)
    p2=(512,0)
    x = sensorValue
    m = (p1[1]-p2[1])/(p1[0]-p2[0])
    b = max_value
    valueComputed = int(m*x+b) * (sensorValue < 512)
    return valueComputed
# ------------------------------------------------------
def traffic_yellow_value(sensorValue, max_value = 255):
    # points are represented as (x,y)
    p1=(0,0)
    p2=(512,255)
    p3 = (1023,0)
    x = sensorValue
    if (sensorValue<512):
        m = (p1[1] - p2[1]) / (p1[0] - p2[0])
        b = 0
    else: # (sensorValue>=512)
        m = (p2[1] - p3[1]) / (p2[0] - p3[0])
        b = p2[1] - m*p2[0]
    valueComputed = int(m*x +b)
    return valueComputed
# ------------------------------------------------------
def traffic_red_value(sensorValue, max_value = 255):
    # points are represented as (x,y)
    p1=(512,0)
    p2=(1023,255)
    x = sensorValue
    if (sensorValue<512):
        m = 0
        b = 0
    else: # (sensorValue>=512)
        m = (p1[1] - p2[1]) / (p1[0] - p2[0])
        b = p2[1] - m*p2[0]
    valueComputed = int(m*x +b)
    return valueComputed

# ------------------------------------------------------

sensor_in_min = 0
sensor_in_max = 1023
x_range = range(0, sensor_in_max + 1)
linewidth = 3
print(sys.argv[0])
mypath = pathlib.PurePath(sys.argv[0])
filename= f'../images/{mypath.stem}.png'

# G points
y_green_values = [traffic_green_value(x) for x in x_range]
graf.plot(x_range, y_green_values, label ="G", color="green", linewidth = linewidth)

# Y points
y_yellow_values = [traffic_yellow_value(x) for x in x_range]
graf.plot(x_range, y_yellow_values, label ="Y", color="orange", linewidth=linewidth)

# R points
y_red_values = [traffic_red_value(x) for x in x_range]
graf.plot(x_range, y_red_values, label ="R", color="red", linewidth=linewidth)

# naming the x axis
graf.xlabel('Sensor Values')
# naming the y axis
graf.ylabel('Analog Output')

graf.title(graf_title)
graf.legend()

# function to show the plot
if INTERACTIVE:
    graf.show()
else:
    graf.savefig(filename)
graf.close()


