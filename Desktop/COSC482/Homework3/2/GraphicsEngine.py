# COSC 482 Homework #3 - 2
#
# The Stars screen saver program that places a random star on the screen every tenth of a second. Each star
# has a random starting position on the screen, random number of points from 5 to 15, random center color,
# and random point color. The stars are also given a random velocity and rotational velocity. When the star
# is created it will animate across the screen and eventually off the screen.
#
# Kalyn Howes
# 3/9/22

from OpenGL.GL import *
from OpenGL.GL.shaders import *
from Shader import *
import numpy as np
import ctypes
from PIL import Image
import random
import pygame
from time import time, sleep
import glm
from Star import *
from StarAttr import *

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

        # self.testStar = Star(0, 0, 5, 1, 0.3) # test one star: x,y,s,ro,ri
        # print('TEST STAR DATA: ', self.testStar.data)

        self.stars = []
        self.starAttrs = []

        # Get the start time of the program.
        self.start_time = time.time()

    def makeStar(self):
        # random starting position, number of points from 5 to 15, center color, and point color
        startPos = [random.uniform(-1, 1), random.uniform(-1, 1)]
        numSides = random.randint(5, 15)

        # limit the inner radii so they're not bigger than outer
        radii = [0.4 * random.random() + 0.25, 0.1 * random.random() + 0.05]
        self.stars.append(Star(startPos[0], startPos[1], numSides, radii[0], radii[1]))

        # given a random velocity and rotational velocity as well
        vel = [random.uniform(-0.005, 0.005), random.uniform(-0.005, 0.005)]
        rotVel = random.uniform(-60, 60)
        self.starAttrs.append(StarAttr(startPos[0], startPos[1], radii[0], radii[1], vel[0], vel[1], rotVel))

    # Turn on shader, clear screen, draw, swap display buffers.
    def update(self):
        glUseProgram(self.shaderProgram)
        glClear(GL_COLOR_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        currentTime = time.time()
        timeDifference = currentTime - self.start_time

        #print(timeDifference)
        # only make a star if it's been a tenth of second
        if timeDifference >= 0.1:
            self.makeStar()
            self.start_time = time.time()


        for i in range(len(self.stars)):
            ModelMatrix = glm.mat4(1.0)  # identity matrix
            # glUniformMatrix4fv(self.modelLoc, 1, GL_FALSE, glm.value_ptr(ModelMatrix))

            # update star in attribute class
            self.starAttrs[i].update(self.screenBounds)

            # rotation
            #print(self.starAttrs[i].rVelocity)
            #R = glm.rotate(timeDifference * self.starAttrs[i].rVelocity * np.pi / 180, glm.vec3(0, 0, 1))
            R = glm.rotate(self.starAttrs[i].rotate, glm.vec3(0, 0, 1))
            #print("rotation: \n", R)

            # translate
            T = glm.translate(ModelMatrix, glm.vec3(self.starAttrs[i].cx, self.starAttrs[i].cy, 0))
            #print('translation matrix: \n', T)

            # # random scaling factor
            # c = random.random()
            # S = glm.scale(ModelMatrix, glm.vec3(c, c, 1))

            ModelMatrix = T * R #* S
            #print('MM: \n', ModelMatrix)
            glUniformMatrix4fv(self.modelLoc, 1, GL_FALSE, glm.value_ptr(ModelMatrix))

            self.stars[i].draw()

        #self.testStar.draw() # drawing test star
        #self.stars[0].draw()

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
