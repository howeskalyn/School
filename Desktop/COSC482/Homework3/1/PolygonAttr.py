# COSC 482 Homework #3 - 1
#
# This program is to produce 50 random circles (bubbles) that bounce around the screen. When a bubble hits
# the edge of the screen it should bounce off in a natural manner. The point colors and the inside color are
# to be chosen at random. The initial starting point of each bubble and its direction and speed are also to be
# chosen at random.
#
# Stores the position of the circle to be rendered as well as its velocity. It should also have
# an update function that will take the elapsed time and adjust the circle’s position for the next frame.
# The graphics engine will ask this controller class for the position so it can set and load the matricies
# to the shaders.
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

    # takes the elapsed time and adjusts the circle's position for the next frame
    def update(self, screenBounds):
        currentTime = time.time()
        timeDifference = currentTime - self.startTime

        # new position = start + dt * velocity
        self.cx = self.startX + timeDifference * self.xVelocity
        self.cy = self.startY + timeDifference * self.yVelocity

        # ---- WALL HITS ----
        hit = False
        if self.cx - self.r <= screenBounds[0]: # left side
            self.xVelocity = -1 * self.xVelocity
            hit = True

        elif self.cx + self.r >= screenBounds[1]: # right side
            self.xVelocity = -1 * self.xVelocity
            hit = True

        elif self.cy - self.r <= screenBounds[2]: # top
            self.yVelocity = -1 * self.yVelocity
            hit = True

        elif self.cy + self.r >= screenBounds[3]: # bottom
            self.yVelocity = -1 * self.yVelocity
            hit = True

        if hit:
            self.startX = self.cx
            self.startY = self.cy
            self.startTime = currentTime

    # Set the center of the box and reload the data.
    def setCenter(self, x, y):
        self.cx = x
        self.cy = y

    def getVelocity(self):
        return [self.xVelocity, self.yVelocity]

    def getPosition(self):
        return [self.cx, self.cy]


