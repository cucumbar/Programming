person1, person2 = list(map(int, input().split(':'))), list(map(int, input().split(':')))
time1h, time1m = person1[0], person1[1]
time2h, time2m = person2[0], person2[1]
if time1h == time2h: 
    if abs(time1m - time2m) <= 15:
        print('Встреча состоится')
    else:
        print('Встреча не состоится')
elif abs(time1h - time2h) == 1:
    if abs(60 - time1m - time2m) <= 15:
        print('Встреча состоится')
    else:
        print('Встреча не состоится')
else:
    print('Встреча не состоится')