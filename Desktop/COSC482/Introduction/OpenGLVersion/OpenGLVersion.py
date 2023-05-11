#! /usr/bin/env python3
#
# Simple program to create an OpenGL Context through PyGame and extract
# the max version of OpenGL supported by the graphics card and drivers
# as well as the type of card and the vender of the card.
#
# Don Spickler
# 11/20/2021

import pygame
from pygame.locals import *
import OpenGL.GL as ogl

if __name__ == '__main__':
# Initialize pygame.
    pygame.init()

# Set OpenGL attributes, version 3.3 and core profile.  The creation
# of the context will adjust the version to that supported by the card.
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK,
                                    pygame.GL_CONTEXT_PROFILE_CORE)
    pygame.display.set_mode([100, 100], OPENGL)

# Get card information and display in console.
    print()
    print("Version  = ", ogl.glGetString(ogl.GL_VERSION).decode('utf-8'))
    print("Vender   = ", ogl.glGetString(ogl.GL_VENDOR).decode('utf-8'))
    print("Renderer = ", ogl.glGetString(ogl.GL_RENDERER).decode('utf-8'))
