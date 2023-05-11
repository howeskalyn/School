# COSC 482 Homework #2 - 4
#
# boxes screensaver!
#
# Kalyn Howes
# 2/28/22

from OpenGL.GL import *
from OpenGL.GL.shaders import *
from Shader import *
import numpy as np
import ctypes
from PIL import Image
from Box import *

class GraphicsEngine():
    # "Addresses" for OpenGL constructs.
    VAO = 0
    Buffer = 0
    vPosition = 0
    vColor = 1
    mode = GL_FILL
    shaderProgram = -1
    screenBounds = [-1, 1, -1, 1]  # Set to the default here but could be a custom setting [lx, ux, ly, uy].

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

        # Set clear/background color to black.
        glClearColor(0, 0, 0, 1)

        self.boxes = []
        self.boxColors = []
        self.selectedBoxes = [] # holds bools not the boxes themselves - 1 if selected & 0 if not

        # initalize selectedBoxes with all 0s
        for i in range(len(self.boxes)):
            self.selectedBoxes[i] = 0

    # Turn on shader, clear screen, draw triangles, swap display buffers.
    def update(self):
        glUseProgram(self.shaderProgram)
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        # draw multiple boxes
        if len(self.boxes) > 0:
            for i in range(len(self.boxes)):
                self.boxes[i].draw()

    # Set mode to fill.
    def setFill(self):
        self.mode = GL_FILL

    # Set mode to line.
    def setLine(self):
        self.mode = GL_LINE

    # Set mode to point.
    def setPoint(self):
        self.mode = GL_POINT

    # Get the real world screen bounds.
    def getScreenBounds(self):
        return self.screenBounds

    # Get the current viewport dimensions.
    def getViewport(self):
        return glGetIntegerv(GL_VIEWPORT)

    # Dump screen buffer data to raw pixels and convert to PIL Image object.
    def getScreenImage(self):
        viewport = glGetIntegerv(GL_VIEWPORT)
        glReadBuffer(GL_FRONT)
        pixels = glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE)
        image = Image.frombytes("RGB", (viewport[2], viewport[3]), pixels)
        image = image.transpose(Image.FLIP_TOP_BOTTOM)
        return image

    # takes in position of mouse & deletes if there is a box in that spot
    def deleteBox(self, pos):
        for i in range(len(self.boxes)):
            if self.boxes[i].inBox(pos):
                self.boxes.remove(self.boxes[i])
                # use destructor
                del self.boxColors[i]
                # del self.boxes[i]
                # del self.ge.isSelected[i]
                # del self.selectedBoxes[i]