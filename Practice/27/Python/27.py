# -*- coding: utf-8 -*-
n = int(input())
a = list(map(int, input().split()))
a_min = []
res = []
j = 0


while j < n:
    
    j += 1
    
    if j < 5:
        res.append(a[0:j])
        
    elif j == 5:
        res.append(a[0:j])
        a_min.append(a[0:j])
        
    else:
        
        if a[j-1] < max(a_min[0]):
            a_min[0][a_min[0].index(max(a_min[0]))] = a[j-1]
        res.append(a_min[0].copy())
        
print("\n".join([" ".join(map(str, sorted(res[i], reverse=True))) for i in range(len(res))]))

