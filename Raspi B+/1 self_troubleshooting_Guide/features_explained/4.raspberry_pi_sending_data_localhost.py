import time, datetime
import telepot
# import the necessary packages
from imutils.video import VideoStream
from pyzbar import pyzbar
import argparse
import datetime
import imutils
import time
import cv2 
import os
import webbrowser           #import package for opening link in browser
import sys                  #import system package
import requests
import random
import RPi.GPIO as GPIO
import time 
import math
import numpy as np
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(27,GPIO.IN)
GPIO.setup(17,GPIO.IN)
from telepot.loop import MessageLoop
now = datetime.datetime.now()  
def action(msg):
    chat_id = msg['chat']['id'] 
    command = msg['text']
    print ('Received: %s' % command)
    if command == 'Hi':
        telegram_bot.sendMessage (chat_id, str("Hi!!!"))
    else:
        telegram_bot.sendMessage (chat_id, str("Not matching with our database"))
        time.sleep(5)
        telegram_bot.sendMessage (chat_id, str("Redirecting to our Service team.."))
        first_names=('John','Andy','Joe')
        last_names=('Johnson','Smith','Williams')
        group=" ".join(random.choice(first_names)+" "+random.choice(last_names) for _ in range(1))
        URL = "http://ip_address/customercalls/get.php?"
        person_id=random.randrange(90067,100000,7) 
        telegram_bot.sendMessage (chat_id, str(person_id)+str(":")+str(group)+str(" will reach out to you "))
        PARAMS = {'person_id':person_id,'problem_detected':command} 
        # sending get request and saving the response as response object 
        r = requests.get(url = URL, params = PARAMS)
        print(r.text) 
telegram_bot = telepot.Bot('1095990063:AAFrNLJQEBmuNcKhR2bJ5El3hKRAjSJMm_s')
MessageLoop(telegram_bot, action).run_as_thread() 
while 1: 
    time.sleep(10)
   
		
