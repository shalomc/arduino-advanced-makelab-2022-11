# importing the required modules
import math
import matplotlib.pyplot as graf
import sys
import pathlib

graf_title = 'All sine waves'
INTERACTIVE = False

def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


def traffic_green_value(sensorValue, max_value = 255):
    mapped_x = arduino_map(sensorValue, sensor_in_min, sensor_in_max, 0, 314)
    sin = math.sin(float(mapped_x) / 100.0 +  math.pi )+1
    valueComputed = int((sin * 1000.0)) * (sensorValue < 512)
    return arduino_map(valueComputed, 0,1000,0,max_value)
# ------------------------------------------------------
def traffic_yellow_value(sensorValue, max_value = 255):
    mapped_x = arduino_map(sensorValue, sensor_in_min, sensor_in_max, 0, 314)
    sin = math.sin(float(mapped_x) / 100.0 + 0 )
    valueComputed = int((sin * 1000.0)) * 1 # always
    return arduino_map(valueComputed, 0,1000,0,max_value)
# ------------------------------------------------------
def traffic_red_value(sensorValue, max_value = 255):
    mapped_x = arduino_map(sensorValue, sensor_in_min, sensor_in_max, 0, 314)
    sin = math.sin(float(mapped_x) / 100.0 +  math.pi )+1
    valueComputed = arduino_map( int(sin * 1000.0), 0, 1000, 0, max_value ) * (sensorValue >= 512)
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


