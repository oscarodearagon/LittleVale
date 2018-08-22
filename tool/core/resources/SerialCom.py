import serial


class SerialCom:
    # Configuration
    SERIAL_BAUDRATE = 9600
    SERIAL_PORT = 'COM5'

    HEADER = bytearray(b'\x00\xff\x00')
    DATA_LENGTH = 16
    MAXIMUM_LENGTH = 19

    def __init__(self):
        self.ser_conn = serial.Serial()
        self.ser_conn.baudrate = SerialCom.SERIAL_BAUDRATE
        self.ser_conn.port = SerialCom.SERIAL_PORT

    def open(self):
        self.ser_conn.open()

        if self.ser_conn.is_open:
            message = "[SerialCom] Successful connection"
        else:
            message = "[SerialCom] Wrong connection"

        print(message)

    def close(self):
        self.ser_conn.close()
        message = "[SerialCom] Close connection"
        print(message)

    def read_block(self):
        result = False
        data = []

        if self.__extract_header():
            data = self.ser_conn.read(SerialCom.DATA_LENGTH)
            result = True
            print(data)

        return result, data

    def __extract_header(self):
        result = False
        counter = 0

        while counter < SerialCom.MAXIMUM_LENGTH:
            data = self.__read_integer(1)
            if data == SerialCom.HEADER[0]:
                data = self.__read_integer(1)
                if data == SerialCom.HEADER[1]:
                    data = self.__read_integer(1)
                    if data == SerialCom.HEADER[2]:
                        result = True
                        break

            if result is False:
                counter += 1

        # if result is True:
        #     message = "[SerialCom] Header extracted"
        # else:
        #     message = "[SerialCom] Header was not found"
        # print(message)

        return result

    def __read_integer(self, number_of_bytes):
        value = self.ser_conn.read(number_of_bytes)
        int_value = int.from_bytes(value, byteorder='big')

        return int_value
