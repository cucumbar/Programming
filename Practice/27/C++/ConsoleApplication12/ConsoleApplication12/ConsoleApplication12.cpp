// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

void Sort(std::vector<int> data, int lenD)
{
	int j = 0;
	int tmp = 0;

	for (int i = 0; i < lenD; i++) {
		j = i;
		for (int k = i; k < lenD; k++) {
			if (data[j] > data[k]) {
				j = k;
			}
		}

		tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}

int max(std::vector<int> mas)
{
	int ans = mas[0];
	for (int i{ 0 }; i < mas.size(); i++) {
		if (ans < mas[i]){
			ans = mas[i];
		}
	}
	return ans;
}

std::vector<int> Srez(std::vector<int> arr, int x, int y, int z = 1) 
{
	std::vector<int> ans;
		for (int i = y; i >= x; i -= z) {
			ans.push_back(arr[i]);
		}
		return ans;
}

int main()
{
	int n, schet, j{ 0 };
	std::vector<std::vector<int>> a, a_min, res;

	std::cin >> n;

	for (int i{ 0 }; i < n; i++) { //счет массива
		std::cin >> schet;
		a[0].push_back(schet);
	}

	while (j < n){
		j++;

		if (j < 5) {
			res.push_back(Srez(a[0], 0, j));
		}

		else if (j == 5) {
			res.push_back(Srez(a[0], 0, j));
			a_min.push_back(Srez(a[0], 0, j));
		}

		else {
			if (a[0][j - 1] < max(a_min[0])) {
				int i = a_min[0][0];
				while (i != (max(a_min[0]))) {
					i++;
				}
				a_min[0][i] = a[0][j - 1];
			}
			res.push_back(a_min[0]);
		}
			
	}

	for (int i{ 0 }; i < res.size(); i++) {
		for (int j{ 0 }; j < res[i].size(); j++) {
			std::cout << res[i][j] << ' ';
		}
		std::cout << '\n';
	}
	return 0;
}


