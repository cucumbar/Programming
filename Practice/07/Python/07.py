try:
    x = input()
    if x == '1':
        a, b, c = map(int, [input(), input(), input()])
        p = sum([a, b, c]) / 2
        print("S = " + str(sum([p * (p - a) * (p - b) * (p - c)]) ** 0.5))
    elif x == '2':
        a, b, c = list(map(int, input().split())), list(map(int, input().split())), list(map(int, input().split()))
        print("S = " + str(abs(sum([(b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1])]) / 2)))
    elif int(x) >= 3 and int(x) <= 1000:
        print('Ошибочный ввод')
except ValueError:
    print('Нельзя так писать.')
