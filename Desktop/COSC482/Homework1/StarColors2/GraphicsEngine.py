# COSC 482 Homework #1: 2-7
# Produces an n-point star where n is chosen by the keyboard (2-9) or increased/decreased by the arrow keys,
# and now lets the user change the color of the points.
# Kalyn Howes
# 2.21.22

from OpenGL.GL import *
from OpenGL.GL.shaders import *
from Shader import *
import numpy as np
import ctypes
from PIL import Image
import math
import random

def constructTriangles(n, color):
    # ANGLE SET UP
    angles = []
    for i in range(1, n + 1):
        angles.append(i * (2 * math.pi / n))

    # ----- OUTER POINTS -----
    radiusOuter = 1

    # get separate x & y coordinates
    xOuter = [radiusOuter * math.cos(angle + math.pi/2) for angle in angles]
    yOuter = [radiusOuter * math.sin(angle + math.pi/2) for angle in angles]

    # moving formatting to while loop!
    # outerPoints = [] # hold all outer points in proper format
    # for i in range(n):
    #     outerPoints.append([color[0], color[1], color[1], xOuter[i], yOuter[i]]) # use random colors later

    # ----- INNER POINTS -----
    rInner = 0.3 # smaller radius for inner points

    # separate x & y coordinates
    xInner = [rInner * math.cos(angle + math.pi/n + math.pi/2) for angle in angles]
    yInner = [rInner * math.sin(angle + math.pi/n + math.pi/2) for angle in angles]

    # moving formatting to while loop!
    # innerPoints = [] # hold all inner points in proper format
    # for i in range(n):
    #     innerPoints.append([1, 1, 1, xInner[i], yInner[i]]) # first 3 parameters are rgb - STAY WHITE

    # ----- DATA FORMULATION -----
    center = [1, 1, 1, 0, 0] # holds center vertex

    # data format: (R, G, B, x, y) - need 3 to make triangle
    retData = []
    i = 0
    while i < n:
        retData.append(center)  # appending vertex: 1, 1, 1, 0, 0
        retData.append([color[0], color[1], color[2], xOuter[i], yOuter[i]])
        retData.append([1, 1, 1, xInner[i], yInner[i]])

        retData.append(center)
        retData.append([color[0], color[1], color[2], xOuter[i], yOuter[i]])
        retData.append([1, 1, 1, xInner[i-1], yInner[i-1]]) # using previous inner point, when i = 0, i = last index
        #print('Prev: ', innerPoints[i-1])
        i = i + 1
    return retData

class GraphicsEngine():
    # "Addresses" for OpenGL constructs.
    VAO = 0
    Buffer = 0
    vPosition = 0
    vColor = 1
    mode = GL_FILL
    shaderProgram = -1

    # Constructor
    def __init__(self):
        # Load shaders and compile shader programs.
        try:
            shader = Shader()
            self.shaderProgram = shader.loadShadersFromFile("PassThroughVert.glsl", "PassThroughFrag.glsl")
        except Exception as err:
            for i in range(len(err.args)):
                print(err.args[i])
            raise Exception(err)


        self.VAO = None
        self.Buffer = None

        self.numPoints = 5
        self.color = [1, 0, 0] # START W RED
        self.data = constructTriangles(self.numPoints, self.color)
        self.loadStarData(self.numPoints, self.color)
        # self.VAO = glGenVertexArrays(1)  # this shouldn't be created every time...
        # self.Buffer = glGenBuffers(1)  # this shouldn't be created every time...

    def loadStarData(self, numPoints, color):
        self.data = constructTriangles(numPoints, color)

        # if self.VAO or self.Buffer:
        #     glDeleteBuffers(1, self.Buffer)
        #     glDeleteVertexArrays(1, self.VAO)

        # Create the Vertex Array Object and bind.
        self.VAO = glGenVertexArrays(1) # this shouldn't be created every time...
        glBindVertexArray(self.VAO)

        # Create the Array Buffer and bind.
        self.Buffer = glGenBuffers(1) # this shouldn't be created every time...
        glBindBuffer(GL_ARRAY_BUFFER, self.Buffer)

        # Load the data to the graphics card using numpy to set the data type.
        gpudata = np.array(self.data).astype(ctypes.c_float)
        glBufferData(GL_ARRAY_BUFFER, gpudata.ravel(), GL_STATIC_DRAW)

        # Set the data attributes so the card knows how to interpret the data.
        floatsize = ctypes.sizeof(ctypes.c_float)
        glVertexAttribPointer(self.vColor, 3, GL_FLOAT, GL_TRUE, 5 * floatsize, ctypes.c_void_p(0))
        glVertexAttribPointer(self.vPosition, 2, GL_FLOAT, GL_FALSE, 5 * floatsize, ctypes.c_void_p(3 * floatsize))

        # Enable the arrays and set the "positions" for the shaders.
        glEnableVertexAttribArray(self.vPosition)
        glEnableVertexAttribArray(self.vColor)

    # Turn on shader, clear screen, draw triangles, swap display buffers.
    def update(self):
        glUseProgram(self.shaderProgram)
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)
        glDrawArrays(GL_TRIANGLES, 0, len(self.data))

    # Set mode to fill.
    def setFill(self):
        self.mode = GL_FILL

    # Set mode to line.
    def setLine(self):
        self.mode = GL_LINE

    # Set mode to point.
    def setPoint(self):
        self.mode = GL_POINT

    # Dump screen buffer data to raw pixels and convert to PIL Image object.
    def getScreenImage(self):
        viewport = glGetIntegerv(GL_VIEWPORT)
        glReadBuffer(GL_FRONT)
        pixels = glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE)
        image = Image.frombytes("RGB", (viewport[2], viewport[3]), pixels)
        image = image.transpose(Image.FLIP_TOP_BOTTOM)
        return image
