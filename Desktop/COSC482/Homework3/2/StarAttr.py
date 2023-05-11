# COSC 482 Homework #3 - 2
#
# The Stars screen saver program that places a random star on the screen every tenth of a second. Each star
# has a random starting position on the screen, random number of points from 5 to 15, random center color,
# and random point color. The stars are also given a random velocity and rotational velocity. When the star
# is created it will animate across the screen and eventually off the screen.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
import ctypes
import numpy as np
import time
#import Star

class StarAttr():
    # Constructor
    def __init__(self, x, y, ir, ro, xv, yv, rv):

        self.cx = x
        self.cy = y
        self.innerR = ir
        self.outerR = ro
        self.xVelocity = xv
        self.yVelocity = yv
        self.rVelocity = rv

        self.rotate = 1 # used in glm.rotate but included here so time is not necessary in ge

        self.startTime = time.time()

    # takes the elapsed time and adjusts the star's position for the next frame
    def update(self, screenBounds):
        currentTime = time.time()
        timeDifference = currentTime - self.startTime

        # rotation
        self.rotate = timeDifference * self.rVelocity * np.pi / 180

        # new position = start + dt * velocity
        self.cx = self.cx + timeDifference * self.xVelocity
        self.cy = self.cy + timeDifference * self.yVelocity

    # Set the center of the star and reload the data.
    def setCenter(self, x, y):
        self.cx = x
        self.cy = y

    def getVelocity(self):
        return [self.xVelocity, self.yVelocity]

    def getPosition(self):
        return [self.cx, self.cy]