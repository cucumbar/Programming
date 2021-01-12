# -*- coding: utf-8 -*-
"""вывод количества строк кода, исключая пустые"""
with open("GUI_test.py", "r", encoding="utf-8") as f:
    x = "".join(f.readlines())
    count = 0
    x = x.split("\n")
    for i in x:
        if i:
            count += 1