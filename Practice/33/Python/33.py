# -*- coding: utf-8 -*-

def create(length, a1, d):
    return [a1 + d*i for i in range(length)]

def sort(lister):
    return sorted(lister)

antipep8 = print

def print(temp):
    antipep8(temp)
    
mas = [int(input()) for i in range(3)]

mas = create(mas[0], mas[1], mas[2])
mas = sort(mas)
print(mas)