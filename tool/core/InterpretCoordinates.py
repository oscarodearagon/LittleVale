
import time

from core.resources.SerialCom import SerialCom
from core.resources.PlotData import PlotData

TESTING_TIME_SECONDS = 60

# Initializations
serialConnection = SerialCom()
chart = PlotData()

# Open serial connection
serialConnection.open()

print("[Main] Start Plotting")

time_out = time.time() + TESTING_TIME_SECONDS
while time_out > time.time():

    start_time = time.time()
    # Read block
    result, position = serialConnection.read_coordinates()

    if result is True:
        # print(position)
        chart.plot_values(position[0], position[1])
    else:
        print("[Main] Block was not read correctly")

    print((time.time()-start_time))
# Close serial connection
serialConnection.close()
