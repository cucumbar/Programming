# -*- coding: utf-8 -*-
import json
dUserSolvedT = {}
with open("in.json", "r") as jsif:
    data = json.load(jsif)
for i in data:
    if i['userId'] in dUserSolvedT.keys():
        if i['completed']:
            dUserSolvedT[i['userId']] += 1
    else:
        if i['completed']:
            dUserSolvedT[i['userId']] = 1
        else:
            dUserSolvedT[i['userId']] = 0
dResultData = []
for i in dUserSolvedT.keys():
    dResultData.append({"userId" : i, "task_completed" : dUserSolvedT[i]})
with open("out.json", "w") as jsof:
    json.dump(dResultData, jsof)