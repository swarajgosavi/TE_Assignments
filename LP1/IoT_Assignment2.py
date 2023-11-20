import Adafruit_DHT
import RPi.GPIO as GPIO
import time

sensor = Adafruit_DHT.DHT11

pin = 16
LED = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.IN)
GPIO.setup(LED, GPIO.OUT)

while True:
    humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
    print('Temp={0.01f}*C Humidity={1.01f}%'.format(temperature, humidity))
    if temperature > 15:
        GPIO.output(LED, GPIO.HIGH)
        time.sleep(0.2)
    else:
        GPIO.output(LED, GPIO.LOW)