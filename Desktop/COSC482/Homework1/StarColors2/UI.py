# COSC 482 Homework #1: 2-7
# Produces an n-point star where n is chosen by the keyboard (2-9) or increased/decreased by the arrow keys,
# and now lets the user change the color of the points.
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
                self.ge.loadStarData(numPoints, self.ge.color)

            # Increase number of points on star with up arrow key
            if event.key == K_UP:
                if self.ge.numPoints < 100:
                    self.ge.numPoints = self.ge.numPoints + 1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # Decrease number of points on star with down arrow key
            if event.key == K_DOWN:
                if self.ge.numPoints > 2:
                    self.ge.numPoints = self.ge.numPoints - 1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # If user presses the r key the amount of red will be increased by 0.01 until the value is 1
            if event.key == K_r:
                if self.ge.color[0] < 1:
                    self.ge.color[0] += 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # t is pressed the red will be decreased by 0.01 until the value is 0
            if event.key == K_t:
                if self.ge.color[0] > 0:
                    self.ge.color[0] -= 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # g will increase the green
            if event.key == K_g:
                if self.ge.color[1] < 1:
                    self.ge.color[1] += 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # h will decrease the green
            if event.key == K_h:
                if self.ge.color[1] > 0:
                    self.ge.color[1] -= 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # b will increase the blue
            if event.key == K_b:
                if self.ge.color[2] < 1:
                    self.ge.color[2] += 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)

            # n will decrease the blue
            if event.key == K_n:
                if self.ge.color[2] > 0:
                    self.ge.color[2] -= 0.1
                self.ge.loadStarData(self.ge.numPoints, self.ge.color)
