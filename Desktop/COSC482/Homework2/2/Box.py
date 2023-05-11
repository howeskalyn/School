# COSC 482 Homework #2 - 2
#
# UI changes - mouse functionality.
#
# Kalyn Howes
# 2/28/22

from OpenGL.GL import *
import ctypes
import numpy as np

class Box():
    # Constructor
    def __init__(self, x = 0, y = 0, wd = 1, ht = 1, xd = 0, yd = 0):
        self.cx = x
        self.cy = y
        self.w = wd
        self.h = ht
        self.colors = [1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1]

        # for click & drag
        self.xDistance = 0
        self.yDistance = 0

        self.BoxVAO = glGenVertexArrays(1)
        self.ArrayBuffer = glGenBuffers(1)
        self.BoxEBO = glGenBuffers(1)

        self.LoadDataToGraphicsCard()

    # Load vertex, color, and index data to the graphics card.
    def LoadDataToGraphicsCard(self):
        vPosition = 0
        vColor = 1

        # Vertex and index data for the box, using two triangles.
        vertices = [self.cx - self.w/2, self.cy + self.h/2,
                    self.cx + self.w / 2, self.cy + self.h / 2,
                    self.cx + self.w / 2, self.cy - self.h / 2,
                    self.cx - self.w / 2, self.cy - self.h / 2
                    ]

        indices = [0, 3, 2, 0, 2, 1]

        # Convert data to GLSL form and get machine sizes of data types.
        indexdata = np.array(indices).astype(ctypes.c_uint)
        vertexdata = np.array(vertices).astype(ctypes.c_float)
        colordata = np.array(self.colors).astype(ctypes.c_float)
        floatsz = ctypes.sizeof(ctypes.c_float)
        uintsz = ctypes.sizeof(ctypes.c_uint)

        # Bind (turn on) a vertex array.
        glBindVertexArray(self.BoxVAO)

        # Load the indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.BoxEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indices), indexdata, GL_STATIC_DRAW)

        # Bindm(turn on) the vertex buffer (storage location).
        glBindBuffer(GL_ARRAY_BUFFER, self.ArrayBuffer)

        # Allocate  space for the vertex and color data.Do not load data at this point.
        glBufferData(GL_ARRAY_BUFFER, floatsz * (len(vertices) + len(self.colors)), None, GL_DYNAMIC_DRAW)

        # Load the vertex data.
        glBufferSubData(GL_ARRAY_BUFFER, 0, floatsz * len(vertices), vertexdata)

        # Load the color data.
        glBufferSubData(GL_ARRAY_BUFFER, floatsz * len(vertices), floatsz * len(self.colors), colordata)

        # Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(0))

        # Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
        glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(floatsz * len(vertices)))

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
    def setWidth(self, wd):
        self.w = wd
        self.LoadDataToGraphicsCard()

    # Return the width of the box.
    def getWidth(self):
        return self.w

    # Set the height of the box and reload the data.
    def setHeight(self, ht):
        self.h = ht
        self.LoadDataToGraphicsCard()

    # Return the height of the box.
    def getHeight(self):
        return self.h

    # Return the size [width, height] of the box.
    def getSize(self):
        return self.w, self.h

    # Set the size (width x height) of the box and reload the data.
    def setSize(self, wd, ht):
        self.w = wd
        self.h = ht
        self.LoadDataToGraphicsCard()

    # Set the color of the box
    def setColor(self, c):
        self.colors = c
        self.LoadDataToGraphicsCard()

    # Draw the box.
    def draw(self):
        glBindVertexArray(self.BoxVAO)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.BoxEBO)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, None)

    # returns a true boolean if the mouse point is inside the box & false otherwise
    # used to reset the color of the box
    def inBox(self, pos):
        #print(f'x: {pos[0]}, y:{pos[1]}')  # print testing
        ret = False

        r = self.cx + (self.w / 2)
        l = self.cx - (self.w / 2)
        u = self.cy + (self.h / 2)
        d = self.cy - (self.h / 2)

        if (pos[0] < r and pos[0] > l) and (pos[1] < u and pos[1] > d):
            ret = True

        return ret

    def updateDistance(self, mousepos):
        self.xDistance = mousepos[0] - self.cx
        self.yDistance = mousepos[1] - self.cy
