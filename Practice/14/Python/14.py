pows, p, two, numb = [0], 0, 1, int(input())
while two * 2 <= numb:
    two *= 2
    p += 1
    pows.append(p)
print(len(pows))