# -*- coding: utf-8 -*-
from random import randrange
def game():
    print('Здравствуйте. Угадайте число от 1 до 100')
    x = randrange(1, 101)
    flag = False
    for i in range(5):
        y = int(input())
        if i <= 4:
            if y < x:
                print("Загаданное число больше")
            elif y > x:
                print("Загаданное число меньше")
            else:
                print("Поздравляю! Вы угадали")
                flag = True
                break
    if flag == False:
        print(f"Вы проиграли. Было загадано: {x}")
    if int(input("Хотите начать сначала? (1 - ДА )" + '\n')) == 1:
        game()
game()