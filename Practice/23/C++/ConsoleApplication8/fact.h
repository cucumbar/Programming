#pragma once
int fact(int a){
	int res = 1;
	for (int i{ 1 }; i-1 < a; i++) {
		res *= i;
	}
	return(res);
}