import numpy as np
import cv2
import time
import math
capture = cv2.VideoCapture(0)
#print (capture.get(cv2.CAP_PROP_FPS))
while True:
    cap = cv2.VideoCapture('test1.avi') 
    while(cap.isOpened()):
        ret, frame = cap.read()
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        if ret == False : 
            print("Done with Instruction Frame")
            #cap.release()
            cv2.destroyAllWindows() 
                    
        cv2.imshow('Instruction Frame',frame) 
        if cv2.waitKey(1) & 0xFF == ord('q'):
             break 
    cap.release()
    cv2.destroyAllWindows()  
			
        
 


  
