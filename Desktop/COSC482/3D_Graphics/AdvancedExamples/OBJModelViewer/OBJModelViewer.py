#! /usr/bin/env python3
#
# This program is a Wavefront OBJ file viewer.
#
# User Options - file loading by drag and drop.
#
# Drag and drop a Wavefront OBJ file to the graphic window to load the file into the program.
# The file must have a .obj extension on it or it will not be loaded.
#
# User Options - Keys
#
# - Escape:  Ends the program.
# - C: Toggles between the two cameras.
# - O: Toggles between outline and fill mode for the box and cube objects.
# - L: Toggles the drawing of the axes.
# - K: Toggles the drawing of the light positions.
# - F1: Draws in fill mode.
# - F2: Draws in line mode.
# - F3: Draws in point mode.
# - F4: Toggles between 60 FPS and unlimited FPS.
# - F12: Saves a screen shot of the graphics window to a png file.
# - 1: Background to black.
# - 2: Background to white.
# - 3: Background to red.
# - 4: Background to green.
# - 5: Background to blue.
# - 6: Background to .5 grayscale.
# - 7: Background to .7 grayscale.
# - 8: Background to .8 grayscale.
# - 9: Background to .9 grayscale.
# - 0: Background to cubemap.
#
#
# If the spherical camera is currently selected,
#
# If no modifier keys are pressed:
#
# - Left: Increases the camera's theta value.
# - Right: Decreases the camera's theta value.
# - Up: Increases the camera's psi value.
# - Down: Decreases the camera's psi value.
#
# If the control or Z key is down:
#
# - Up: Decreases the camera's radius.
# - Down: Increases the camera's radius.
#
# If the yaw-pitch-roll camera is currently selected,
#
# If no modifier keys are pressed:
#
# - Left: Increases the yaw.
# - Right: Decreases the yaw.
# - Up: Increases the pitch.
# - Down: Decreases the pitch.
#
# If the control or Z key is down:
#
# - Left: Increases the roll.
# - Right: Decreases the roll.
# - Up: Moves the camera forward.
# - Down: Moves the camera backward.
#
# If the shift or S key is down:
#
# - Left: Moves the camera left.
# - Right: Moves the camera right.
# - Up: Moves the camera up.
# - Down: Moves the camera down.
#
# User Options - Mouse
#
# If the spherical camera is currently selected,
#
# If no modifier keys are pressed and the left mouse button is down a movement will
# alter the theta and psi angles of the spherical camera to give the impression
# of the mouse grabbing and moving the coordinate system.
#
# If the control key is down and the left mouse button is down then the camera will
# be moved in and out from the origin by the vertical movement of the mouse.
#
# If the wheel is moved then the camera will be moved in and out from the origin by
# the amount of the wheel movement.
#
# If the yaw-pitch-roll camera is currently selected,
#
# If no modifier keys are pressed and the left mouse button is down a movement will
# alter the yaw and pitch angles of the camera.
#
# If the control key is down and the left mouse button is down then the camera will
# be moved forward and backward by the vertical movement of the mouse.
#
# If the shift key is down and the left mouse button is down then the camera will
# be moved right and left as well as up and down.
#
# If the shift and control keys are down and the left mouse button is down then the
# camera will roll.
#
# If the wheel is moved then the camera will be moved foward and backward by
# the amount of the wheel movement.
#
# Don Spickler
# 1/6/2022

import pygame
from pygame.locals import *
import time
from OpenGL.GL import *
from GraphicsEngine import *
from UI import *

# Program setup information
ProgramName = "Wavefront OBJ Model Viewer"
maxfps = 60
minMajor = 3
minMinor = 3
Width = 800
Height = 600

# Shut down pygame and end the program.
def exitProgram():
    pygame.quit()
    exit()

# Test card supported version with desired version for the program.
def getOGLVersionAcceptable():
    versionok = True
    major = glGetIntegerv(GL_MAJOR_VERSION)
    minor = glGetIntegerv(GL_MINOR_VERSION)
    if (major < minMajor):
        versionok = False
    elif (major == minMajor and minor < minMinor):
        versionok = False
    return versionok

if __name__ == '__main__':
    pygame.init()

    # Add a user-defined event to update the PFS in the titlebar.
    UPDATE_FPS = USEREVENT + 1
    pygame.time.set_timer(UPDATE_FPS, 1000)

    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK,
                                    pygame.GL_CONTEXT_PROFILE_CORE)
    pygame.display.gl_set_attribute(pygame.GL_MULTISAMPLESAMPLES, 4)

    pygame.display.set_mode((Width, Height), DOUBLEBUF | OPENGL | RESIZABLE | HWSURFACE)
    pygame.display.set_caption(ProgramName)

    # Check to see if hardware supports desired version of OpenGL.
    if not getOGLVersionAcceptable():
        print("Hardware does not support required OpenGL version ", str(minMajor) + "." + str(minMinor))
        print("Exiting")
        exitProgram()

    # Create the GraphicsEngine and the User Interface objects.
    try:
        ge = GraphicsEngine()
        ui = UI(ge)
    except Exception as err:
        exitProgram()

    # Set up clock and frame count for FPS calculation.
    clock = pygame.time.Clock()
    starttime = time.time()
    frames = 0

    # Start the pygame event loop.
    while True:
        clock.tick(maxfps)
        frames += 1

        for event in pygame.event.get():
            # X or escape to close the program.
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                exitProgram()
            # F4 to switch FPS cap between 60 and unlimited.
            elif event.type == KEYDOWN and event.key == K_F4:
                if maxfps == 0:
                    maxfps = 60
                else:
                    maxfps = 0
            # User defined event to update FPS.
            elif event.type == UPDATE_FPS:
                now = time.time()
                fps = frames / (now - starttime)
                pygame.display.set_caption(ProgramName + "    FPS: " + str("%.2f" % fps))
                frames = 0
                starttime = now
            # Process all other events in the UI object.
            else:
                ui.processEvents(event)

        # Process Key states
        ui.processKeyStates()

        # Have graphics engine update the image.
        ge.update()

        # Swap the display buffers.
        pygame.display.flip()
