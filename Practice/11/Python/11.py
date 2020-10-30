# -*- coding: utf-8 -*-
#версия простая, однако
num, pow = int(input()), int(input())
result = 1
for i in range(abs(pow)):
	result *= num
if pow < 0:
	result = 1 / result
print(result)