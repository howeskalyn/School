# COSC 482 Homework #3 - 1
#
# This program is to produce 50 random circles (bubbles) that bounce around the screen. When a bubble hits
# the edge of the screen it should bounce off in a natural manner. The point colors and the inside color are
# to be chosen at random. The initial starting point of each bubble and its direction and speed are also to be
# chosen at random.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
import ctypes
import numpy as np


class Polygon():
    # Constructor
    def __init__(self, x=0, y=0, s=3, rad=1):
        self.cx = x
        self.cy = y
        self.r = rad
        self.sides = s
        self.fill = True
        self.color = [1, 0, 0, 1]

        # Setup VAO and buffers.
        self.VAO = glGenVertexArrays(1)
        self.DataBuffer = glGenBuffers(1)
        self.FilledEBO = glGenBuffers(1)
        self.OutlineEBO = glGenBuffers(1)

        self.LoadDataToGraphicsCard()

    # Load vertex, color, and index data to the graphics card.
    def LoadDataToGraphicsCard(self):
        vPosition = 0
        vColor = 1

        # Create vertex and index data.
        vertices = [self.cx, self.cy]
        colors = []
        colors.extend(self.color)
        for i in range(self.sides + 1):
            vertices.extend([self.r * np.cos(i*2*np.pi/self.sides) + self.cx,
                             self.r * np.sin(i*2*np.pi/self.sides) + self.cy])
            colors.extend(self.color)

        indices = []
        for i in range(self.sides + 2):
            indices.append(i)

        outlineindices = indices[1:]

        # Convert data to GLSL form and get machine sizes of data types.
        indexdata = np.array(indices).astype(ctypes.c_uint)
        outlineindexdata = np.array(outlineindices).astype(ctypes.c_uint)
        vertexdata = np.array(vertices).astype(ctypes.c_float)
        colordata = np.array(colors).astype(ctypes.c_float)
        floatsz = ctypes.sizeof(ctypes.c_float)
        uintsz = ctypes.sizeof(ctypes.c_uint)

        # Bind (turn on) a vertex array.
        glBindVertexArray(self.VAO)

        # Remove old data.
        # glDeleteBuffers(1, self.DataBuffer)
        # glDeleteBuffers(1, self.FilledEBO)
        # glDeleteBuffers(1, self.OutlineEBO)

        # Setup buffers for new data.
        # self.DataBuffer = glGenBuffers(1)
        # self.FilledEBO = glGenBuffers(1)
        # self.OutlineEBO = glGenBuffers(1)

        # Load the indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indices), indexdata, GL_STATIC_DRAW)

        # Load the outline indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.OutlineEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(outlineindices), outlineindexdata, GL_STATIC_DRAW)

        # Bind (turn on) the vertex buffer (storage location).
        glBindBuffer(GL_ARRAY_BUFFER, self.DataBuffer)

        # Allocate  space for the vertex and color data.Do not load data at this point.
        glBufferData(GL_ARRAY_BUFFER, floatsz * (len(vertices) + len(colors)), None, GL_DYNAMIC_DRAW)

        # Load the vertex data.
        glBufferSubData(GL_ARRAY_BUFFER, 0, floatsz * len(vertices), vertexdata)

        # Load the color data.
        glBufferSubData(GL_ARRAY_BUFFER, floatsz * len(vertices), floatsz * len(colors), colordata)

        # Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(0))

        # Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(floatsz * len(vertices)))

        # Set position indexes for shader streams.
        glEnableVertexAttribArray(vPosition)
        glEnableVertexAttribArray(vColor)

    # Set the center of the box and reload the data.
    def setCenter(self, x, y):
        self.cx = x
        self.cy = y
        self.LoadDataToGraphicsCard()

    # Return the center of the box.
    def getCenter(self):
        return self.cx, self.cy

    # Set the width of the box and reload the data.
    def setRadius(self, rad):
        self.r = rad
        self.LoadDataToGraphicsCard()

    # Return the width of the box.
    def getRadius(self):
        return self.r

    # Set the height of the box and reload the data.
    def setSides(self, s):
        self.sides = s
        self.LoadDataToGraphicsCard()

    # Return the height of the box.
    def getSides(self):
        return self.sides

    # Set to fill mode.
    def setFill(self):
        self.fill = True

    # Set to outline mode.
    def setOutline(self):
        self.fill = False

    # Set the color of the box
    def setColor(self, c):
        self.color = c
        self.LoadDataToGraphicsCard()

    # Draw the box.
    def draw(self):
        glBindVertexArray(self.VAO)
        if self.fill:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.FilledEBO)
            glDrawElements(GL_TRIANGLE_FAN, self.sides + 2, GL_UNSIGNED_INT, None)
        else:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.OutlineEBO)
            glDrawElements(GL_LINE_LOOP, self.sides + 1, GL_UNSIGNED_INT, None)
