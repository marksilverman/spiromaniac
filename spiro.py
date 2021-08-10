#!/home/msilverm/bin/python3

from graphics import *
from random import *
import time
from math import sin,cos,pi
import sys

really_show = False

def show(msg):
    if really_show:
        print(msg)

r = randint(1, 254)
g = randint(1, 254)
b = randint(1, 254)
color1 = color_rgb(r, g, b)
r += 20
g += 20
b += 20
if r > 255: r -= 255
if g > 255: g -= 255
if b > 255: b -= 255
color2 = color_rgb(r, g, b)
width = 30

def draw(p1, p2):
    l = Line(p1, p2)
    l.setFill(color1)
    # l.setOutline(color2)
    l.setWidth(2)
    l.draw(win)

w = 800
h = 800
x0 = w//2
y0 = h//2

factor = 60
radius1 = 5 * factor
radius2 = 2 * factor
radius = radius1 - radius2
height = 0.5 * factor
resolution = 50

addr = 1
addg = 1
addb = 1

while True:
    win = GraphWin('lines', w, h)
    win.setCoords(0, 0, win.width, win.height)
    win.setBackground(color2)

    starting_x = None
    starting_y = None
    oldx = x0
    oldy = y0

    p1 = None
    max_big_angle = int(round(resolution * 10 * 2 * pi, 0))
    show(f"max_big_angle={max_big_angle}")
    for big_angle in range(0, max_big_angle):
        angle = big_angle / resolution
        show(f"big_angle={big_angle}")
        show(f"angle={angle}")
        x = x0
        y = y0
        x += radius * cos(angle) + height * cos(angle * radius / radius2)
        y += radius * sin(angle) - height * sin(angle * radius / radius2)
        x = int(round(x, 0))
        y = int(round(y, 0))

        p2 = Point(x, y)
        show(f"x={x}, y={y}")

        if p1:
            draw(p1, p2)
            if big_angle > 10 and x == starting_x and y == starting_y:
                show(f"done; big_angle={big_angle}")
                break
        else:
            starting_x = int(round(x, 0))
            starting_y = int(round(y, 0))
            show(f"starting_x={starting_x}, starting_y={starting_y}")

        p1 = p2
        r += addr
        g += addg
        b += addb
        if r == 255 or r == 0: addr *= -1
        if g == 255 or g == 0: addg *= -1
        if b == 255 or b == 0: addb *= -1
        #print(f"r={r}, g={g}, b={b}")
        color1 = color_rgb(r, g, b)
        oldx = x
        oldy = y
            
    height += 0.5 * factor

    win.getMouse()
    win.close()

