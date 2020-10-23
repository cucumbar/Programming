formule = lambda x: int(x[0]) + int(x[1]) * int(x[2]) + 9.8 * int(x[2]) ** 2 / 2
print(formule(input().split()))