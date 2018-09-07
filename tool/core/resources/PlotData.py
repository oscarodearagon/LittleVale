import matplotlib.pyplot as plt

plt.ion()


class PlotData:

    MOMENT_00_MAX = 16

    # 1x1 Sensor
    # X_VALUE_MAX = 4 * 16
    # X_VALUE_MIN = 16
    # Y_VALUE_MAX = 4 * 16
    # Y_VALUE_MIN = 16

    # 2x2 Sensor
    X_VALUE_MAX = 512
    X_VALUE_MIN = 64
    Y_VALUE_MAX = 512
    Y_VALUE_MIN = 64

    POINT_TYPE = 'ro'

    def __init__(self):
        # Set up plot
        self.figure, self.ax = plt.subplots()
        self.lines, = self.ax.plot([], [], PlotData.POINT_TYPE)
        # Autoscale on unknown axis and known lims on the other
        self.ax.set_autoscaley_on(True)
        self.ax.set_xlim(PlotData.X_VALUE_MIN, PlotData.X_VALUE_MAX)
        self.ax.set_ylim(PlotData.Y_VALUE_MIN, PlotData.Y_VALUE_MAX)
        # Other stuff
        self.ax.grid()

    def plot_values(self, x_value, y_value):
        # Update data (with the new _and_ the old points)
        self.lines.set_xdata(x_value)
        self.lines.set_ydata(y_value)
        # Need both of these in order to rescale
        self.ax.relim()
        self.ax.autoscale_view()
        # We need to draw *and* flush
        self.figure.canvas.draw()
        self.figure.canvas.flush_events()
