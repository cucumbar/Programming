# -*- coding: utf-8 -*-
from re import sub
from time import localtime

with open("WidgetPage.txt", "r") as f1, open("PDataCash.txt", "r") as f2:
    widg = f1.readlines()
    repldat = f2.readline()

x = localtime()
widg = "".join(widg)
widg = sub(r"%", repldat.split()[0], widg, count=1)

if repldat.split()[0].lower() == r"clouds":
    if x.tm_hour >= 21 or x.tm_hour < 5:
        widg = sub(r"%", r"3n", widg, count=1)
    else:
        widg = sub(r"%", r"3d", widg, count=1)
elif repldat.split()[0].lower() == r"clear":
    if x.tm_hour >= 21 or x.tm_hour < 5:
        widg = sub(r"%", "1n", widg, count=1)
    else:
        widg = sub(r"%", "1d", widg, count=1)
else:
    if x.tm_hour >= 21 or x.tm_hour < 5:
        widg = sub(r"%", "4n", widg, count=1)
    else:
        widg = sub(r"%", "4d", widg, count=1)
        
widg = sub(r"%", repldat.split()[1], widg, count=1)
widg = sub(r"%", repldat.split()[1], widg, count=1)

with open("PublicData.json", "r") as f:
    dat = f.readlines()
    dat = "".join(dat)
    widg = sub(r"%", dat, widg, count=1)

with open("WidgetPage.html", "w") as f:
    print(widg, file=f)

with open(r"..\WidgetPage.html", "w") as f: #..\server(C++)\ConsoleApplication1\ConsoleApplication1\ ||||C:\\Users\\Михондрус\\myGitRepoCloned\\Programming\\Lab\\01\\server(C++)\\ConsoleApplication1\\ConsoleApplication1\\
    print(widg, file=f)