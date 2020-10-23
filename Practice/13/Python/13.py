# -*- coding: utf-8 -*-
def IsPrime(a):
    for i in range(2, a // 2 + 2):
        if a == 2 or a == 3:
            print('Простое')
            return
        elif a % i == 0:
            print('Составное')
            return
        elif i == a // 2:
            print('Простое')
IsPrime(int(input()))