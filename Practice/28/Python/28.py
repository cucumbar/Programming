# -*- coding: utf-8 -*-
def factorise(a):
    mults = []
    i = 2
    
    while i <= a + 1:
        if a % i == 0:
            mults.append(i)
            a //= i
            i -= 1
        i += 1
    
    ans = [str(i) + "^" + str(mults.count(i)) if mults.count(i) > 1 else str(i) for i in set(mults)]
    return "*".join(ans)

print(factorise(999))
print(factorise(10))
print(factorise(1000000000))
print(factorise(1))