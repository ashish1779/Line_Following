# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 16:48:52 2019

@author: Ashish Anand
"""

import numpy as np
import cv2
import serial 
import time   

arduino = serial.Serial('com7',9600) 
arduino.flushInput()
#time.sleep(1) #get established
#print (arduino.readline()) #read the serial data and print it as line
raw_string=""

cap = cv2.VideoCapture(0)

def send_raw_cube():
	ready_signal = arduino.readline()	# original signal message

	# wait until arduino is ready
	ardu_ready = False	
		
	while ardu_ready == False:
		arduino_status = arduino.readline()
		time.sleep(0.01)
		if arduino_status == ready_signal:	# if arduino is ready
			ardu_ready = True
			time.sleep(0.01)

	arduino.write(str.encode(raw_string))
	print ("String sent: ", raw_string)

	time.sleep(0.01)


while True:
    ret, image = cap.read()
    roi = image#[200:250, 0:639]
    bgr_arr = np.array(image)
    blue_arr = bgr_arr[:,:,0]
    ret, Whiteline = cv2.threshold(blue_arr,50,100, cv2.THRESH_BINARY)
    Black_block= cv2.inRange(roi,(0,0,0),(30,30,30))
    kernel = np.ones((3,3), np.uint8)
    Whiteline = cv2.erode(Whiteline, kernel, iterations=5)
    Whiteline = cv2.dilate(Whiteline, kernel, iterations=9)	
    Black_block = cv2.erode(Black_block, kernel, iterations=5)
    Black_block = cv2.dilate(Black_block, kernel, iterations=9)	
    img_white,contours_white, hierarchy = cv2.findContours(Whiteline.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)	
    img_black,contours_black, hierarchy = cv2.findContours(Black_block.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)	
    if len(contours_white) > 0 :
        x1,y1,w1,h1 = cv2.boundingRect(contours_white[0])	   
        cv2.line(image, (x1+int(w1/2), 200), (x1+int(w1/2), 250),(255,0,0),3)
    if len(contours_black) > 0 :
        x2,y2,w2,h2 = cv2.boundingRect(contours_black[0])	   
        #cv2.line(image, (x2+int(w2/2), 200), (x2+int(w2/2), 250),(0,0,255),3)
    
    cv2.drawContours(image, contours_white, -1, (255,0,0), 2)
    #cv2.drawContours(image, contours_black, -1, (0,0,255), 2)
    
    midpoint = 320
    Error = (x1 + int(w1/2)) - midpoint
    Error_sent = str(Error)
    raw_string = Error_sent
    arduino.write(str.encode(raw_string))
    #print ("Error value sent" , raw_string)
    #time.sleep(.1)
    cv2.imshow("Line Detect", image)	
    #send_raw_cube()
    #while True:
    #time.sleep(0.01)
    print (arduino.readline())
        

    if cv2.waitKey(30) & 0xff == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()    
