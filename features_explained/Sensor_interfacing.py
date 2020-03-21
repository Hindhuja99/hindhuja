import time
import RPi.GPIO as GPIO
import time 
import random
# Import SPI library (for hardware SPI) and MCP3008 library.
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008

# Software SPI configuration:
CLK  = 11
MISO = 9
MOSI = 10
CS   = 8
mcp = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(27,GPIO.IN)
GPIO.setup(17,GPIO.IN)
try:
    while True:
        water_level= mcp.read_adc(0)
        if ((GPIO.input(27))==1):
			water_level=random.randrange(10,100,1)
			print "WATER LEVEL",water_level
			time.sleep(5)
        temp = mcp.read_adc(1)
        if ((GPIO.input(17))==0):
			temp=random.randrange(40,130,2)
			print "Temperature",temp
			time.sleep(5)
except KeyboardInterrupt:
    print ("EXIT")
  
			
        
 


  
