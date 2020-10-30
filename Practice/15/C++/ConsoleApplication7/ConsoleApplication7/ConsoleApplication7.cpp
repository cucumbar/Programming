﻿// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <ctime>
int main() {
	srand(time(0));
	int y, x;
	std::string s;
	bool flag{false};
    std::cout << "Здравствуйте. Угадайте число от 1 до 100\n";
    x = rand() % (101);
    for (int i = 1; i < 5; i++){
        std::cin >> y;
        if (i <= 4){
            if (y < x){
                std::cout << "Загаданное число больше\n";
            }
            else if (y > x){
                std::cout << "Загаданное число меньше\n";
            }
            else{
                std::cout << "Поздравляю! Вы угадали\n";
                flag = true;
                break;
            }
        }
    }
    if (flag == false){
        std::cout << "Вы проиграли. Было загадано: \n" << x;
    }
    std::cout << "\nХотите начать сначала? (1 - ДА )\n";
    std::cin >> x;
    if (x == 1){
        main();
    }
	return 0;
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
