# COSC 482 Homework #3 - 3
#
# The eyes will follow the mouse pointer around the window.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
from OpenGL.GL.shaders import *
from Shader import *
import numpy as np
import ctypes
from PIL import Image
from Polygon import *
import random
import pygame
import time
import glm
from PolygonAttr import *
from Polygon import *

class GraphicsEngine():
    # "Addresses" for OpenGL constructs.
    VAO = 0
    Buffer = 0
    vPosition = 0
    vColor = 1
    mode = GL_FILL
    shaderProgram = -1
    screenBounds = [-1, 1, -1, 1]

    # Constructor
    def __init__(self):
        # Load shaders and compile shader programs.
        try:
            shader = Shader()
            self.shaderProgram = shader.loadShadersFromFile("AspectRatioAndTransformVert.glsl", "PassThroughFrag.glsl")
        except Exception as err:
            for i in range(len(err.args)):
                print(err.args[i])
            raise Exception(err)

        # Turn on program, get the location of the projection and model matrices in the shader.
        glUseProgram(self.shaderProgram)
        self.projLoc = glGetUniformLocation(self.shaderProgram, "Projection")
        self.modelLoc = glGetUniformLocation(self.shaderProgram, "Model")
        self.setProjectionMatrix(pygame.display.get_surface().get_size())

        # Set clear/background color to black.
        glClearColor(0, 0, 0, 1)

        # self.eyes = []
        # self.pupils = []
        # self.pupilAttr = []

        self.circles = [] # first 2 will be whites of eyes, then pupils
        self.circleAttr = []

        # eyes
        self.circles.append(Polygon(0.4, 0, 50, 0.2))
        self.circles[len(self.circles) - 1].setColor([1, 1, 1, 0])
        self.circles.append(Polygon(-0.4, 0, 50, 0.2))
        self.circles[len(self.circles) - 1].setColor([1, 1, 1, 0])
        # pupils
        self.circles.append(Polygon(0.4, 0, 50, 0.08))
        self.circles[len(self.circles) - 1].setColor([0, 0, 0, 0])
        self.circles.append(Polygon(-0.4, 0, 50, 0.08))  # centerX, centerY, numSides, radius
        self.circles[len(self.circles) - 1].setColor([0, 0, 0, 0])

        velocity = [random.uniform(-0.01, 0.01), random.uniform(-0.01, 0.01)]

        # eyes attrs
        self.circleAttr.append(PolygonAttr(0, 0, 0.2, 0, 0))
        self.circleAttr.append(PolygonAttr(0, 0, 0.2, 0, 0))
        # pupils attrs
        self.circleAttr.append(PolygonAttr(0, 0, 0.08, velocity[0], velocity[1]))
        self.circleAttr.append(PolygonAttr(0, 0, 0.08, velocity[0], velocity[1]))

        # Get the start time of the program.
        self.start_time = time.time()

    # Turn on shader, clear screen, draw, swap display buffers.
    def update(self):
        glUseProgram(self.shaderProgram)
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        for i in range(len(self.circles)):

            ModelMatrix = glm.mat4(1.0) # identity matrix
            ModelMatrix = glm.translate(ModelMatrix, glm.vec3(self.circleAttr[i].cx, self.circleAttr[i].cy, -1))
            glUniformMatrix4fv(self.modelLoc, 1, GL_FALSE, glm.value_ptr(ModelMatrix))

            self.circles[i].draw()

        self.printOpenGLErrors()

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

    # Set and load the projection matrix to the graphics card.
    def setProjectionMatrix(self, size):
        w, h = size

        # if width > height create a matrix to map scene to [-a, a] X [-1, 1]
        # if height > width create a matrix to map scene to [-1, 1] X [-a, a]
        if w > h:
            aspratio = w / h
            ProjectionMatrix = glm.ortho(-aspratio, aspratio, -1, 1) # glm.ortho creates the scaling matrix
            self.screenBounds = [-aspratio, aspratio, -1, 1]
        else:
            aspratio = h / w
            ProjectionMatrix = glm.ortho(-1, 1, -aspratio, aspratio) # glm.ortho creates the scaling matrix
            self.screenBounds = [-1, 1, -aspratio, aspratio]

        # Load Projection Matrix to the projection matrix in the shader.
        glUniformMatrix4fv(self.projLoc, 1, GL_FALSE, glm.value_ptr(ProjectionMatrix))

    # Print out any errors in the OpenGL error queue.
    def printOpenGLErrors(self):
        errCode = glGetError()
        while errCode != GL_NO_ERROR:
            errString = gluErrorString(errCode)
            print("OpenGL Error: ", errString, "\n")
            errCode = glGetError()
