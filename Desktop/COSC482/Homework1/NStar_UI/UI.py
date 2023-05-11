# COSC 482 Homework #1: 2-4
# Produces an n-point star where n is chosen by the keyboard (2-9).
# Kalyn Howes
# 2.21.22

import pygame
from pygame.locals import *
import datetime
from GraphicsEngine import *

class UI():
    # Constructor, links the graphics engine to the user interface for easy
    # one-way communication from the UI to the GE.
    def __init__(self, GE):
        self.ge = GE
        # Set the initial repeat rate time and repeat speed.
        pygame.key.set_repeat(500, 25)

    def processEvent(self, event):
        # Process key pressed events.
        if event.type == KEYDOWN:
            # Set the rendering mode to fill.
            if event.key == K_F1:
                self.ge.setFill()

            # Set the rendering mode to line.
            if event.key == K_F2:
                self.ge.setLine()

            # Set the rendering mode to point.
            if event.key == K_F3:
                self.ge.setPoint()

            # Get a screen shot and save to png file.
            if event.key == K_F12:
                path = datetime.datetime.now().strftime('ScreenShot_%Y-%m-%d_%H:%M:%S.%f.png')
                image = self.ge.getScreenImage()
                image.save(path)

            # Reset the display mode.
            if event.key == K_r:
                pygame.display.set_mode((800, 600), DOUBLEBUF | OPENGL | RESIZABLE | HWSURFACE)

            # Change number of points on star using number keys 2-9
            if event.key in [K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9]:
                print('Key Pressed: ', event.key)
                numPoints = event.key - K_0
                print(f'Number of points {numPoints} = {event.key} - {K_0} ')
                self.ge.loadStarData(numPoints)
