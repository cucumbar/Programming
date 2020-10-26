import re 
pattern = r"a(\w\d\d|\d\w\d|\d\d\w)55661"
Siegesmund_tickets = input()
answer = re.findall(pattern, input())
print(' '.join(answer) if answer != [] else -1)
