# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 01:00:01 2019

@author: Ashish Anand
"""

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

camera = PiCamera()
camera.resolution = (640, 360)
camera.rotation = 180
rawCapture = PiRGBArray(camera, size=(640, 360))
time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):	
	image = frame.array
	roi = image[200:250, 0:639]
	bgr_arr = np.array(image)
        blue_arr = bgr_arr[:,:,0]
        ret, Whiteline = cv2.threshold(blue_arr,50,100, cv2.THRESH_BINARY)
	#Whiteline= cv2.inRange(roi, (0,0,0), (50,50,50))
	kernel = np.ones((3,3), np.uint8)
	Whiteline = cv2.erode(Whiteline, kernel, iterations=5)
	Whiteline = cv2.dilate(Whiteline, kernel, iterations=9)	
	contours, hierarchy = cv2.findContours(Whiteline.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)	
	if len(contours) > 0 :
	   x,y,w,h = cv2.boundingRect(contours[0])	   
	   cv2.line(image, (x+(w/2), 200), (x+(w/2), 250),(255,0,0),3)
	cv2.imshow("Line Detect", image)	
	rawCapture.truncate(0)	
	key = cv2.waitKey(1) & 0xFF	
	if key == ord("q"):
		break
