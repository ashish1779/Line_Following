# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 23:15:19 2019

@author: Ashish Anand
"""

import sys
import os
import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while True:
    ret, img = cap.read()
    #img2 = cv2.resize(img,(360,480))
    bgr_arr = np.array(img)
    
    blue_arr = bgr_arr[:,:,0]
    #mask = cv2.inRange(blue_arr,80,130)
    ret, thresh = cv2.threshold(blue_arr,80,120, cv2.THRESH_BINARY)
    img2, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    res = cv2.bitwise_and(img,img, mask = thresh)
    cv2.drawContours(thresh, contours, -1, (0,255,0), 3)
    
    #(_,contours,hierarchy)=cv2.findContours(yellow,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        
    for pic, contour in enumerate(contours):
              area = cv2.contourArea(contour)
              if(area>30):
                   x,y,w,h = cv2.boundingRect(contour)     
                   thresh = cv2.rectangle(thresh,(x,y),(x+w,y+h),(255,0,0),2)
                   print(x,y,w,h)
    
    cv2.imshow('image',img) 
    cv2.imshow('image1',blue_arr)
    cv2.imshow('thresh',thresh)
    if cv2.waitKey(30) & 0xff == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()   
