#Bozosort
import random

def Bozosort(mas, second=0, third='', direction=True):
    if third == '':
            real_sort = mas.copy()
            real_sort.sort()
            
            if not direction:
                real_sort.reverse()
                    
            while mas != real_sort:
                x1 = random.randrange(0, len(mas))
                x2 = random.randrange(0, len(mas))
                
                while x1 == x2:
                    x2 = random.randrange(0, len(mas))
                    
                mas[x1], mas[x2] = mas[x2], mas[x1]
                    
            return mas
    else:
        return Bozosort([mas, second, third], direction=direction)

if __name__ == "__main__":
    n = int(input())
    x = list(map(int, input().split()))
    f, s, t = x[0], x[1], x[2]
    Bozosort(x)
    x_sqr = tuple(x)
    print(" ".join(map(str, x)))
    Bozosort(x, direction=False)
    print(" ".join(map(str, x)))
    print(" ".join(map(str, x_sqr)))
    print(" ".join(map(str, x)))
    print(" ".join(map(str, Bozosort(f, s, t))))
    print(" ".join(map(str, Bozosort(f, s, t, False))))
    