res = 1
Siegesmund_words = [i for i in 'halёloklempnerdasistfantastischfluggegecheimen']
Siegesmund_letters = set(Siegesmund_words)
Siegesmund_wordcount = {i : Siegesmund_words.count(i) / len(Siegesmund_words) for i in Siegesmund_letters}
print(Siegesmund_wordcount)
try:
    for i in input():
        res *= Siegesmund_wordcount[i]
except KeyError:
    res = 0
print(res)