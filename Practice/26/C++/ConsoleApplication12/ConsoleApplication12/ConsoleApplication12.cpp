// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>

int real_sort(std::vector<int> arr, int size) {
	while (--size > 0)
		if (arr[size - 1] > arr[size])
			return 0;
	return 1;
}

std::vector<int> Bozosort(std::vector<int> mas) {
	const int len = mas.size();
	while (!real_sort(mas, len)) {

		std::swap(mas[std::rand() % len], mas[std::rand() % len]);
		for (int j{ 1 }; j < len; j++) {
			std::cout << mas[j] << ' ';
		}
		std::cout << '\n';
	}
	return mas;
}

int main()
{
	std::vector<int> test1;
	int a;
	for (int i{ 1 }; i < 4; i++) {
		std::cin >> a;
		test1.push_back(a);
	}
	std::cout << '\n';
	test1 = Bozosort(test1);
	for (int i{ 1 }; i < 4; i++) {
		std::cout << test1[i] << ' ';
	}
	for (int i{ 1 }; i < 4; i++) {
		std::cin >> a;
		test1.push_back(a);
	}
	std::cout << '\n';
	test1 = Bozosort(test1);
	for (int i{ 1 }; i < 4; i++) {
		std::cout << test1[i] << ' ';
	}
	return 0;
}