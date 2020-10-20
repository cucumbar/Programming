n = int(input())
def count_sys(a, syst):
    res = ['']
    while a > 0:
        res.append(str(a % syst))
        a //= syst
    res.reverse()
    xres = list('0' for i in range((n - len(res)+1)))
    xres.extend(res)
    xres.pop()
    return ''.join(xres)
letts = [i for i in input()]
letts_cop = set(letts)
combinations = ['0' * n]
combinations.extend([count_sys(i, len(letts_cop)) for i in range(1, len(letts_cop) ** n)]) # if len(set(count_sys(i, len(letts_cop))).difference(set(list(range(letts_cop))))) == 0]
print(' '.join([''.join([letts[int(i)] for i in j]) for j in combinations if len(letts_cop.intersection(set([letts[int(i)] for i in j]))) == len(letts_cop)]))
combinations = []