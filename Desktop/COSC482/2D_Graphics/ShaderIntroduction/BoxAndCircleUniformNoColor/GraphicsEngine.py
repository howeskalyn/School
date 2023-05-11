#! /usr/bin/env python3
#
# Graphics engine object sets up graphics card programs and data.
# Updates the display and has methods for mode changes and screen shots.
#
# Don Spickler
# 12/16/2021

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GL.shaders import *
from Shader import *
import pygame
import numpy as np
import ctypes
from PIL import Image
import glm
import random

from BoxNoColor import *
from Axes2D import *
from PolygonNoColor import *


class GraphicsEngine():
    # "Addresses" for OpenGL constructs.
    VAO = 0
    Buffer = 0
    vPosition = 0
    vColor = 1
    mode = GL_FILL
    shaderProgram = -1

    ScreenBounds = [-1, 1, -1, 1]

    # Constructor
    def __init__(self):
        # Load shaders and compile shader programs.
        try:
            shader = Shader()
            self.shaderProgram = shader.loadShadersFromFile("AspectRatioVert.glsl", "ConstantColorFrag.glsl")
            self.AxisProgram = shader.loadShadersFromFile("AspectRatioVert.glsl", "PassThroughFrag.glsl")
        except Exception as err:
            for i in range(len(err.args)):
                print(err.args[i])
            raise Exception(err)

        self.setProjectionMatrices(pygame.display.get_surface().get_size())

        glUseProgram(self.shaderProgram)
        self.constantColorLoc = glGetUniformLocation(self.shaderProgram, "ConstantColor")

        # Set clear/background color to black.
        glClearColor(0, 0, 0, 1)

        # Create and load the objects.
        self.axes = Axes2D()
        self.circle = Polygon(0, 0, 50, 0.5)

        self.colors = []
        self.boxes = []
        self.boxes.append(Box())
        self.colors.append([1, 0, 0])

        for i in range(10):
            x = 1.8 * random.random() - 0.9
            y = 1.8 * random.random() - 0.9
            w = 0.6 * random.random() + 0.1
            h = 0.6 * random.random() + 0.1
            box = Box(x, y, w, h)
            self.boxes.append(box)
            self.colors.append([random.random(), random.random(), random.random()])

    # Turn on shader, clear screen, draw axes and boxes, swap display buffers.
    def update(self):
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        glUseProgram(self.AxisProgram)
        self.axes.draw()

        glUseProgram(self.shaderProgram)

        for i in range(len(self.boxes)):
            glUniform4fv(self.constantColorLoc, 1, self.colors[i])
            self.boxes[i].draw()

        glUniform4fv(self.constantColorLoc, 1, [1, 0, 1])
        self.circle.draw()

        self.printOpenGLErrors()

    # Set render style to outline for all objects.
    def setOutlineMode(self):
        for i in range(len(self.boxes)):
            self.boxes[i].setOutline()

        self.circle.setOutline()

    # Set render style to fill for all objects.
    def setFillMode(self):
        for i in range(len(self.boxes)):
            self.boxes[i].setFill()

        self.circle.setFill()

    # Set mode to fill.
    def setFill(self):
        self.mode = GL_FILL

    # Set mode to line.
    def setLine(self):
        self.mode = GL_LINE

    # Set mode to point.
    def setPoint(self):
        self.mode = GL_POINT

    def setProjectionMatrices(self, size):
        self.setProjectionMatrix(size, self.shaderProgram, "Projection")
        self.setProjectionMatrix(size, self.AxisProgram, "Projection")

    # Set and load the projection matrix to the graphics card.
    def setProjectionMatrix(self, size, prog, name):
        w, h = size

        # if width > height create a matrix to map scene to [-a, a] X [-1, 1]
        # if height > width create a matrix to map scene to [-1, 1] X [-a, a]
        # glm.ortho creates the scaling matrix.
        if w > h:
            aspratio = w / h
            ProjectionMatrix = glm.ortho(-aspratio, aspratio, -1, 1)
            self.ScreenBounds = [-aspratio, aspratio, -1, 1]
        else:
            aspratio = h / w
            ProjectionMatrix = glm.ortho(-1, 1, -aspratio, aspratio)
            self.ScreenBounds = [-1, 1, -aspratio, aspratio]

        # print(ProjectionMatrix)
        # print(self.ScreenBounds)

        # Load Projection Matrix to the projection matrix in the shader.
        glUseProgram(prog)
        projLoc = glGetUniformLocation(prog, name)
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm.value_ptr(ProjectionMatrix))

    # Dump screen buffer data to raw pixels and convert to PIL Image object.
    def getScreenImage(self):
        viewport = glGetIntegerv(GL_VIEWPORT)
        glReadBuffer(GL_FRONT)
        pixels = glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE)
        image = Image.frombytes("RGB", (viewport[2], viewport[3]), pixels)
        image = image.transpose(Image.FLIP_TOP_BOTTOM)
        return image

    # Print out any errors in the OpenGL error queue.
    def printOpenGLErrors(self):
        errCode = glGetError()
        while errCode != GL_NO_ERROR:
            errString = gluErrorString(errCode)
            print("OpenGL Error: ", errString, "\n")
            errCode = glGetError()
