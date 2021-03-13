#include <iostream>
#include <algorithm>

int* create(const int& l, const int& a0, const int& d) {
	int* arr{ new int[l] };

	for (int i{ 0 }; i < l; i++) {
		arr[i] = a0 + d * i;
	}

	return arr;
}

void sort(const int& l, int*& arr) {
	for (int i{ 0 }; i < l; i++) {

		for (int j{ i }; j < l; j++) {
			if (arr[j] < arr[i]) {
				std::swap(arr[j], arr[i]);
			}
		}
	}

}

void print(const int& l, int*& arr) {
	std::cout << "[";

	for (int i{ 0 }; i < l; i++) {

		if (i == l - 1) {
			std::cout << arr[i];
		}

		else {
			std::cout << arr[i] << ", ";
		}
	}

	std::cout << "]\n";
}

int main(){
	int a, b, c;
	std::cin >> a >> b >> c;
	int * t = create(a, b, c);
	sort(a, t);
	print(a, t);
	delete [] t;
}
