# COSC 482: Homework 5 - 2
#
# Animated with the camera at the front of the train close to the tracks but slightly
# above them, so the viewer sees a roller coaster like animation of tracks moving underneath
# them.
#
# Kalyn Howes
# 3.28.22

from OpenGL.GL import *
import ctypes
import numpy as np
import math

class Track():
    # Constructor
    def __init__(self, iR=9.8, oR=10.2, x1=0, y1=0, z1=0):
        self.x = x1
        self.y = y1
        self.z = z1
        self.innerRadius = iR
        self.outerRadius = oR
        self.color = [1, 1, 1, 1]

        self.VAO = glGenVertexArrays(1)

        self.Buffer1 = glGenBuffers(1)
        self.Buffer2 = glGenBuffers(1)
        self.Buffer3 = glGenBuffers(1)

        self.FilledEBO1 = glGenBuffers(1)
        self.FilledEBO2 = glGenBuffers(1)
        self.FilledEBO3 = glGenBuffers(1)

        self.LoadDataToGraphicsCard()

    # Load vertex, color, and index data to the graphics card.
    def LoadDataToGraphicsCard(self):
        vPosition = 0
        vColor = 1

        innerVertices = []
        outerVertices = []
        railVertices = []
        numTies = 500

        # inner rail first
        for i in range(0, numTies):
            theta = i * 2 * math.pi / numTies
            x = self.innerRadius * math.cos(theta)
            y = math.sin(3 * theta) - 2 * math.cos(2 * (theta + 0.2)) + 2 * math.sin(7 * theta)
            z = self.innerRadius * math.sin(theta)

            innerVertices.append([1, 1, 1, x, y, z]) # color (white) & x,y,z
        #print(innerVertices)

        # outer rail
        for i in range(0, numTies):
            theta = i * 2 * math.pi / numTies
            x = self.outerRadius * math.cos(theta)
            y = math.sin(3 * theta) - 2 * math.cos(2 * (theta + 0.2)) + 2 * math.sin(7 * theta)
            z = self.outerRadius * math.sin(theta)

            outerVertices.append([1, 1, 1, x, y, z])  # color(white) & x,y,z
        #print(outerVertices)

        self.data = innerVertices
        self.data += outerVertices
        print(self.data)

        indicesInner = []
        for i in range(numTies):
            indicesInner.append(i)

        indicesOuter = []
        for i in range(numTies, numTies * 2):
            indicesOuter.append(i)

        indicesRails = []
        for i in range(0, 2 * numTies):
            indicesRails.append(i)
            indicesRails.append(i + numTies)

        # Convert data to GLSL form and get machine sizes of data types.
        indexdataInner = np.array(indicesInner).astype(ctypes.c_uint)
        indexdataOuter = np.array(indicesOuter).astype(ctypes.c_uint)
        indexdataRails = np.array(indicesRails).astype(ctypes.c_uint)

        uintsz = ctypes.sizeof(ctypes.c_uint)

        glBindVertexArray(self.VAO)
        glBindBuffer(GL_ARRAY_BUFFER, self.Buffer1)
        gpudata = np.array(self.data).astype(ctypes.c_float)
        glBufferData(GL_ARRAY_BUFFER, gpudata.ravel(), GL_STATIC_DRAW)

        # Load the indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO1)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indicesInner), indexdataInner, GL_STATIC_DRAW)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO2)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indicesOuter), indexdataOuter, GL_STATIC_DRAW)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO3)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indicesRails), indexdataRails, GL_STATIC_DRAW)

        # Set the data attributes so the card knows how to interpret the data.
        floatsize = ctypes.sizeof(ctypes.c_float)
        glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 6 * floatsize, ctypes.c_void_p(0))
        glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6 * floatsize, ctypes.c_void_p(3 * floatsize))

        # Enable the arrays and set the "positions" for the shaders.
        glEnableVertexAttribArray(vPosition)
        glEnableVertexAttribArray(vColor)

    def draw(self):
        glBindVertexArray(self.VAO)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO1)
        glDrawElements(GL_LINE_LOOP, len(self.data), GL_UNSIGNED_INT, None)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO2)
        glDrawElements(GL_LINE_LOOP, len(self.data), GL_UNSIGNED_INT, None)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO3)
        glDrawElements(GL_LINES, len(self.data), GL_UNSIGNED_INT, None)
