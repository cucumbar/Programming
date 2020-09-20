# -*- coding: utf-8 -*-
import random
print('yaponskaya бондицкая игра "чет-нечет(cho-han)"')
igroki = {}
rez = []
chohan = ['Чёт!', 'Нечёт!']
imena = ['Цукихико', 'Ямамото', 'Миямото', 'Чжэнь', 'Уася', 'Усемутаки', 'Коджиро', 'Матахати', 'Пек-Кхек', 'Рюгаготоку']
prilag = ['Пидрила ', 'Лох ', 'Алкоголик ', 'Тупой ', 'Хитрый ', 'Крутой ', 'Богатый ', 'Бедный ', 'Ссучившийся ']
for i in range(7):
    igroki[prilag[random.randrange(0, len(prilag))] + imena[random.randrange(0, len(imena))]] = 0
print(igroki)
o = input('Играть буш? ')
while o == 'Да':
    print('Бросаем кости...\nБросок!')
    for i in igroki.keys():
        print(i+': '+chohan[random.randrange(0, 2)])
    t = input('Ты: ')
    for i in range(2):
        rez.append(random.randrange(1, 7))
        print(rez[i], end = ' ')
    if sum(rez) % 2 == 0:
        print('\nПобедил чёт!')
    else:
        print('Победил нечёт!')
    o = input('Играть дальше буш? ')
    if o != 'Да':
        print('Приходи ещё!')
    rez = []