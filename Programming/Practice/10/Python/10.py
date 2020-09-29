# -*- coding: utf-8 -*-
goal, left1, left2, right1, right2 = map(int, input().split())
DontExist = True
if left1 <= left2:
    if left1 + right1 == goal:
        print(left1, right1)
        DontExist = False
    elif left1 + right2 == goal:
        print(left1, right2)
        DontExist = False
else:
    if left2 + right1 == goal:
        print(left2, right1)
        DontExist = False
    elif left2 + right2 == goal:
        print(left2, right2)
        DontExist = False
if DontExist == True: print(-1)