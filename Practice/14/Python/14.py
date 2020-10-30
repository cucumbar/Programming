pows, p, two, numb = [0], 0, 1, int(input())
if numb > 0:
    while two * 2 <= numb:
        two *= 2
        p += 1
        pows.append(p)
else:
    pows.pop()
print(len(pows))
#chto