// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{ //ПЕРЕВЕСТИ НАДО
	import copy
Siegesmund_roullete = int(input())
popular_numbers = {1 : [Siegesmund_roullete]}
popular_numbers1 = copy.deepcopy(popular_numbers)
red = (1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36)
black = [i for i in range(1,37) if i not in red]
redblack_numbers = [1 if Siegesmund_roullete in red else 0, 1 if Siegesmund_roullete in black else 0]
unused_numbers = [i for i in range(37) if i != Siegesmund_roullete]
print(' '.join(map(str, popular_numbers[max(popular_numbers.keys())])))  #тут некрасиво получилось но переделывать не буду уж как есть
print(' '.join(map(str, unused_numbers)))
print(' '.join(map(str, redblack_numbers)))
while True:
    Siegesmund_roullete = int(input())
    if Siegesmund_roullete < 0:
        break
    flag = False
    for i in popular_numbers.keys():
        if Siegesmund_roullete in popular_numbers1[i]:
            popular_numbers1[i].pop(popular_numbers1[i].index(Siegesmund_roullete))
            try:
                popular_numbers1[i + 1].append(Siegesmund_roullete)
            except KeyError:
                popular_numbers1[i + 1] = [Siegesmund_roullete]
            flag = True
            break
    popular_numbers = copy.deepcopy(popular_numbers1)
    if flag == False:
        popular_numbers1[1].append(Siegesmund_roullete)
    if Siegesmund_roullete in unused_numbers:
        unused_numbers.pop(unused_numbers.index(Siegesmund_roullete))
    if Siegesmund_roullete in red:
        redblack_numbers[0] += 1
    elif Siegesmund_roullete in black:
        redblack_numbers[1] += 1
    print(' '.join(map(str, popular_numbers1[max(popular_numbers1.keys())])))
    print(' '.join(map(str, unused_numbers)))
    print(' '.join(map(str, redblack_numbers)))
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
