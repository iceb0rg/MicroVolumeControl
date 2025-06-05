import pulsectl
import serial
import threading
import time

volume_percent = 0

def set_volume(percent):
    volume_level = percent / 100.0  
    with pulsectl.Pulse('set-volume') as pulse:
        sink = pulse.sink_list()[0]
        pulse.volume_set(sink, pulsectl.PulseVolumeInfo([volume_level] * len(sink.volume.values)))

def get_current_volume():
    with pulsectl.Pulse('get-volume') as pulse:
        sink = pulse.sink_list()[0]
        return round(100 * sink.volume.value_flat)


def volume_updater():
    global volume_percent
    while True:
        volume_percent = get_current_volume()
        


threading.Thread(target=volume_updater, daemon=True).start()


ser = serial.Serial('/dev/ttyACM0', 115200, timeout=0)

while True:
    line = ser.readline().decode('utf-8').strip()
    if line:
        try:
            sensor_value = int(line)
            sensor_value = max(0, min(100, sensor_value))
            print("Sensor data:", sensor_value, "   Current volume:", volume_percent, "%")

            if sensor_value != volume_percent:
                set_volume(sensor_value)

        except ValueError:
            print("Neplatná data:", line)
