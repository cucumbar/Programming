# -*- coding: utf-8 -*-
import json as js
import requests as req
from os import startfile

inp = req.get("http://api.openweathermap.org/data/2.5/find?q=Simferopol,UA&type=like&APPID=a50134af28c2718b67c6f87a3f126eef")
JSONData = inp.json()

if __name__ != "__main__":
    with open(r"..\server(C++)\ConsoleApplication1\ConsoleApplication1\supscripts\PublicData.json", "w") as f:
        js.dump(JSONData, f)
else:
    with open(r"PublicData.json", "w") as f:
        js.dump(JSONData, f)
        
# with open("PublicData.json", "r") as read_file:
#     UnpackData = js.load(read_file)

weather = JSONData["list"][0]["weather"][0]["main"]
temperature = JSONData["list"][0]["main"]["temp"] - 273.15

if __name__ != "__main__":
    with open(r"..\server(C++)\ConsoleApplication1\ConsoleApplication1\supscripts\PDataCash.txt", "w") as f:
        print(weather, round(temperature), file=f)
else:
    with open(r"PDataCash.txt", "w") as f:
        print(weather, round(temperature), file=f)
        
startfile("widgetparser.py")