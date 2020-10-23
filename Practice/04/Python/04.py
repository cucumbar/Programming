c, d = map(int, input().split())
c, d = d, c
print(c, d)
#или
c, d = map(int, input().split())
r = c
c = d
d = r
print(c, d)