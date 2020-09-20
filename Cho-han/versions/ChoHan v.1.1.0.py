# -*- coding: utf-8 -*-
import random
print('yaponskaya бондицкая игра "чет-нечет(cho-han)"\nВот тибе 500 ен выиграй всех')
igroki = {}
rez = []
dengi = 500
delezh = 0
pobed = 0
t = []
chohan = ['Чёт!', 'Нечёт!']
imena = ['Цукихико', 'Ямамото', 'Миямото', 'Чжэнь', 'Уася', 'Усемутаки', 'Коджиро', 'Матахати', 'Пек-Кхек', 'Рюгаготоку']
prilag = ['Пидрила ', 'Чмо ', 'Шулер ', 'Лох ', 'Алкоголик ', 'Тупой ', 'Хитрый ', 'Крутой ', 'Богатый ', 'Бедный ', 'Ссучившийся ']
for i in range(7):
    igroki[prilag[random.randrange(0, len(prilag))] + imena[random.randrange(0, len(imena))]] = (random.randrange(100, 1000, 100), '', 0)
print(igroki.items())
o = str(input('Играть буш? ').upper()).strip()
while o == 'ДА':
    print('Бросаем кости...\nБросок!')
    for i in igroki.keys():
        igroki[i] = (igroki[i][0], str(chohan[random.randrange(2)]), igroki[i][0] // random.randrange(3, 10))
        print(i + ': ' + igroki[i][1], igroki[i][2])
    t += str(input('Ты: ').lower()).split()
    for i in range(2):
        rez.append(random.randrange(1, 7))
        print(rez[i], end = ' ')
    if sum(rez) % 2 == 0:
        print('\nПобедил чёт!')
        for i in igroki.keys():
            if igroki[i][1] != 'Чёт!':
                delezh += igroki[i][2]
                igroki[i] = (igroki[i][0]-igroki[i][2], '', 0)
            else:
                pobed += 1
        if t[0] != 'чет' or t[0] != 'чет!' or t[0] != 'чёт!' or t[0] != 'чёт':
            dengi -= int(t[1])
            delezh += int(t[1])
            for i in igroki.keys():
                if igroki[i][1] == 'Чёт!':
                    igroki[i][0] = delezh // pobed
        if t[0] == 'чет' or t[0] == 'чет!' or t[0] == 'чёт!' or t[0] == 'чёт':
            pobed += 1
            dengi += delezh // pobed
            for i in igroki.keys():
                if igroki[i][1] == 'Чёт!':
                    igroki[i][0] = delezh // pobed
    else:
        print('Победил нечёт!')
        for i in igroki.keys():
            if igroki[i][1] != 'Нечёт!':
                delezh += igroki[i][2]
                igroki[i] = (igroki[i][0]-igroki[i][2], '', 0)
            else:
                pobed += 1
        if t[0] != 'нечет' or t[0] != 'нечет!' or t[0] != 'нечёт!' or t[0] != 'нечёт':
            dengi -= int(t[1])
            delezh += int(t[1])
            for i in igroki.keys():
                if igroki[i][1] == 'Нечёт!':
                    igroki[i][0] = delezh // pobed #туплы не меняются, исправить
        if t[0] == 'нечет' or t[0] == 'нечет!' or t[0] == 'нечёт!' or t[0] == 'нечёт':
            pobed += 1
            dengi += delezh // pobed
            for i in igroki.keys():
                if igroki[i][1] == 'Нечёт!':
                    igroki[i][0] = delezh // pobed
    o = str(input('Играть дальше буш? ').upper()).strip()
    if o != 'ДА':
        print('Приходи ещё!')
    rez = []
    #1. пусть будет класс вместо словаря кортежей? 2. неравномерный дележ бабок проигравших 3. комбинации