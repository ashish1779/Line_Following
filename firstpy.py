#!/usr/bin/env python3

from tkinter import *
import serial

#Open ports

port1 = serial.Serial("/dev/ttyACM0", 115200)

def button1 ():
    port1.write(b'1')
    
def button2 ():
    port1.write(b'2')
    
def button3 ():
    port1.write(b'3')
    
def button4 ():
    port1.write(b'4')
    
def button5 ():
    port1.write(b'5')
    
def button6 ():
    port1.write(b'6')
    
def button7 ():
    port1.write(b'7')
    
#initialize

root = Tk()
root.geometry("300x200")
root.title("Manual Control")

#Create items
B1 = Button(root, text="UP", command=button1)
B1.pack()
B1.flash()

B2 = Button(root, text="DOWN", command=button2)
B2.pack()
B2.flash()

B3 = Button(root, text="LEFT", command=button3)
B3.pack(side=LEFT)
B3.flash()

B4 = Button(root, text="RIGHT", command=button4)
B4.pack(side=RIGHT)
B4.flash()


B6 = Button(root, text="FORWARD", command=button6)
B6.pack()
B6.flash()

B5 = Button(root, text="STOP", bg="red", fg="white", height = 3, width = 10, command=button5)
B5.pack()
B5.flash()

B7 = Button(root, text="BACKWARD", command=button7)
B7.pack(side=BOTTOM)
B7.flash()

root.mainloop()
