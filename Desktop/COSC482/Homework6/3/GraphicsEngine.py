# COSC 482 - Homework 6 - 1
#
# Frankenstein Exercises
#
# Kalyn Howes
# 4/15/22

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GL.shaders import *
from Shader import *
import pygame
import numpy as np
import ctypes
from PIL import Image
import glm
import time
import random

from Cube import *
from Sphere import *
from Cylinder import *
from Torus import *
from Trefoil import *
from Plane import *
from HeightMap import *
from ModelData import *
from Axes3D import *
from SphericalCamera import *
from YPRCamera import *
from Light import *
from Material import *


class GraphicsEngine():
    mode = GL_FILL
    shaderProgram = -1
    cameranum = 0
    displayobjmode = 1
    showaxes = True
    showlight = True
    projectionMatrix = glm.mat4(1)
    viewMatrix = glm.mat4(1)

    # Constructor
    def __init__(self):
        # Load shaders and compile shader programs.
        try:
            shader = Shader()
            self.AxesShader = shader.loadShadersFromFile("Shaders/VertexShaderBasic3D.glsl",
                                                         "Shaders/PassThroughFrag.glsl")
            self.LightingShader = shader.loadShadersFromFile("Shaders/VertexShaderLighting.glsl",
                                                             "Shaders/PhongMultipleLights.glsl")
            self.ConstColorShader = shader.loadShadersFromFile("Shaders/VertexShaderBasic3D.glsl",
                                                               "Shaders/ConstantColorFrag.glsl")
        except Exception as err:
            for i in range(len(err.args)):
                print(err.args[i])
            raise Exception(err)

        # Turn on program, get the locations of some of the uniform variables.
        glUseProgram(self.AxesShader)
        self.projviewLoc = glGetUniformLocation(self.AxesShader, "ProjView")
        self.modelLoc = glGetUniformLocation(self.AxesShader, "Model")

        glUseProgram(self.LightingShader)
        self.projviewLocPhong = glGetUniformLocation(self.LightingShader, "ProjView")
        self.modelLocPhong = glGetUniformLocation(self.LightingShader, "Model")
        self.normalMatrixLocPhong = glGetUniformLocation(self.LightingShader, "NormalMatrix")
        GlobalAmbient = glm.vec4(0.2, 0.2, 0.2, 1)
        glUniform4fv(glGetUniformLocation(self.LightingShader, "GlobalAmbient"),
                     1, glm.value_ptr(GlobalAmbient))
        glUniform1i(glGetUniformLocation(self.LightingShader, "numLights"), 3)

        glUseProgram(self.ConstColorShader)
        self.projviewLocConst = glGetUniformLocation(self.ConstColorShader, "ProjView")
        self.modelLocConst = glGetUniformLocation(self.ConstColorShader, "Model")
        lightcol = glm.vec4(1, 1, 0, 1)
        glUniform4fv(glGetUniformLocation(self.ConstColorShader, "ConstantColor"),
                     1, glm.value_ptr(lightcol))

        self.setProjectionMatrix(pygame.display.get_surface().get_size())

        # Set clear/background color to black and turn on depth testing.
        glClearColor(0, 0, 0, 1)
        # glClearColor(1, 1, 1, 1)
        glEnable(GL_DEPTH_TEST)
        # glEnable(GL_CULL_FACE)

        # Create the cameras.
        self.sphericalcamera = SphericalCamera(30, 60, 45)
        self.yprcamera = YPRCamera()
        self.setViewMatrix()

        # Create and load the objects.
        self.axes = Axes3D()

        # -------- Create Plane & Towers & Laser Beam --------------
        self.plane2 = Plane(2, 2, 20, 20, 'y')

        self.mat = Material()
        self.torus2 = Torus()
        self.sphere2 = Sphere()
        self.cylinder = Cylinder(r=0.05)

        self.lights = []
        for i in range(3):
            self.lights.append(Light())
        self.lightcamera = SphericalCamera(20, 45, 45)

        # Set light positions.  Light 0 will ne locked to the lightcamera object.
        self.lights[0].position = glm.vec4(self.lightcamera.getPosition(), 1)
        self.lights[1].position = glm.vec4(-10, 20, -10, 1)
        self.lights[2].position = glm.vec4(10, -20, -10, 1)

        # Tone down the intensity of the lights.
        # lightFactor = 1
        lightFactor = 0.75
        for i in range(3):
            self.lights[i].diffuse = lightFactor * self.lights[i].diffuse
            self.lights[i].specular = lightFactor * self.lights[i].specular

        self.mat.LoadMaterial(self.LightingShader, "Mat")
        self.activeGlow = False

        # Get the start time of the program.
        self.start_time = time.time()

    # Loads the model matrix, calculates the normal matrix, (M^(-1))^T, and loads
    # it to the shader.  Function assumes that the lighting shader program is active.
    def LoadMatrices(self, model):
        glUniformMatrix4fv(self.modelLocPhong, 1, GL_FALSE, glm.value_ptr(model))
        NM = glm.inverse(glm.transpose(glm.mat3(model)))
        glUniformMatrix3fv(self.normalMatrixLocPhong, 1, GL_FALSE, glm.value_ptr(NM))

    # Turn on shader, clear screen, draw axes, cubes, or box.
    def update(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, self.mode)

        # Draw axes if selected.
        if self.showaxes:
            glUseProgram(self.AxesShader)
            axestrans = glm.scale(glm.vec3(10))
            glUniformMatrix4fv(self.modelLoc, 1, GL_FALSE, glm.value_ptr(axestrans))
            self.axes.draw()

        # Draw position of the light if selected.
        if self.showlight:
            glUseProgram(self.ConstColorShader)
            self.lights[0].position = glm.vec4(self.lightcamera.getPosition(), 1)
            for i in range(3):
                lightobjmodel = glm.translate(glm.vec3(self.lights[i].position))
                glUniformMatrix4fv(self.modelLocConst, 1, GL_FALSE, glm.value_ptr(lightobjmodel))

        # Draw remainder of scene.
        glUseProgram(self.LightingShader)

        # Set the light position from the light "camera". Load to shader.
        self.lights[0].position = glm.vec4(self.lightcamera.getPosition(), 1)
        for i in range(3):
            self.lights[i].LoadLight(self.LightingShader, "Lt[" + str(i) + "]")

        # Get the position of the camera and load to the shader.
        eye = glm.vec3(0, 0, 0)
        if self.cameranum == 0:
            eye = self.sphericalcamera.getPosition()
        elif self.cameranum == 1:
            eye = self.yprcamera.getPosition()

        glUniform3fv(glGetUniformLocation(self.LightingShader, "eye"), 1, glm.value_ptr(eye))

        # Draw selected objects with appropriate transformations.
        if self.displayobjmode == 1:

            # ---- PLANE ----
            self.mat.dullGreen()
            self.mat.LoadMaterial(self.LightingShader, "Mat")

            planemodel = glm.scale(glm.vec3(10))
            self.LoadMatrices(planemodel)
            self.plane2.draw()

            # randomize the spheres to which the laser beams connect
            randomchoice = random.randint(0, 6)

            # ---- TORI ----
            for donuts in range (0, 4):
                S = glm.scale(glm.vec3(3.25))
                R = glm.rotate(np.pi / 2, glm.vec3(1, 0, 0))
                sphereS = glm.scale(glm.vec3(1.05))

                timeDifference = time.time() - self.start_time

                if donuts == 0:
                    i = 1
                    u = 0
                    for stacks in range(0, 8):
                        if stacks < 7:
                            T = glm.translate(glm.vec3(5, 1.25 + u, 5))
                            S = glm.scale(glm.vec3(3.25 * i))
                            R = glm.rotate(np.pi / 2, glm.vec3(1, 0, 0))
                            self.LoadMatrices(T * R * S)

                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.metallicBlue()

                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.torus2.draw()

                        if stacks == 7:
                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)  # glow for the sphere
                            else:
                                self.mat.Pewter2()

                            sphereT = glm.translate(glm.vec3(5, 1.75 + u, 5))
                            self.LoadMatrices(sphereT * sphereS)
                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.sphere2.draw()

                            if stacks == self.activeGlow:
                                self.drawCylinder(randomchoice)

                        i = i - 0.09999999
                        u = u + 2 * i

                elif donuts == 1:
                    i = 1
                    u = 0
                    for stacks in range(0, 8):
                        if stacks < 7:
                            T = glm.translate(glm.vec3(-5, 1.25 + u, -5))
                            S = glm.scale(glm.vec3(3.25 * i))
                            R = glm.rotate(np.pi / 2, glm.vec3(1, 0, 0))
                            self.LoadMatrices(T * R * S)

                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.metallicBlue()

                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.torus2.draw()

                        if stacks == 7:
                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)  # glow for the sphere
                            else:
                                self.mat.Pewter2()

                            sphereT = glm.translate(glm.vec3(-5, 1.75 + u, -5))
                            self.LoadMatrices(sphereT * sphereS)
                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.sphere2.draw()

                            if stacks == self.activeGlow:
                                self.drawCylinder(randomchoice)

                        i = i - 0.09999999
                        u = u + 2 * i

                elif donuts == 2:
                    i = 1
                    u = 0
                    for stacks in range(0, 8):
                        if stacks < 7:
                            T = glm.translate(glm.vec3(-5, 1.25 + u, 5))
                            S = glm.scale(glm.vec3(3.25 * i))
                            R = glm.rotate(np.pi / 2, glm.vec3(1, 0, 0))
                            self.LoadMatrices(T * R * S)

                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.metallicBlue()

                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.torus2.draw()

                        if stacks == 7:
                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.Pewter2()

                            sphereT = glm.translate(glm.vec3(-5, 1.75 + u, 5))
                            self.LoadMatrices(sphereT * sphereS)
                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.sphere2.draw()

                            if stacks == self.activeGlow:
                                self.drawCylinder(randomchoice)

                        i = i - 0.09999999
                        u = u + 2 * i

                elif donuts == 3:
                    i = 1
                    u = 0
                    for stacks in range(0, 8):
                        if stacks < 7:
                            T = glm.translate(glm.vec3(5, 1.25 + u, -5))
                            S = glm.scale(glm.vec3(3.25 * i))
                            R = glm.rotate(np.pi / 2, glm.vec3(1, 0, 0))
                            self.LoadMatrices(T * R * S)

                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.metallicBlue()

                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.torus2.draw()

                        if stacks == 7:
                            if stacks == self.activeGlow:
                                self.mat.glow(timeDifference)
                            else:
                                self.mat.Pewter2()

                            sphereT = glm.translate(glm.vec3(5, 1.75 + u, -5))
                            self.LoadMatrices(sphereT * sphereS)
                            self.mat.LoadMaterial(self.LightingShader, "Mat")
                            self.sphere2.draw()

                            if stacks == self.activeGlow:
                                self.drawCylinder(randomchoice)

                        i = i - 0.09999999
                        u = u + 2 * i

                torusmodel = T * R * S
                self.LoadMatrices(torusmodel)
                self.torus2.draw()

            self.activeGlow = math.floor(timeDifference) % 8
            timeDifference = 0

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

    # Set and load the projection matrix to the graphics card.
    def setProjectionMatrix(self, size):
        w, h = size
        self.projectionMatrix = glm.perspective(glm.radians(50.0), w / h, 0.01, 500.0)
        PV = self.projectionMatrix * self.viewMatrix
        glUseProgram(self.AxesShader)
        glUniformMatrix4fv(self.projviewLoc, 1, GL_FALSE, glm.value_ptr(PV))
        glUseProgram(self.LightingShader)
        glUniformMatrix4fv(self.projviewLocPhong, 1, GL_FALSE, glm.value_ptr(PV))
        glUseProgram(self.ConstColorShader)
        glUniformMatrix4fv(self.projviewLocConst, 1, GL_FALSE, glm.value_ptr(PV))

    # Set and load the view matrix to the graphics card.
    def setViewMatrix(self):
        if self.cameranum == 0:
            self.viewMatrix = self.sphericalcamera.lookAt()
        else:
            self.viewMatrix = self.yprcamera.lookAt()

        PV = self.projectionMatrix * self.viewMatrix
        glUseProgram(self.AxesShader)
        glUniformMatrix4fv(self.projviewLoc, 1, GL_FALSE, glm.value_ptr(PV))
        glUseProgram(self.LightingShader)
        glUniformMatrix4fv(self.projviewLocPhong, 1, GL_FALSE, glm.value_ptr(PV))
        glUseProgram(self.ConstColorShader)
        glUniformMatrix4fv(self.projviewLocConst, 1, GL_FALSE, glm.value_ptr(PV))

    # Toggle between the two cameras.
    def toggleCamera(self):
        if self.cameranum == 0:
            self.cameranum = 1
        else:
            self.cameranum = 0

    # Toggle the drawing of the axes.
    def toggleAxes(self):
        self.showaxes = not self.showaxes

    # Toggle the drawing of the axes.
    def toggleLight(self):
        self.showlight = not self.showlight

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

    # draws the cylinder in the proper location based on which random spheres are chosen
    def drawCylinder(self, randomchoice):
        self.mat.Turquoise()
        self.mat.LoadMaterial(self.LightingShader, "Mat")

        cylindermodel = glm.vec3(1)

        if randomchoice == 0:
            cylindermodel = glm.translate(glm.vec3(5, 10, -5))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(2))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()

        elif randomchoice == 1:
            cylindermodel = glm.translate(glm.vec3(-5, 10, -5))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(2))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()

        elif randomchoice == 2:
            cylindermodel = glm.translate(glm.vec3(-5, 10, -5))
            cylindermodel = glm.rotate(cylindermodel, math.pi / 2, glm.vec3(0, 1, 0))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(2))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()

        elif randomchoice == 3:
            cylindermodel = glm.translate(glm.vec3(-5, 10, 5))
            cylindermodel = glm.rotate(cylindermodel, math.pi / 2, glm.vec3(0, 1, 0))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(2))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()

        elif randomchoice == 4:
            cylindermodel = glm.translate(glm.vec3(-5, 10, -5))
            cylindermodel = glm.rotate(cylindermodel, math.pi / 4, glm.vec3(0, 1, 0))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(3))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()

        elif randomchoice == 5:
            cylindermodel = glm.translate(glm.vec3(5, 10, -5))
            cylindermodel = glm.rotate(cylindermodel, 7 * math.pi / 4, glm.vec3(0, 1, 0))
            cylindermodel = glm.scale(cylindermodel, glm.vec3(3))
            self.LoadMatrices(cylindermodel)
            self.cylinder.draw()


