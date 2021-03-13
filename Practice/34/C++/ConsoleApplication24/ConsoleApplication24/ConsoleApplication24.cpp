#include <iostream>

int* create(const int& l, const int& a0, const int& d) {
	int* arr{ new int[l] };

	for (int i{ 0 }; i < l; i++) {
		arr[i] = a0 + d * i;
	}

	return arr;
}

void create(int** arr, int l, int a0, int d){
	*arr = create(l, a0, d);
}

void destroy(int** arr){
	if (arr == nullptr){
		return;
	}

	else if (*arr){
		delete[] *arr;
		*arr = nullptr;
	}
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
	int len, first, move;

	std::cin >> len >> first >> move;
	int* arr;

	create(&arr, len, first, move);
	sort(len, arr);
	print(len, arr);
	destroy(&arr);

	return 0;
}