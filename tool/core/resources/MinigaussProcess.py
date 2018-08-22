import math

class MinigaussProcess:

    # Stable average
    STABLE_AVERAGE = 190

    TOLERANCE = 8
    DATA_LENGTH = 16

    CALIBRATION_ENTRIES = 10

    BINARY_THRESHOLD = 25

    COLUMNS = 4
    ROWS = 4

    MOMENT_00_MAX = 16

    def __init__(self):
        self.data_list = [0] * MinigaussProcess.DATA_LENGTH
        self.binary_list = [0] * MinigaussProcess.DATA_LENGTH

        self.calibration_list = [0] * MinigaussProcess.DATA_LENGTH
        self.calibration_counter = 0

        self.moment_00 = 0
        self.moment_10 = 0
        self.moment_01 = 0

        self.x_c = 0
        self.y_c = 0

    def process_data(self, data):
        result = False

        self.__adapt_data(data)
        self.__print_list()

        # self.__average_calculation()

        # This function must be implemented in the embedded side
        self.__process_data()

        return result

    def calibration(self, data):
        status = False
        self.calibration_counter += 1
        for index, item in enumerate(data):
            self.calibration_list[index] += item

        print(self.calibration_list)
        if self.calibration_counter == MinigaussProcess.CALIBRATION_ENTRIES:
            for index in range(MinigaussProcess.DATA_LENGTH):
                self.calibration_list[index] /= MinigaussProcess.CALIBRATION_ENTRIES
                self.calibration_list[index] = round(self.calibration_list[index], 0)
            print(self.calibration_list)
            status = True

        return status

    def get_coordinates(self):
        x = math.trunc(self.x_c)
        y = math.trunc(self.y_c)
        print("Coordinates: ({},{})".format(x, y))
        return x, y

    def __process_data(self):
        self.__remove_average()
        #self.__remove_calibration()
        self.__print_list()

        self.__binary_list()
        # self.__multiply_list(2)
        # self.__print_list()

        self.__calculate_moments()

        self.__calculate_centroid()

    def __adapt_data(self, data):
        for index, item in enumerate(data):
            self.data_list[index] = item

    def __remove_average(self):
        for index, item in enumerate(self.data_list):
            self.data_list[index] = item - MinigaussProcess.STABLE_AVERAGE

    def __remove_calibration(self):
        for index, item in enumerate(self.data_list):
            self.data_list[index] = item - self.calibration_list[index]

    def __multiply_list(self, factor):
        for index, item in enumerate(self.data_list):
            self.data_list[index] = item * factor

    def __average_calculation(self):
        accumulator = 0
        for item in self.data_list:
            accumulator += item
        average = accumulator / MinigaussProcess.DATA_LENGTH
        print(average)

    def __binary_list(self):

        for index, item in enumerate(self.data_list):
            if MinigaussProcess.BINARY_THRESHOLD > item:
                self.binary_list[index] = 0
            else:
                self.binary_list[index] = 1

        # # Without binary
        # self.binary_list = self.data_list

        print(self.binary_list)

    def __print_list(self):
        print(self.data_list)

    def __calculate_moments(self):
        self.__moment_00()
        self.__moment_01()
        self.__moment_10()

    def __calculate_centroid(self):

        if self.moment_00 is not 0:
            # self.x_c = self.moment_10 / self.moment_00
            # self.y_c = self.moment_01 / self.moment_00

            self.x_c = (self.moment_10 * MinigaussProcess.MOMENT_00_MAX) / self.moment_00
            self.y_c = (self.moment_01 * MinigaussProcess.MOMENT_00_MAX) / self.moment_00
        else:
            self.x_c = 0
            self.y_c = 0
            print("No Magnetic field detected")

        print("Coordinates: ({},{})".format(self.x_c, self.y_c))

    def __moment_00(self):
        value = 0

        for item in self.binary_list:
            if item is not 0:
                value += item

        self.moment_00 = value
        print("Moment 00: {}".format(self.moment_00))

    def __moment_01(self):
        value = 0
        factor_index = 0
        rows_sum = [0, 0, 0, 0]
        factors = [4, 3, 2, 1]
        reference = 0

        for index, item in enumerate(self.binary_list):

            if item is not 0:
                rows_sum[factor_index] += item

            reference += 1
            if reference >= MinigaussProcess.ROWS:
                reference = 0
                factor_index += 1

        # print("Moment 01: rows_sum={}".format(rows_sum))

        for index in range(MinigaussProcess.ROWS):
            value += rows_sum[index] * factors[index]

        self.moment_01 = value
        print("Moment 01: {}".format(self.moment_01))

    def __moment_10(self):
        # value = 0
        # factor_list = [1, 2, 3, 4]
        # factor_index = 0

        value = 0
        factor_index = 0
        columns_sum = [0, 0, 0, 0]
        factors = [1, 2, 3, 4]

        for index, item in enumerate(self.binary_list):

            if item is not 0:
                columns_sum[factor_index] += item

            factor_index += 1
            if factor_index >= MinigaussProcess.COLUMNS:
                factor_index = 0

        # print("Moment 01: rows_sum={}".format(columns_sum))

        for index in range(MinigaussProcess.COLUMNS):
            value += columns_sum[index] * factors[index]

        self.moment_10 = value
        print("Moment 10: {}".format(self.moment_10))
