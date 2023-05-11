#! /usr/bin/env python3
#
# Box object
#
# This object loads the vertex and color data into separate array buffers.  The data
# is packed and the drawing is indexed.
#
# Don Spickler
# 12/06/2021

from OpenGL.GL import *
import ctypes
import numpy as np

class Box_PackedIndexed():
    # Constructor
    def __init__(self, x = 0, y = 0, wd = 1, ht = 1):
        self.cx = x
        self.cy = y
        self.w = wd
        self.h = ht
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

        colors = [1, 0, 0,
                  0, 1, 0,
                  0, 0, 1,
                  1, 1, 1]

        indices = [0, 3, 2, 0, 2, 1]

        # Convert data to GLSL form and get machine sizes of data types.
        indexdata = np.array(indices).astype(ctypes.c_uint)
        vertexdata = np.array(vertices).astype(ctypes.c_float)
        colordata = np.array(colors).astype(ctypes.c_float)
        floatsz = ctypes.sizeof(ctypes.c_float)
        uintsz = ctypes.sizeof(ctypes.c_uint)

        self.BoxVAO = glGenVertexArrays(1)
        self.VertexBuffer = glGenBuffers(1)
        self.ColorBuffer = glGenBuffers(1)
        self.BoxEBO = glGenBuffers(1)

        # Bind (turn on) a vertex array.
        glBindVertexArray(self.BoxVAO)

        # Load the indexing array on the graphics card.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.BoxEBO)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uintsz * len(indices), indexdata, GL_STATIC_DRAW)

        # Bind (turn on) the vertex buffer, load data, set attributes.
        glBindBuffer(GL_ARRAY_BUFFER, self.VertexBuffer)
        glBufferData(GL_ARRAY_BUFFER, floatsz * len(vertices), vertexdata, GL_DYNAMIC_DRAW)
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(0))

        # Bind (turn on) the color buffer, load data, set attributes.
        glBindBuffer(GL_ARRAY_BUFFER, self.ColorBuffer)
        glBufferData(GL_ARRAY_BUFFER, floatsz * len(colors), colordata, GL_DYNAMIC_DRAW)
        glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(0))

        # Set position indexes for shader streams.
        glEnableVertexAttribArray(vPosition)
        glEnableVertexAttribArray(vColor)

    # Draw the box.
    def draw(self):
        glBindVertexArray(self.BoxVAO)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.BoxEBO)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, None)
