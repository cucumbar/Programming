a, b, c = map(int, [input(), input(), input()])
D = b ** 2 - 4 * a * c
a = 2 * a
if a == 0 and b == 0 and c == 0:
    print('x = любое')
elif a == 0 and b == 0 and c!= 0:
    print(c, '=/= 0, ошибка')
elif D > 0 and a != 0:
    print('x1 =', int(-b / a + D ** 0.5 / a), 'x2 =', int(-b / a - D ** 0.5 / a))
elif D == 0 and a != 0:
    print('x =', int(-b / a + D ** 0.5 / a))
elif a == 0:
    print('x =', int(-c / b))
else:
    print('Комплексное число')