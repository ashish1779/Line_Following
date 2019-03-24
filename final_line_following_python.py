# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 16:48:52 2019

@author: Ashish Anand
"""

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np
import RPi.GPIO as GPIO 
#import serial
from serial import Serial


arduino = Serial('/dev/ttyACM0',9600)
Error_sent= " "
count = 0
Error = 0

GPIO.setmode(GPIO.BOARD)

camera = PiCamera()
camera.resolution = (640, 360)
camera.rotation = 180
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 360))
time.sleep(0.1)


for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):	
    image = frame.array
    roi = image[200:250, 0:639]   #region of interest
    bgr_arr = np.array(image)
    blue_arr = bgr_arr[:,:,0]
    ret, Whiteline = cv2.threshold(blue_arr,50,100, cv2.THRESH_BINARY)
    Black_block= cv2.inRange(roi,(0,0,0),(30,30,30))
    kernel = np.ones((3,3), np.uint8)
    Whiteline = cv2.erode(Whiteline, kernel, iterations=5)
    Whiteline = cv2.dilate(Whiteline, kernel, iterations=9)	
    Black_block = cv2.erode(Black_block, kernel, iterations=5)
    Black_block = cv2.dilate(Black_block, kernel, iterations=9)	
    contours_white, hierarchy = cv2.findContours(Whiteline.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)	
    contours_black, hierarchy = cv2.findContours(Black_block.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)	
    if len(contours_white) > 0 :
	x1,y1,w1,h1 = cv2.boundingRect(contours_white[0])
        if (x1 >= 0 and y1>=0 and w1 >=0 and h1>=0 ):
	    cv2.line(image, (x1+int(w1/2), 200), (x1+int(w1/2), 250),(255,0,0),3)
	    midpoint = 320
	    Error = (x1 + int(w1/2)) - midpoint
	    Error_sent = str(Error / 8 )
	else:
	    print("f**k")
	    Error = 0
	    Error_sent = str(Error)
    '''if len(contours_black) > 0 :
        x2,y2,w2,h2 = cv2.boundingRect(contours_black[0])	   
        #cv2.line(image, (x2+int(w2/2), 200), (x2+int(w2/2), 250),(0,0,255),3)
    '''
    cv2.drawContours(image, contours_white, -1, (255,0,0), 2)
    #cv2.drawContours(image, contours_black, -1, (0,0,255), 2)
    
    '''midpoint = 320
    Error = (x1 + int(w1/2)) - midpoint
    Error_sent = str(Error)'''
    print("Error_sent",Error_sent)
    while True:
	count+=1
	arduino.write(str.encode(Error_sent))
	print(arduino.readline())
	time.sleep(.1)
	if count == 2:
	    count = 0
	    break
	    
    cv2.imshow("Line Detect", image)	
    
    rawCapture.truncate(0)	
    key = cv2.waitKey(1) & 0xFF	
    if key == ord("q"):
	break
