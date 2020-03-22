
## Drunk Driving Analysis

## when gas sensor on, LCD displays content and notifies in the local host and motor OFF or Otherwise


import RPi.GPIO as GPIO
import time
import os
import webbrowser           #import package for opening link in browser
import sys                  #import system package
import requests
import datetime
import webbrowser           #import package for opening link in browser

PIR=19
GAS = 18
RELAY1 = 20 
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(GAS, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(GAS, GPIO.IN)
GPIO.setup(RELAY1, GPIO.OUT)


# Define GPIO to LCD mapping
LCD_RS = 21
LCD_E  = 16
LCD_D4 = 23
LCD_D5 = 24
LCD_D6 = 25
LCD_D7 = 8

relay = 20
 
# Define some device constants
LCD_WIDTH = 16    # Maximum characters per line
LCD_CHR = True
LCD_CMD = False
 
LCD_LINE_1 = 0x80 # LCD RAM address for the 1st line
LCD_LINE_2 = 0xC0 # LCD RAM address for the 2nd line
 
# Timing constants
E_PULSE = 0.0005
E_DELAY = 0.0005
GPIO.setup(LCD_E, GPIO.OUT)  # E
GPIO.setup(LCD_RS, GPIO.OUT) # RS
GPIO.setup(LCD_D4, GPIO.OUT) # DB4
GPIO.setup(LCD_D5, GPIO.OUT) # DB5
GPIO.setup(LCD_D6, GPIO.OUT) # DB6
GPIO.setup(LCD_D7, GPIO.OUT) # DB7

GPIO.setup(relay, GPIO.OUT) # RELAY
GPIO.setup(PIR, GPIO.IN) # RELAY

# GPIO 23 set up as input. It is pulled up to stop false signals  
GPIO.setup(3, GPIO.IN, pull_up_down=GPIO.PUD_UP)
# GPIO 23 set up as input. It is pulled up to stop false signals  
GPIO.setup(2, GPIO.IN, pull_up_down=GPIO.PUD_UP)  


def lcd_init():
  # Initialise display
  lcd_byte(0x33,LCD_CMD) # 110011 Initialise
  lcd_byte(0x32,LCD_CMD) # 110010 Initialise
  lcd_byte(0x06,LCD_CMD) # 000110 Cursor move direction
  lcd_byte(0x0C,LCD_CMD) # 001100 Display On,Cursor Off, Blink Off
  lcd_byte(0x28,LCD_CMD) # 101000 Data length, number of lines, font size
  lcd_byte(0x01,LCD_CMD) # 000001 Clear display
  time.sleep(E_DELAY)
 
def lcd_byte(bits, mode):
  # Send byte to data pins
  # bits = data
  # mode = True  for character
  #        False for command
 
  GPIO.output(LCD_RS, mode) # RS
 
  # High bits
  GPIO.output(LCD_D4, False)
  GPIO.output(LCD_D5, False)
  GPIO.output(LCD_D6, False)
  GPIO.output(LCD_D7, False)
  if bits&0x10==0x10:
    GPIO.output(LCD_D4, True)
  if bits&0x20==0x20:
    GPIO.output(LCD_D5, True)
  if bits&0x40==0x40:
    GPIO.output(LCD_D6, True)
  if bits&0x80==0x80:
    GPIO.output(LCD_D7, True)
 
  # Toggle 'Enable' pin
  lcd_toggle_enable()
 
  # Low bits
  GPIO.output(LCD_D4, False)
  GPIO.output(LCD_D5, False)
  GPIO.output(LCD_D6, False)
  GPIO.output(LCD_D7, False)
  if bits&0x01==0x01:
    GPIO.output(LCD_D4, True)
  if bits&0x02==0x02:
    GPIO.output(LCD_D5, True)
  if bits&0x04==0x04:
    GPIO.output(LCD_D6, True)
  if bits&0x08==0x08:
    GPIO.output(LCD_D7, True)
 
  # Toggle 'Enable' pin
  lcd_toggle_enable()
 
def lcd_toggle_enable():
  # Toggle enable
  time.sleep(E_DELAY)
  GPIO.output(LCD_E, True)
  time.sleep(E_PULSE)
  GPIO.output(LCD_E, False)
  time.sleep(E_DELAY)    
 
def lcd_string(message,line):
  # Send string to display
 
  message = message.ljust(LCD_WIDTH," ")
 
  lcd_byte(line, LCD_CMD)
 
  for i in range(LCD_WIDTH):
    lcd_byte(ord(message[i]),LCD_CHR)
 
# Initialise display
lcd_init()

lcd_byte(0x80, LCD_CMD)
lcd_string("    WELCOME",LCD_LINE_1)
time.sleep(2) 

lcd_byte(0x01, LCD_CMD)
lcd_byte(0x80, LCD_CMD)
lcd_string("    DRIVER",LCD_LINE_1)
lcd_byte(0xC0, LCD_CMD)
lcd_string("ALCOHOL DETCTIN",LCD_LINE_2)
time.sleep(2) 
lcd_byte(0x01, LCD_CMD)
while True:
  
    
    i = GPIO.input(GAS)
    if (i == 0):
        GPIO.output(relay, False)
        lcd_byte(0x80, LCD_CMD)
        lcd_string("   ALCOHOL      ",LCD_LINE_1)
	lcd_byte(0xC0, LCD_CMD)
	lcd_string("  DETECTED      ",LCD_LINE_2) 
	ProblemDetected="Leakage with the pipe"
        resp = requests.get("http://****/gas/get.php?gas=ProblemDetected")
        
        print(resp.text)
        time.sleep(5)
        
    ##else:
	
	lcd_byte(0x80, LCD_CMD)
	lcd_string("    DRIVER      ",LCD_LINE_1)
	lcd_byte(0xC0, LCD_CMD)
	lcd_string("ALCOHOL DETECT  ",LCD_LINE_2)
	pir = GPIO.input(PIR)
        if (pir == 1):
            GPIO.output(relay, True)
##    
