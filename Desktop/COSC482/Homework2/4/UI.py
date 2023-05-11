# COSC 482 Homework #2 - 4
#
# boxes screensaver!
#
# Kalyn Howes
# 2/28/22

import pygame
from pygame.locals import *
import datetime
from GraphicsEngine import *
import random


class UI():
    def __init__(self, GE):
        self.ge = GE
        pygame.key.set_repeat(500, 25)

    # Create a random box on each frame while the program is running.
    # The box width and height should be random between 0.2 and 0.6
    # Once the number of boxes exceeds 200 remove the first box from the list so that there are
    # always 200 boxes being drawn on the screen.
    def boxPerFrame(self):
        if len(self.ge.boxes) > 200:
            self.ge.deleteBox(self.ge.boxes[0]) # delete first box
        else:
            # add the box with a random width and height between 0.2-0.6
            w = 0.6 * random.random() + 0.2
            h = 0.6 * random.random() + 0.2
            center = [random.uniform(-1, 1), random.uniform(-1, 1)]
            self.ge.boxes.append(Box(center[0], center[1], w, h))

            # set random colors for new box
            r = random.random()
            g = random.random()
            b = random.random()
            # set color of last box added
            self.ge.boxes[len(self.ge.boxes) - 1].setColor([r, g, b, r, g, b, r, g, b, r, g, b])
            self.ge.boxColors.append([r, g, b, r, g, b, r, g, b, r, g, b])
            #print('Added random box.')

    # ---------------- HELPER FUNCTIONS -----------------------
    # check all boxes for current mouse position
    # if the current mouse position is not found - return false
    def checkAllBoxes(self, pos):
        ret = False
        for i in range(len(self.ge.boxes)):
            if self.ge.boxes[i].inBox(pos):
                ret = True
        return ret

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

        if event.type == MOUSEBUTTONDOWN:
            self.processMouseButtonDown(event)

        # processes the actual motion of the mouse
        if event.type == MOUSEMOTION:
            self.processMouseMotion(event)

    def processMouseButtonDown(self, event):
        buttons = pygame.mouse.get_pressed(5)
        pos = pygame.mouse.get_pos()
        screenPos = self.MouseToScreenConversion(pos)  # actual x,y coordinates
        key = pygame.key.get_pressed() # get key state

        # 3C: ctrl right-click adds a random box
        if (buttons[2]) and (key[K_LCTRL] or key[K_RCTRL]):
            if not self.checkAllBoxes(screenPos): # if there is not already a box there
                # add the box with a random width and height between 0.1-0.3
                w = 0.3 * random.random() + 0.1
                h = 0.3 * random.random() + 0.1
                self.ge.boxes.append(Box(screenPos[0], screenPos[1], w, h))

                # set random colors for new box
                r = random.random()
                g = random.random()
                b = random.random()
                # set color of last box added
                self.ge.boxes[len(self.ge.boxes) - 1].setColor([r, g, b, r, g, b, r, g, b, r, g, b])
                self.ge.boxColors.append([r, g, b, r, g, b, r, g, b, r, g, b])
                print('Added random box.')

            # 3C: if the ctrl key is pressed & you right-click on a box, it should delete that box
            else: # if there is a box, delete it
                for i in range(len(self.ge.boxes)):
                    boxHit = self.ge.boxes[i].inBox(screenPos)
                    if boxHit:
                        self.ge.deleteBox(screenPos)
                        print('BOX DELETED.')

        # 3H: Click of left button - calculate distance from center of box to the mouse & save in box (constant)
        if buttons[0]:
            for i in range(len(self.ge.boxes)):
                self.ge.boxes[i].updateDistance(screenPos)
                print('Left clicked on a box.')

        # 3E: highlight box in yellow when mouse is left-clicked with ctrl key down
        if (buttons[0]) and key[K_LCTRL] or key[K_RCTRL]:
            for i in range(len(self.ge.boxes)):  # needs to check all boxes
                boxHit = self.ge.boxes[i].inBox(screenPos)
                if boxHit:
                    self.ge.boxes[i].setColor([1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0])
                    print('Set current box to yellow & selected it.')
                    self.ge.selectedBoxes.append(self.ge.boxes[i]) # store in selected
                    self.ge.boxes[i].isSelected = 1

            # 3G: ctrl key down & left click outside any of the boxes - deselect
            if not self.checkAllBoxes(screenPos):
                for i in range(len(self.ge.boxes)):
                    self.ge.boxes[i].setColor(self.ge.boxColors[i])
                    print('Set current box to original color & deselected all.')
                    self.ge.boxes[i].isSelected = 0
                self.ge.selectedBoxes.clear()

    def processMouseMotion(self, event):
        buttons = pygame.mouse.get_pressed(5)
        pos = pygame.mouse.get_pos()
        screenPos = self.MouseToScreenConversion(pos)  # actual x,y coordinates

        rel = pygame.mouse.get_rel()
        moved = rel[0] != 0 or rel[1] != 0 # mouse moves boolean

        # 3D: highlight the box in red when the mouse is over the box and back when the mouse is not over the box
        for i in range(len(self.ge.boxes)): # needs to check all boxes
            boxHit = self.ge.boxes[i].inBox(screenPos)

            if boxHit: # mouse inside a box
                self.ge.boxes[i].setColor([1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0])
                print('Set current box to red.')

            elif not boxHit: # mouse outside any box - if box is selected it must STAY yellow
                if self.ge.boxes[i].isSelected: # the box is in the selected ones it reverts to yellow
                    self.ge.boxes[i].setColor([1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0])
                    print('Set current box to yellow (since it is selected).')

                else: # otherwise it reverts to its original
                    self.ge.boxes[i].setColor(self.ge.boxColors[i])
                    print('Set current box to original color.')

            # 3H: if the mouse is over the box then a left click and drag will move the box along with the mouse
            if boxHit:
                if buttons[0] and moved:
                    self.ge.boxes[i].setCenter(screenPos[0] - self.ge.boxes[i].xDistance,
                                          screenPos[1] - self.ge.boxes[i].yDistance)
                    print('One box is being dragged.')

            # 3J: WHEN SHIFT IS PRESSED, mouse over a selected box, click & drag will move all selected boxed
            key = pygame.key.get_pressed()
            if (key[K_LSHIFT] or key[K_RSHIFT]) and boxHit:
                if buttons[0] and moved:

                    for j in range(len(self.ge.selectedBoxes)): # for all selected boxes
                        self.ge.selectedBoxes[j].setCenter(screenPos[0] - self.ge.selectedBoxes[j].xDistance,
                                                   screenPos[1] - self.ge.selectedBoxes[j].yDistance)
                    print('Selected boxes are being dragged.')


    def processKeydown(self, event):
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

        # Clears all boxes from the screen
        if event.key == K_F8:
            for i in range(len(self.ge.boxes)):
                self.boxes.remove(self.boxes[i])
            print('Deleted all boxes.')

        # Get a screenshot and save to png file.
        if event.key == K_F12:
            path = datetime.datetime.now().strftime('ScreenShot_%Y-%m-%d_%H:%M:%S.%f.png')
            image = self.ge.getScreenImage()
            image.save(path)
            print('Screenshot Taken.')

    def processKeyStates(self):
        key = pygame.key.get_pressed()

        # 3I functions:
        if key[K_RALT] or key[K_LALT]:
            # Up: Increases the height and width of the box.
            if key[K_UP]:
                for i in range(len(self.ge.selectedBoxes)):
                    w = self.ge.selectedBoxes[i].getWidth()
                    w = w + 0.01
                    self.ge.selectedBoxes[i].setWidth(w)
                    h = self.ge.selectedBoxes[i].getHeight()
                    h = h + 0.01
                    self.ge.selectedBoxes[i].setHeight(h)
                print('Selected boxes height & width increased.')

            # Down: Decreases the height and width of the box.
            elif key[K_DOWN]:
                for i in range(len(self.ge.selectedBoxes)):
                    w = self.ge.selectedBoxes[i].getWidth()
                    w = w - 0.01
                    self.ge.selectedBoxes[i].setWidth(w)
                    h = self.ge.selectedBoxes[i].getHeight()
                    h = h - 0.01
                    self.ge.selectedBoxes[i].setHeight(h)
                print('Selected boxes height & width decreased.')

        elif key[K_LCTRL] or key[K_RCTRL]:  # Either control key down.
            # Increase the box width.
            if key[K_LEFT]:
                for i in range(len(self.ge.selectedBoxes)):
                    w = self.ge.selectedBoxes[i].getWidth()
                    w = w + 0.01
                    self.ge.selectedBoxes[i].setWidth(w)
                print('Selected boxes width increased.')

            # Decrease the box width.
            if key[K_RIGHT]:
                for i in range(len(self.ge.selectedBoxes)):
                    w = self.ge.selectedBoxes[i].getWidth()
                    w = w - 0.01
                    self.ge.selectedBoxes[i].setWidth(w)
                print('Selected boxes width decreased.')

            # Increase the box height.
            if key[K_UP]:
                for i in range(len(self.ge.selectedBoxes)):
                    h = self.ge.selectedBoxes[i].getHeight()
                    h = h + 0.01
                    self.ge.selectedBoxes[i].setHeight(h)
                print('Selected boxes height increased.')

            # Decrease the box height.
            if key[K_DOWN]:
                for i in range(len(self.ge.selectedBoxes)):
                    h = self.ge.selectedBoxes[i].getHeight()
                    h = h - 0.01
                    self.ge.selectedBoxes[i].setHeight(h)
                print('Selected boxes height decreased.')

            # 3F: ctrl A will select all the boxes (all turn yellow)
            if key[K_a]:
                for i in range(len(self.ge.boxes)):  # needs to check all boxes
                    self.ge.boxes[i].setColor([1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0])
                    self.ge.selectedBoxes.append(self.ge.boxes[i])
                    self.ge.boxes[i].isSelected = 1

                print('All boxes selected (yellow).')

            # 3F: ctrl Q will deselect all the boxes (return to original color)
            if key[K_q]:
                for i in range(len(self.ge.boxes)):
                    self.ge.boxes[i].setColor(self.ge.boxColors[i])
                    self.ge.boxes[i].isSelected = 0
                self.ge.selectedBoxes.clear() # reset selected boxes
                print('All boxes deselected (original color).')

        else: # more 3I functions
            # Move box up.
            if key[K_UP]:
                for i in range(len(self.ge.selectedBoxes)):
                    cx, cy = self.ge.selectedBoxes[i].getCenter()
                    cy = cy + 0.01
                    self.ge.selectedBoxes[i].setCenter(cx, cy)
                print('Selected boxes moved up.')

            # Move box down.
            if key[K_DOWN]:
                for i in range(len(self.ge.selectedBoxes)):
                    cx, cy = self.ge.selectedBoxes[i].getCenter()
                    cy = cy - 0.01
                    self.ge.selectedBoxes[i].setCenter(cx, cy)
                print('Selected boxes moved down.')

            # Move box left.
            if key[K_LEFT]:
                for i in range(len(self.ge.selectedBoxes)):
                    cx, cy = self.ge.selectedBoxes[i].getCenter()
                    cx = cx - 0.01
                    self.ge.selectedBoxes[i].setCenter(cx, cy)
                print('Selected boxes moved left.')

            # Move box right.
            if key[K_RIGHT]:
                for i in range(len(self.ge.selectedBoxes)):
                    cx, cy = self.ge.selectedBoxes[i].getCenter()
                    cx = cx + 0.01
                    self.ge.selectedBoxes[i].setCenter(cx, cy)
                print('Selected boxes moved right.')
