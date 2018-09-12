
import time

from core.resources.SerialCom import SerialCom

TESTING_TIME_SECONDS = 60

# Initializations
serialConnection = SerialCom()

# Open serial connection
serialConnection.open()

print("[Main] Start Tag")

time_out = time.time() + TESTING_TIME_SECONDS
while time_out > time.time():

    # Read block
    tag_id = serialConnection.read_tag_id()
    print(tag_id)

# Close serial connection
serialConnection.close()