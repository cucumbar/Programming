# This Python file uses the following encoding: utf-8
import math
import copy


cordsys = ['Cartesian', 'Polar']

class Point:
    def __init__(self, a1 = 0, a2 = 0, coordinates_system = 'Cartesian'):
        if type(a1) == str:
            a1.replace(',', ' ')
            a1.replace('(', '')
            a1.replace(')', '')
            self.x = float( a1.split()[0] )
            self.y = float( a1.split()[1] )
        else:
            if (coordinates_system == 'Cartesian'):
                self.x = a1
                self.y = a2
            else:
                self.x = math.cos(a2) * a1
                self.y = math.sin(a2) * a1

    def __eq__(self, other):
        return (abs(self.x - other.x) < 1e-10) and (abs(self.y - other.y) < 1e-10)

    def __ne__(self, other):
        return not(self == other)

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_r(self):
        return math.hypot(self.x, self.y)

    def get_phi(self):
        return math.atan2(self.y, self.x)

    def set_x(self, x):
        self.x = x

    def set_y(self, y):
        self.y = y

    def set_r(self, r):
        phi = self.get_phi()

        self.x = math.cos(phi) * r
        self.y = math.sin(phi) * r

    def set_phi(self, phi):
        r = self.get_r()

        self.x = math.cos(phi) * r
        self.y = math.sin(phi) * r

    def __repr__(self):
        return 'Point({1},{2})'.format(self.x, self.y)

    def __str__(self):
        return '({1},{2})'.format(self.x, self.y)

with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]

simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180*math.pi/180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')
