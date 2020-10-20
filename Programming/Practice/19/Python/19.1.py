import itertools
print(' '.join([''.join(i) for i in itertools.permutations(r=int(input()), iterable=input())]))