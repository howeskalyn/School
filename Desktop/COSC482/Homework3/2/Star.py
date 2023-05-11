# COSC 482 Homework #3 - 2
#
# The Stars screen saver program that places a random star on the screen every tenth of a second. Each star
# has a random starting position on the screen, random number of points from 5 to 15, random center color,
# and random point color. The stars are also given a random velocity and rotational velocity. When the star
# is created it will animate across the screen and eventually off the screen.
#
# Allows for stars of any number of points and any radius (length to the point from the center).
# The center of the star is always at the origin. Has functions to change the point color
# (color at all the tips of the points) and the center color. Loads only one set of vertex data
# but have two EBOs, one for a filled in star and one for the outline of the star.
# Has a boolean variable to select between the two and of course use this boolean
# value to determine which to use in the draw command of the star.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
import ctypes
import numpy as np
import math
import random

class Star():
    # Constructor
    def __init__(self, x=0, y=0, s=5, ro=1, ri=0.3):
        self.cx = x
        self.cy = y
        self.rOuter = ro
        self.rInner = ri
        self.sides = s
        self.fill = True
        self.color = []
        self.center = [1, 1, 1, 0, 0]

        self.data = []

        # Setup VAO and buffers.
        self.VAO = glGenVertexArrays(1)
        self.Buffer = glGenBuffers(1)
        self.FilledEBO = glGenBuffers(1)
        self.OutlineEBO = glGenBuffers(1)

        self.LoadDataToGraphicsCard()

    def LoadDataToGraphicsCard(self):
        vPosition = 0
        vColor = 1

        # set center colors to random
        self.center = [random.random(), random.random(), random.random(), 0, 0]

        # create vertices
        angles = []
        for i in range(1, self.sides + 1):
            angles.append(i * (2 * math.pi / self.sides))

        # ----- OUTER POINTS -----
        xOuter = [self.rOuter * math.cos(angle + math.pi / 2) for angle in angles]
        yOuter = [self.rOuter * math.sin(angle + math.pi / 2) for angle in angles]

        outerPoints = []  # hold all outer points in proper format
        randcol = [random.random(), random.random(), random.random()]
        for i in range(self.sides):
            # add in random colors
            outerPoints.append([randcol[0], randcol[1], randcol[2], xOuter[i], yOuter[i]])  # first 3 parameters are rgb

        # ----- INNER POINTS -----
        xInner = [self.rInner * math.cos(angle + math.pi / self.sides + math.pi / 2) for angle in angles]
        yInner = [self.rInner * math.sin(angle + math.pi / self.sides + math.pi / 2) for angle in angles]

        innerPoints = []  # hold all inner points in proper format
        randcol = [random.random(), random.random(), random.random()]
        for i in range(self.sides):
            innerPoints.append([randcol[0], randcol[1], randcol[2], xInner[i], yInner[i]]) # first 3 parameters are rgb

        # ----- DATA FORMULATION -----
        i = 0
        while i < self.sides:
            self.data.append(self.center)
            self.data.append(outerPoints[i])  # appending vertex: color, outerPoints[x], outerPoints[y]
            self.data.append(innerPoints[i])

            self.data.append(self.center)
            self.data.append(outerPoints[i])
            self.data.append(innerPoints[i - 1])  # using previous inner point, when i = 0, i = last index
            i = i + 1

        #print('DATA IN STAR: ', self.data)

        indices = []
        for i in range(len(self.data)):
            indices.append(i)

        outlineindices = indices[1:] # this needs changed to fit triangles....

        # Convert data to GLSL form and get machine sizes of data types.
        indexdata = np.array(indices).astype(ctypes.c_uint)
        outlineindexdata = np.array(outlineindices).astype(ctypes.c_uint)
        uintsz = ctypes.sizeof(ctypes.c_uint)

        glBindVertexArray(self.VAO)
        glBindBuffer(GL_ARRAY_BUFFER, self.Buffer)
        gpudata = np.array(self.data).astype(ctypes.c_float)
        glBufferData(GL_ARRAY_BUFFER, gpudata.ravel(), GL_STATIC_DRAW)

        # Set the data attributes so the card knows how to interpret the data.
        floatsize = ctypes.sizeof(ctypes.c_float)
        glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 5 * floatsize, ctypes.c_void_p(0))
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 5 * floatsize, ctypes.c_void_p(3 * floatsize))

        # Load the indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indices), indexdata, GL_STATIC_DRAW)

        # Load the outline indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.OutlineEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(outlineindices), outlineindexdata, GL_STATIC_DRAW)

        # Enable the arrays and set the "positions" for the shaders.
        glEnableVertexAttribArray(vPosition)
        glEnableVertexAttribArray(vColor)


    # Set the center of the star and reload the data.
    def setCenter(self, x, y):
        self.cx = x
        self.cy = y
        self.LoadDataToGraphicsCard()

    # Return the center of the star.
    def getCenter(self):
        return self.cx, self.cy

    # Set to fill mode.
    def setFill(self):
        self.fill = True

    # Set to outline mode.
    def setOutline(self):
        self.fill = False

    # Set the color of the star
    def setColor(self, c):
        self.color = c
        self.LoadDataToGraphicsCard()

    # Draw the box.
    def draw(self):
        glBindVertexArray(self.VAO)
        # glDrawArrays(GL_TRIANGLES, 0, len(self.data))
        # print(len(self.data))

        # # ******* DOESNT WORK **************
        if self.fill:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO)
            glDrawElements(GL_TRIANGLES,  len(self.data), GL_UNSIGNED_INT, None)
        else:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.OutlineEBO)
            glDrawElements(GL_LINE_LOOP,  len(self.data), 1, GL_UNSIGNED_INT, None)
            1#print('set to outline')



