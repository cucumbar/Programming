# -*- coding: utf-8 -*-
#"эффективная" в других языках в следствие отсутствия в оных длинной арифметикеесь
def mul(a):
    rez = 1
    for i in range(len(a)):
        rez *= a[i]
    return rez
fact = {0 : 1, 1 : 1}
numb = int(input())
res = 1
for i in range(1, numb+1):
    if i not in fact.keys():
        fact[i] = mul([j for j in range(1, i+1)])
        res = fact[i]
    else:
        res *= i
print(res)