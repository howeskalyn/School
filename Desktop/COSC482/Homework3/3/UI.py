# COSC 482 Homework #3 - 3
#
# The eyes will follow the mouse pointer around the window.
#
# Kalyn Howes
# 3/9/22

import pygame
from pygame.locals import *
import datetime
from GraphicsEngine import *
import random

class UI():
    def __init__(self, GE):
        self.ge = GE
        pygame.key.set_repeat(500, 25)

    # ---------------- HELPER FUNCTIONS -----------------------
    # convert from pixel positions to world positions.
    def MouseToScreenConversion(self, mousePosition):
        x, y = mousePosition
        lx, ux, ly, uy = self.ge.getScreenBounds()
        ulx, ulr, w, h = self.ge.getViewport()
        screenPos = [x / w * (ux - lx) + lx, uy - y / h * (uy - ly)]
        return screenPos

    # ------------- PROCESSING FUNCTIONS ------------------------
    def processEvents(self, event):
        if event.type == KEYDOWN:
            self.processKeydown(event)
        elif event.type == pygame.VIDEORESIZE:
            self.ge.setProjectionMatrix(event.size)

        # processes the actual motion of the mouse
        if event.type == MOUSEMOTION:
            self.processMouseMotion(event)

    def processMouseMotion(self, event):
        buttons = pygame.mouse.get_pressed(5)
        pos = pygame.mouse.get_pos()
        screenPos = self.MouseToScreenConversion(pos)  # actual x,y coordinates
        #print("MOUSE MOTION DETECTED: screenPos = ", screenPos)

        rel = pygame.mouse.get_rel()
        moved = rel[0] != 0 or rel[1] != 0  # mouse moves boolean

        # any mouse movement should update the center of the pupil
        self.ge.circleAttr[2].update(screenPos) # first 2 indices are the eyes
        self.ge.circleAttr[3].update(screenPos)


    # Escape: Ends the program.
    # •1: Sets the circles to render in outline mode.
    # •2: Sets the circles to render in filled mode.
    # •F1: Polygon fill mode.
    # •F2: Polygon line mode.
    # •F3: Polygon point mode.
    # •F4: Toggle between 60 FPS and unlimited. (in main)
    # •F12: Saves a screenshot of the graphics window to a png file.
    def processKeydown(self, event):
        # render circles in outline mode
        if event.key == K_1:

            for i in range(len(self.ge.circles)):
                self.ge.circles[i].setOutline()

            print('Mode: Line')

        # render circles in filled mode
        if event.key == K_2:
            for i in range(len(self.ge.circles)):
                self.ge.circles[i].setFill()

            print('Mode: Fill')

        # Set the rendering mode to fill.
        if event.key == K_F1:
            self.ge.setFill()
            print('Mode: Fill')

        # Set the rendering mode to line.
        if event.key == K_F2:
            self.ge.setLine()
            print('Mode: Line')

        # Set the rendering mode to point.
        if event.key == K_F3:
            self.ge.setPoint()
            print('Mode: Point')

        # Get a screenshot and save to png file.
        if event.key == K_F12:
            path = datetime.datetime.now().strftime('ScreenShot_%Y-%m-%d_%H-%M-%S.%f.png')
            image = self.ge.getScreenImage()
            image.save(path)
            print('Screenshot Taken.')

    def processKeyStates(self):
        key = pygame.key.get_pressed()
