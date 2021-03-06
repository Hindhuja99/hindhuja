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
from telepot.loop import MessageLoop
now = datetime.datetime.now()  
accessed=0
count=0
def action(msg):
    chat_id = msg['chat']['id'] 
    command = msg['text']
    print ('Received: %s' % command)
    if command == 'Hi':
        telegram_bot.sendMessage (chat_id, str("Hi!!!"))
        telegram_bot.sendMessage (chat_id, str("Accessing data.."))
		# construct the argument parser and parse the arguments
        ap = argparse.ArgumentParser()
        ap.add_argument("-o", "--output", type=str, default="barcodes.csv",help="path to output CSV file containing barcodes")
        args = vars(ap.parse_args()) 
		# initialize the video stream and allow the camera sensor to warm up
        print("[INFO] starting video stream...")
		# vs = VideoStream(src=0).start()
        vs = VideoStream(usepicamera=True).start()
        time.sleep(2.0)
		# open the output CSV file for writing and initialize the set of
		# barcodes found thus far
        csv = open(args["output"], "w")
        found = set()
        text1="Not Inserted"
		# loop over the frames from the video stream
        while True: 
			# grab the frame from the threaded video stream and resize it to
			# have a maximum width of 400 pixels
            frame = vs.read()
            frame = imutils.resize(frame, width=400)
			# find the barcodes in the frame and decode each of the barcodes
            barcodes = pyzbar.decode(frame)
			# loop over the detected barcodes
            for barcode in barcodes:
				# extract the bounding box location of the barcode and draw
				# the bounding box surrounding the barcode on the image
                (x, y, w, h) = barcode.rect
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0,255), 2)
				# the barcode data is a bytes object so if we want to draw it
				# on our output image we need to convert it to a string first
                barcodeData = barcode.data.decode("utf-8")
                barcodeData = "Model No. 5AB26726"
                barcodeType = barcode.type
				# draw the barcode data and barcode type on the image
                text = "{} ({})".format(barcodeData, barcodeType)
                cv2.putText(frame, text, (x, y - 10),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                text1="Inserted"
                #time.sleep(10.0)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
				# if the barcode text is currently not in our CSV file, write
				# the timestamp + barcode to disk and update the set
                if barcodeData not in found:
                    csv.write("{},{}\n".format(datetime.datetime.now(),barcodeData))
                    csv.flush()
                    found.add(barcodeData)
			# show the output frame
            cv2.imshow("Barcode Scanner", frame)
            key = cv2.waitKey(1) & 0xFF
			# if the `q` key was pressed, break from the loop
            if text1== "Inserted":
                print("Inserted Model No. 5AB26726")
                time.sleep(10.0)
                break
            if key == ord("q"):
                break
		# close the output CSV file do a bit of cleanup
        csv.close()
        cv2.destroyAllWindows()
        vs.stop()
        telegram_bot.sendMessage (chat_id, str("Authentication Done..")) 
        telegram_bot.sendMessage (chat_id, str("How may I help You ?")) 
        accessed=1 
        #print("accessed",accessed)
    elif command == 'what is my customer id': 
        telegram_bot.sendMessage (chat_id, str("Your ID : 5AB26726"))
    elif command == 'reasons for water leaks?': 
        telegram_bot.sendMessage (chat_id, str("The main reasons could be"))
        telegram_bot.sendMessage (chat_id, str("•	Cracks or breaks in water supply hoses to washer"))
        telegram_bot.sendMessage (chat_id, str("•	Clogged or improperly vented drain"))
        telegram_bot.sendMessage (chat_id, str("•	Too much of detergent"))	   
    elif command == '/start': 
        telegram_bot.sendMessage (chat_id, str("welcome!!"))  
    elif command == 'Where could these leakages happen':
        telegram_bot.sendDocument(chat_id, document=open('/home/pi/manualforleakageslocation.py'))
    elif command == 'How to rectify the leakage problem?':
        telegram_bot.sendDocument(chat_id, document=open('/home/pi/troubleshootleakage.py'))
        time.sleep(5)
        telegram_bot.sendMessage(chat_id, str("Go through the document, For AR of it,Click the corresponding letter")) 
    elif command == 'Thanks for the guidance':
        telegram_bot.sendMessage (chat_id, str("welcome!!")) 
    elif command == 'A': 
        capture = cv2.VideoCapture(0)
        #print (capture.get(cv2.CAP_PROP_FPS))
        t = 100
        w = 640.0
        last = 0 
        ok=0
        while True:
            ret, image = capture.read()
            img_height, img_width, depth = image.shape
            scale = w / img_width
            h = img_height * scale
            image = cv2.resize(image, (0,0), fx=scale, fy=scale)
            h=int(h)
            w=int(w)
            # Apply filters
            grey = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
            blured = cv2.medianBlur(grey, 15)

            # Compose 2x2 grid with all previews
            grid = np.zeros([2*h, 2*w, 3], np.uint8)
            grid[0:h, 0:w] = image

            # We need to convert each of them to RGB from grescaled 8 bit format
            grid[h:2*h, 0:w] = np.dstack([cv2.Canny(grey, t / 2, t)] * 3)
            grid[0:h, w:2*w] = np.dstack([blured] * 3)
            grid[h:2*h, w:2*w] = np.dstack([cv2.Canny(blured, t / 2, t)] * 3)

            #cv2.imshow('Image previews', grid)

            sc = 1
            md = 30
            at = 40
            circles = cv2.HoughCircles(blured, cv2.HOUGH_GRADIENT, sc, md, t, at)
            if circles is not None:
                # We care only about the first circle found.
                circle = circles[0][0]
                x, y, radius = int(circle[0]), int(circle[1]), int(circle[2])
                print(x, y, radius)
 
                # Highlight the circle
                cv2.circle(image, (x, y), radius, (0, 0, 255), 5)
                text="Object Detection Completed"
                cv2.putText(image, text, (x, y),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                ok=ok+1
                # Draw dot in the center
                cv2.circle(image, (x, y), 1, (0, 0, 255), 2) 
                if ok>=2:
                    time.sleep(10)
                    cap = cv2.VideoCapture('test1.avi')
                    while(cap.isOpened()):
                        ret, frame = cap.read()
				        #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
				         
                        if ret==True:
                            cv2.imshow('Instruction Frame',frame)
                        if cv2.waitKey(1) & 0xFF == ord('q'):
                            break 
                        if ret== False: 
                            print("Done with Instruction frame")
                            cap.release()
                            cv2.destroyAllWindows() 
                            ok=0 
                    #capture.stop()
            cv2.imshow('Image with detected circle', image)
            if cv2.waitKey(1) & 0xFF == ord('q'): 
                break
			
    else:
        telegram_bot.sendMessage (chat_id, str("Not matching with our database"))
        time.sleep(5)
        telegram_bot.sendMessage (chat_id, str("Redirecting to our Service team.."))
        first_names=('John','Andy','Joe')
        last_names=('Johnson','Smith','Williams')
        group=" ".join(random.choice(first_names)+" "+random.choice(last_names) for _ in range(1))
        URL = "http://169.254.239.177/customercalls/get.php?"
        person_id=random.randrange(90067,100000,7) 
        telegram_bot.sendMessage (chat_id, str(person_id)+str(":")+str(group)+str(" will reach out to you "))
        PARAMS = {'person_id':person_id,'problem_detected':command} 
        # sending get request and saving the response as response object 
        r = requests.get(url = URL, params = PARAMS)
        print(r.text) 
telegram_bot = telepot.Bot('1095990063:AAFrNLJQEBmuNcKhR2bJ5El3hKRAjSJMm_s')
MessageLoop(telegram_bot, action).run_as_thread() 
while 1: 
    chat_id=704863333
    water_level= mcp.read_adc(0)
    if ((GPIO.input(27))==1):
        water_level=random.randrange(10,100,1)
        print ("WATER LEVEL",water_level)
    temp = mcp.read_adc(1)
    if ((GPIO.input(17))==0):
        temp=random.randrange(40,60,2)
        if temp<=60:
            #print ("Temperature",temp)  
            count+=1
            #print("count",count)
            #print("accessed",accessed)
            if count>=3: 
                print ("Temperature",temp)
                telegram_bot.sendMessage (chat_id, str("Temperature level reading {} F is unsafe for your clothes").format(temp))
                telegram_bot.sendMessage (chat_id, str("Kindly follow our Guide for Proper Functioning")) 
                count=0
    time.sleep(10)
   
		
