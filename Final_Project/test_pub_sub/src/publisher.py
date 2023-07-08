#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64, String

import RPi.GPIO as GPIO
import smbus #i2c

import time

import RPi.GPIO as GPIO
import spidev # spi 

address = 0x48
bus = smbus.SMBus(1)
cmd = 0x40

SW_Pin = 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(SW_Pin, GPIO.IN, GPIO.PUD_UP)

turnLeft = 22
GPIO.setup(turnLeft, GPIO.IN, GPIO.PUD_DOWN)

turnRight = 17
GPIO.setup(turnRight, GPIO.IN, GPIO.PUD_DOWN)

speedUp = 4
GPIO.setup(speedUp, GPIO.IN, GPIO.PUD_DOWN)

speedDown = 27
GPIO.setup(speedDown, GPIO.IN, GPIO.PUD_DOWN)

global message1, message2
global speed, angle

numCode = [
    0x7E,  # Số 0
    0x30,  # Số 1
    0x6D,  # Số 2
    0x79,  # Số 3
    0x33,  # Số 4
    0x5B,  # Số 5
    0x5F,  # Số 6
    0x70,  # Số 7
    0x7F,  # Số 8
    0x7B   # Số 9
]

def initSpi():

    # Định nghĩa thiết bị SPI
    spi = spidev.SpiDev()
    spi.open(0, 0)

    # Thiết lập module MAX7219
    spi.max_speed_hz = 10000000  # Đặt tốc độ clock SPI
    spi.mode = 0                  # Đặt chế độ SPI thành 0

    # Định nghĩa các thanh ghi cho MAX7219
    REG_DECODE_MODE = 0x09
    REG_INTENSITY = 0x0A
    REG_SCAN_LIMIT = 0x0B
    REG_SHUTDOWN = 0x0C
    REG_DISPLAY_TEST = 0x0F

    # Khởi tạo module MAX7219
    spi.xfer2([REG_DECODE_MODE, 0x00])  # Vô hiệu hóa chế độ giải mã cho tất cả các chữ số
    spi.xfer2([REG_INTENSITY, 7])       # Đặt độ sáng (0-15)
    spi.xfer2([REG_SCAN_LIMIT, 7])      # Giới hạn quét cho tất cả các chữ số
    spi.xfer2([REG_SHUTDOWN, 1])        # Hoạt động bình thường
    spi.xfer2([REG_DISPLAY_TEST, 0])    # Vô hiệu hóa kiểm tra hiển thị

    return spi

def displayNumbers(speed, spi):

    hangChuc = int (speed * 10 / 10)
    hangDonVi = int (speed * 10 % 10)
    if hangChuc == 10 :
        spi.xfer2([5, numCode[1]]) 
        spi.xfer2([4, numCode[0]])   
    else:
        spi.xfer2([5, numCode[hangChuc] | 0x80])  
        spi.xfer2([4, numCode[hangDonVi]])


def xiNhan(mode, spi):

    spi.xfer2([1 + mode , numCode[8]])  
    spi.xfer2([2 + mode, numCode[8]])
    time.sleep(0.02)
    spi.xfer2([1 + mode , 0x00])  
    spi.xfer2([2 + mode, 0x00])
    
def analogRead(chn):
    bus.write_byte(address, cmd + chn)
    value = bus.read_byte(address)
    return value

def analogWrite(value):
    bus.write_byte_data(address, cmd, value)

def checkButtonSpeed():
    global speed
    if GPIO.input(speedUp) ==1:
        speed += 0.3
        rospy.loginfo("Up")
        time.sleep(0.01)

    if GPIO.input(speedDown) ==1:
        speed -= 0.5
        rospy.loginfo("Down")
        time.sleep(0.05)
    
    if GPIO.input(SW_Pin) == 0:
        speed = 5

    if (speed >= 10): speed = 10
    if (speed <= 0): speed = 0
    return speed

def checkButtonAngle(val_Y):
    global angle 
    angle = 0
    #camera quay phai
    if  val_Y > 230:
        angle = -0.5
        rospy.loginfo("cam quay phai")

    #camera quay trai
    if val_Y < 20:
        angle = 0.5
        rospy.loginfo("cam quay trai")
        
    return angle

def Publisher():
    rospy.init_node("continuous_publisher")
    joint1 = rospy.Publisher('/robotBCD/joint1_velocity_controller/command', Float64, queue_size=10)
    joint2 = rospy.Publisher('/robotBCD/joint2_velocity_controller/command', Float64, queue_size=10)
    joint3 = rospy.Publisher('/robotBCD/joint3_velocity_controller/command', Float64, queue_size=10)
    rospy.Publisher('string_publish', String, queue_size=10)
    rate = rospy.Rate(10)

    message1 = Float64()
    message2 = Float64()
    message3 = Float64()
    spi = initSpi()

    while not rospy.is_shutdown():
        val_X = analogRead(2)
        val_Y = analogRead(0)

        speed = checkButtonSpeed()
        angle = checkButtonAngle(val_Y)

    
        if val_X > 200: #di thang
            velRight = speed
            velLeft = -speed
            rospy.loginfo("STRAIGHT")

            if GPIO.input(turnLeft) ==1:
                velRight = 6
                velLeft = -2
                rospy.loginfo("TURNRIGHT:")
                xiNhan(0, spi)

            if GPIO.input(turnRight) ==1:
                velRight= 2
                velLeft = -6
                rospy.loginfo("TURNLEFT:")
                xiNhan(6, spi)   
          
        elif val_X < 70: #di lui 
            velLeft = speed
            velRight = -speed

            rospy.loginfo("BACK:")
            xiNhan(0, spi)
            xiNhan(6, spi)

            if GPIO.input(turnLeft) ==1:
                velRight = -4
                velLeft = 2
                rospy.loginfo("TURNRIGHT:")
                xiNhan(0, spi)

            if GPIO.input(turnRight) ==1:
                velRight= -2
                velLeft = 4
                rospy.loginfo("TURNLEFT:")
                xiNhan(6, spi)   

        elif val_X <= 200 and val_Y <= 200 and val_X >= 50 and val_Y >= 50:
            velRight = 0
            velLeft = 0

            if GPIO.input(turnLeft) ==1:
                velRight = 3
                velLeft = 3
                time.sleep(0.05)

                rospy.loginfo("TURNRIGHT")
                xiNhan(0, spi)

            if GPIO.input(turnRight) ==1:
                velRight= -3
                velLeft = -3
                time.sleep(0.05)

                rospy.loginfo("TURNLEFT")
                xiNhan(6, spi)   

        displayNumbers(speed, spi)

        message1.data = float(velRight)
        message2.data = float(velLeft)
        message3.data = float(angle)

        #rospy.loginfo("Publishing value spped right: %s" % message1.data)
        #rospy.loginfo("Publishing value spped left: %s" % message2.data)
        #rospy.loginfo("Publishing value angle: %s" % message3.data)
        joint1.publish(message1)
        joint2.publish(message2)
        joint3.publish(message3)

    for i in range (8):
        spi.xfer2([i + 1, 0x00])  
    spi.close()
    rate.sleep()
    
if __name__ == "__main__":
    speed = 0
    angle = 0
    Publisher()