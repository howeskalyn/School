# COSC 482 Homework #3 - 3
#
# The eyes will follow the mouse pointer around the window.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
import ctypes
import numpy as np
import time
import Polygon

class PolygonAttr():
    # Constructor
    def __init__(self, x, y, r, xv, yv):

        # for movement
        self.xVelocity = xv
        self.yVelocity = yv
        self.r = r
        self.startX = x
        self.startY = y
        self.cx = x
        self.cy = y
        self.startTime = time.time()

    # next frame
    def update(self, mousePos):
        v = [mousePos[0] - self.cx, mousePos[1] - self.cy]
        self.cx = 0.1 * v[0]
        self.cy = 0.1 * v[1]

    # Set the center of the box and reload the data.
    def setCenter(self, x, y):
        self.cx = x
        self.cy = y

    def getVelocity(self):
        return [self.xVelocity, self.yVelocity]

    def getPosition(self):
        return [self.cx, self.cy]


