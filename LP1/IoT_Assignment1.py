import RPi.GPIO as GPIO
import time

sensor = 16
LED = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(sensor, GPIO.IN)
GPIO.setup(LED, GPIO.OUT)

try:
    while True:
        if GPIO.input(sensor):
            GPIO.output(LED, False)
            while GPIO.input(sensor):
                time.sleep(0.2)
        else:
            GPIO.output(LED, True)
except KeyboardInterrupt:
    GPIO.cleanup()