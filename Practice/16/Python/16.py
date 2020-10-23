import re 
pattern = r"a\w\d\d55661"
Siegesmund_tickets = input()
answer = re.findall(pattern, input())
print(' '.join(answer) if answer != [] else -1)