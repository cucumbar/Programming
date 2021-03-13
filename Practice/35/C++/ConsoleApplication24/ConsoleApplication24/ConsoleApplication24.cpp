#include <iostream>

struct IntArray {
	int* data;
	int size;
};

extern int sized{ 0 };

void create(IntArray* arr, int size) {
	int* dat = new int[size];
	for (int i{ 0 }; i < size; i++) {
		dat[i] = 1 + 1 * i;
	}

	sized = size;
	arr->data = dat;

	delete[] dat;
	dat = nullptr;
}

void create(IntArray& arr, int size) {
	int* dat = new int[size];
	for (int i{ 0 }; i < size; i++) {
		dat[i] = 1 + 1 * i;
	}

	sized = size;
	arr.data = dat;

	delete[] dat;
	dat = nullptr;
}

int get(IntArray* arr, int index) {
	try {
		return arr->data[index];
	}

	catch(std::exception e){
		std::cout << "Vyhod za granici massiva";
		exit(12345);
	}
}

int get(IntArray& arr, int index) {
	try {
		return arr.data[index];
	}

	catch (std::exception& e) {
		std::cout << "Vyhod za granici massiva";
		exit(12345);
	}
}

void set(IntArray* arr, int index, int value) {
	try {
		arr->data[index] = value;
	}
	catch (std::exception& e) {
		std::cout << "Vyhod za granici massiva";
		exit(12345);
	}
}

void set(IntArray& arr, int index, int value) {
	try {
		arr.data[index] = value;
	}

	catch (std::exception& e) {
		std::cout << "Vyhod za granici massiva";
		exit(12345);
	}
}

void print(IntArray* arr) {
	std::cout << "[";

	for (int i{ 0 }; i < sized; i++) {

		if (i == sized - 1) {
			std::cout << arr->data[i];
		}
		
		else {
			std::cout << arr->data[i] << ", ";
		}
	}

	std::cout << "]\n";
}

void print(IntArray& arr) {
	std::cout << "[";

	for (int i{ 0 }; i < sized; i++) {

		if (i == sized - 1) {
			std::cout << arr.data[i];
		}

		else {
			std::cout << arr.data[i] << ", ";
		}
	}

	std::cout << "]\n";
}

void resize(IntArray* arr, int newSize) {
	int* dat = new int[newSize];

	if (newSize >= sized) {

		for (int i{ 0 }; i < sized; i++) {
			dat[i] = arr->data[i];
		}

		for (int i{ sized }; i < newSize; i++) {
			dat[i] = 0;
		}
	}

	else {
		for (int i{ 0 }; i < newSize; i++) {
			dat[i] = arr->data[i];
		}
	}

	arr->data = dat;

	delete[] dat;
	dat = nullptr;
}

void resize(IntArray& arr, int newSize) {
	int* dat = new int[newSize];

	if (newSize >= sized) {

		for (int i{ 0 }; i < sized; i++) {
			dat[i] = arr.data[i];
		}

		for (int i{ sized }; i < newSize; i++) {
			dat[i] = 0;
		}
	}

	else {
		for (int i{ 0 }; i < newSize; i++) {
			dat[i] = arr.data[i];
		}
	}

	arr.data = dat;

	delete[] dat;
	dat = nullptr;
}

void destroy(IntArray* arr) {
	if (arr->data == nullptr) {
		return;
	}

	else if (*arr->data) {
		delete [] arr->data;
		arr = nullptr;
		arr->size = 0;
	}
}

void destroy(IntArray& arr) {
	if (arr.data == nullptr) {
		return;
	}

	else if (*arr.data) {
		delete [] arr.data;
		arr.size = 0;
	}
}


int main(){
	IntArray res;
	create(res, 30);
	print(res);
	resize(res, 50);
	print(res);
	resize(res, 10);
	print(res);
	destroy(res);
	return 0;
}