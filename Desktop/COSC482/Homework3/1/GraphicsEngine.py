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

        self.circles = []
        self.circleColors = []
        self.circleAttrs = []

        # self.testCircle = Polygon(0, 0, 50, 0.5) # test circle

        # circles of random radii between 0.1 and 0.2 centered at the origin
        numSides = 50
        for i in range(50):
            radius = 0.2 * random.random() + 0.1
            center = [0,0]
            self.circles.append(Polygon(center[0], center[1], numSides, radius)) # centerX, centerY, numSides, radius

            # random color process
            r = random.random()
            g = random.random()
            b = random.random()
            self.circles[len(self.circles) - 1].setColor([r, g, b, 0])
            self.circleColors.append([r, g, b, 0])

            velocity = [random.uniform(-0.5, 0.5), random.uniform(-0.5, 0.5)]
            self.circleAttrs.append(PolygonAttr(center[0], center[1], radius, velocity[0], velocity[1]))
            #print(f'Circle #{i} position: ', self.circleAttrs[i].cx, self.circleAttrs[i].cy)
            #print('Added random circle.')

        # Get the start time of the program.
        self.start_time = time.time()

    # Turn on shader, clear screen, draw, swap display buffers.
    def update(self):
        glUseProgram(self.shaderProgram)
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        for i in range(len(self.circles)):

            ModelMatrix = glm.mat4(1.0) # identity matrix

            # manual- directly changing the circles:
            # v = self.circleAttrs[i].getVelocity()
            # newX = self.circles[i].cx + v[0]
            # newY = self.circles[i].cy + v[1]
            # self.circles[i].setCenter(newX, newY)  # without using attr class *

            # update circle in attribute class
            self.circleAttrs[i].update(self.screenBounds)

            #print('MM BEFORE: ', ModelMatrix)
            ModelMatrix = glm.translate(ModelMatrix, glm.vec3(self.circleAttrs[i].cx, self.circleAttrs[i].cy, -1))
            glUniformMatrix4fv(self.modelLoc, 1, GL_FALSE, glm.value_ptr(ModelMatrix))
            #print('MM AFTER: ', ModelMatrix)

            self.circles[i].draw()

        # self.testCircle.draw() # drawing test circle

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
