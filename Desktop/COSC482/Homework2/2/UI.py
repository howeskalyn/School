# COSC 482 Homework #2 - 2
#
# UI changes - mouse functionality.
#
# Kalyn Howes
# 2/28/22

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

    def processEvents(self, event):
        if event.type == KEYDOWN:
            self.processKeydown(event)

        if event.type == MOUSEBUTTONDOWN:
            self.processMouseButtonDown(event)

        # processes the actual motion of the mouse
        if event.type == MOUSEMOTION:
            self.processMouseMotion(event)

    # actually does something with the mouse motion
    def processMouseMotion(self, event):

        # Get the mouse states, buttons, position, and relative movement.
        buttons = pygame.mouse.get_pressed(5)
        pos = pygame.mouse.get_pos()  # need to get just the position of the mouse from the event
        rel = pygame.mouse.get_rel()
        # print(event)  # test printing - this position is in PIXELS
        screenPos = self.MouseToScreenConversion(pos) # actual x,y coordinates

        # Boolean for the mouse moved.
        moved = rel[0] != 0 or rel[1] != 0

        # highlight the box in red when the mouse is over the box and back when the mouse is not over the box
        boxHit = self.ge.box.inBox(screenPos)
        #print(boxHit)
        if boxHit == True:
            self.ge.box.setColor([1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0])
        elif boxHit == False:
            self.ge.box.setColor([1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1])

        # click and drag movement:
        # if the mouse is over the box then a left click and drag will move the box along with the mouse
        if boxHit == True:

            if buttons[0] and moved:
                #print('clicked & MOVED')
                #print(screenPos[0] - self.ge.box.xDistance)
                #print(screenPos[1] - self.ge.box.yDistance)
                self.ge.box.setCenter(screenPos[0] - self.ge.box.xDistance, screenPos[1] - self.ge.box.yDistance)

    def processMouseButtonDown(self, event):
        # Get the mouse states, buttons, position, and relative movement.
        buttons = pygame.mouse.get_pressed(5)
        pos = pygame.mouse.get_pos()  # need to get just the position of the mouse from the event
        screenPos = self.MouseToScreenConversion(pos)  # actual x,y coordinates

        # Click of left button - calculate distance from center of box to the mouse & save in box (constant)
        if buttons[0]:
            #print('clicked')
            self.ge.box.updateDistance(screenPos)

    # Gets the viewport dimensions and input mouse position to convert the mouse location
    # from pixel positions to world positions.
    def MouseToScreenConversion(self, mousePosition):
        x, y = mousePosition
        lx, ux, ly, uy = self.ge.getScreenBounds()
        ulx, ulr, w, h = self.ge.getViewport()
        screenPos = [x / w * (ux - lx) + lx, uy - y / h * (uy - ly)]
        return screenPos

    def processKeydown(self, event):
        if (event.mod & KMOD_CTRL) and (event.mod & KMOD_SHIFT):  # Control and shift down
            # Reset the box center.
            if event.key == K_f:
                self.ge.box.setCenter(0, 0)

        # if either alt key is pressed, B will turn the box solid blue, G will turn
        # the box solid green, W will turn the box solid white, and M will reset the box vertices to the
        # red/green/blue/white default vertex colors.
        elif event.mod & KMOD_ALT:  # Alt down
            if event.key == K_b:
                self.ge.box.setColor([0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1])
            elif event.key == K_g:
                self.ge.box.setColor([0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0])
            elif event.key == K_w:
                self.ge.box.setColor([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
            elif event.key == K_m:
                self.ge.box.setColor([1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1])

        else:  # No modifiers
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

    def processKeyStates(self):
        key = pygame.key.get_pressed()
        if key[K_LCTRL] or key[K_RCTRL]:  # Either control key down.
            # Increase the box width.
            if key[K_LEFT]:
                w = self.ge.box.getWidth()
                w = w + 0.01
                self.ge.box.setWidth(w)

            # Decrease the box width.
            if key[K_RIGHT]:
                w = self.ge.box.getWidth()
                w = w - 0.01
                self.ge.box.setWidth(w)

            # Increase the box height.
            if key[K_UP]:
                h = self.ge.box.getHeight()
                h = h + 0.01
                self.ge.box.setHeight(h)

            # Decrease the box height.
            if key[K_DOWN]:
                h = self.ge.box.getHeight()
                h = h - 0.01
                self.ge.box.setHeight(h)
        else:  # No modifiers
            # Move box up.
            if key[K_UP]:
                cx, cy = self.ge.box.getCenter()
                cy = cy + 0.01
                self.ge.box.setCenter(cx, cy)

            # Move box down.
            if key[K_DOWN]:
                cx, cy = self.ge.box.getCenter()
                cy = cy - 0.01
                self.ge.box.setCenter(cx, cy)

            # Move box left.
            if key[K_LEFT]:
                cx, cy = self.ge.box.getCenter()
                cx = cx - 0.01
                self.ge.box.setCenter(cx, cy)

            # Move box right.
            if key[K_RIGHT]:
                cx, cy = self.ge.box.getCenter()
                cx = cx + 0.01
                self.ge.box.setCenter(cx, cy)
