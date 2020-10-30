// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
	class alco:
    def __init__(self, name, price, V):
        self.price = int(price)
        self.name = name
        self.V = int(V)
        self.quantity = int(V) / int(price)
Si_money = int(input())
menu = []
res = {}
Money_dos = False
money = [Si_money]
probuhano = 0
for i in range(int(input())):
    a, b, c = input().split()
    menu.append(alco(a, b, c))
    if int(b) <= Si_money:
        Money_dos = True
def alcomarket(x):
    mmax = 0
    flag = False
    for i in x:
        if i.quantity > mmax:
            mmax = i.quantity
            temp = i
    products = money[0] // temp.price
    money[0] = money[0] % temp.price
    res[temp.name] = products, temp.V
    for i in x:
        if i.price <= money[0]:
            flag = True
    if flag == True:
        x.pop(x.index(temp))
        alcomarket(x)
if Money_dos == False:
    print(-1)
else:
    alcomarket(menu)
    for i, j in res.items():
        if j[0] != 0:
            print(i, j[0])
            probuhano += j[0] * j[1]
    print(probuhano)
    print(''.join(map(str, money)))
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
