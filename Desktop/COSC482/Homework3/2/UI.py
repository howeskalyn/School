# COSC 482 Homework #3 - 2
#
# The Stars screen saver program that places a random star on the screen every tenth of a second. Each star
# has a random starting position on the screen, random number of points from 5 to 15, random center color,
# and random point color. The stars are also given a random velocity and rotational velocity. When the star
# is created it will animate across the screen and eventually off the screen.
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

    # Escape: Ends the program.
    # •1: Sets the stars to render in outline mode.
    # •2: Sets the stars to render in filled mode.
    # •F1: Polygon fill mode.
    # •F2: Polygon line mode.
    # •F3: Polygon point mode.
    # •F4: Toggle between 60 FPS and unlimited. (in main)
    # •F12: Saves a screenshot of the graphics window to a png file.
    def processKeydown(self, event):
        # render stars in outline mode
        if event.key == K_1:

            for i in range(len(self.ge.stars)):
                self.ge.stars[i].setOutline()

            print('Mode: Line')

        # render stars in filled mode
        if event.key == K_2:
            for i in range(len(self.ge.stars)):
                self.ge.stars[i].setFill()

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
