import re 

pattern = r"a[0-9]{2}[a-z]55661"
pattern1 = r"a[a-z][0-9]{2}55661"
pattern2 = r"a[0-9][a-z][0-9]55661"
Siegesmund_tickets = input()
s = input()
answer = re.findall(pattern, s)
answer.extend(re.findall(pattern1, s))
answer.extend(re.findall(pattern2, s))
print(' '.join(answer) if answer != [] else -1)
pattern = r"a(\w\d\d|\d\w\d|\d\d\w)55661"
Siegesmund_tickets = input()
answer = re.findall(pattern, input())
print(' '.join(answer) if answer != [] else -1)
