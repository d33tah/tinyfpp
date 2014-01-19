#!/usr/bin/python

import json
import sys

class Point:
    def __init__(self,x,y,z):
        self.x, self.y, self.z = x,y,z
    def __str__(self):
        return ( "%f %f %f 0.0 0.0" % (self.x, self.y, self.z) )

f = open(sys.argv[1],'r')
raw = f.read()
tree = json.loads(raw)

points = []
for i in range(int(len(tree['vertices'])/3.0)):
    x = tree['vertices'][i*3+0]
    y = tree['vertices'][i*3+1]
    z = tree['vertices'][i*3+2]
    points += [Point(x,y,z)]

for i in range(int(len(tree['faces'])/8.0)):
    x_i = tree['faces'][i*8+1]
    y_i = tree['faces'][i*8+2]
    z_i = tree['faces'][i*8+3]
    x = points[x_i]
    y = points[y_i]
    z = points[z_i]
    print "%s\n%s\n%s\n" % (x,y,z)
