import re 
<<<<<<< HEAD
pattern = r"a[0-9]{2}[a-z]55661"
pattern1 = r"a[a-z][0-9]{2}55661"
pattern2 = r"a[0-9][a-z][0-9]55661"
Siegesmund_tickets = input()
s = input()
answer = re.findall(pattern, s)
answer.extend(re.findall(pattern1, s))
answer.extend(re.findall(pattern2, s))
print(' '.join(answer) if answer != [] else -1) -1)
=======
pattern = r"a(\w\d\d|\d\w\d|\d\d\w)55661"
Siegesmund_tickets = input()
answer = re.findall(pattern, input())
print(' '.join(answer) if answer != [] else -1)
>>>>>>> 26705308f2a156b5156fd50f8f8c411cfc384f19
