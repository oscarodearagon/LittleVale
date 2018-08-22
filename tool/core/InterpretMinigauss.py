
import time

from core.resources.SerialCom import SerialCom
from core.resources.MinigaussProcess import MinigaussProcess
from core.resources.PlotData import PlotData

# Constants
WAIT_TIME_SECONDS = 5
TESTING_TIME_SECONDS = 1

# Initializations
serialConnection = SerialCom()
minigauss = MinigaussProcess()
chart = PlotData()

# Open serial connection
serialConnection.open()

# Calibration
calibration_status = False
while calibration_status is False:
    result, data = serialConnection.read_block()
    if result is True:
        calibration_status = minigauss.calibration(data)
    else:
        print("[Main] Block was not read correctly in Calibration stage")

print("[Main] Finish Calibration stage")

time_out = time.time() + WAIT_TIME_SECONDS
while time_out > time.time():
    # Read block
    result, data = serialConnection.read_block()

print("[Main] Start Processing")

time_out = time.time() + TESTING_TIME_SECONDS
while time_out > time.time():

    # Read block
    result, data = serialConnection.read_block()

    if result is True:
        # print(data)

        # Start data processing
        result, position = minigauss.process_data(data)

        # Plot position
        x_value, y_value = minigauss.get_coordinates()
        chart.plot_values(x_value, y_value)

        # if result is True:
        #     print(position)
        #
        #     # Plot position
        #
        # else:
        #     print("[Main] Data couldn't be processed correctly")
    else:
        print("[Main] Block was not read correctly")

# Close serial connection
serialConnection.close()
