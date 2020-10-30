// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{ //ПЕРЕДЕЛАТЬ!!!!!!!!!
	import time
import itertools
n = int(input())
def count_sys(a, syst):
    res = ['']
    while a > 0:
        res.append(str(a % syst))
        a //= syst
    res.reverse()
    xres = list('0' for i in range((n - len(res)+1)))
    xres.extend(res)
    xres.pop()
    return ''.join(xres)
letts = [i for i in input()]
x = time.time()
letts_cop = set(letts)
array_opt = list(str(i) for i in range(n-1, 0, -1))
list_opt = []
if len(letts_cop) == n:
    print(' '.join([''.join(i) for i in itertools.permutations(r=n, iterable=''.join(letts))]))
else:
    for i in range(len(letts_cop) ** n):
        temp = count_sys(i, len(letts_cop))
        if set(letts[int(i)] for i in temp).intersection(letts_cop) == letts_cop:
            list_opt = [letts[int(i)] for i in temp]
            print(''.join(list_opt), end = ' ')
        if list_opt == array_opt:
            break
print(time.time() - x)
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
