import json as j
import openpyxl as oxl
from datetime import datetime
from flask import Flask, request
 
app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        
        global s, r
        s = request.get_json()
        print(s)
        r = j.load(s)
        book = oxl.Workbook()
        sheet = book.active()
        sheet["A1"] = "N"
        sheet["B1"] = "User ID"
        sheet["C1"] = "Datetime"
        sheet["D1"] = "Item"
        sheet["E1"] = "Price"
        
        for i in range(len(r["check"])):
    
            sheet["A" + str(i + 2)] = i + 1
            sheet["B" + str(i + 2)] = r["user_id"]
            sheet["C" + str(i + 2)] = datetime.now()
            sheet["D" + str(i + 2)] = r["check"][i]["item"]
            sheet["E" + str(i + 2)] = r["check"][i]["price"]
            
        book.save("data.xlsx")
        book.close()
        return "Это POST запрос"
    
    if request.method == 'GET':
        print(s)
        return s
 
    """
    # -*- coding: utf-8 -*-
import openpyxl as oxl
from datetime import datetime

book = oxl.Workbook()
sheet = book.active
sheet["A1"] = "N"
sheet["B1"] = "User ID"
sheet["C1"] = "Datetime"
sheet["D1"] = "Item"
sheet["E1"] = "Price"
r = {"user_id": "9359F683B13A18A1", "check":[{"item": "SANDALIANS","price": 250},{"item": "SOCKIANS","price": 100}]}
for i in range(len(r["check"])):
    
    sheet["A" + str(i + 2)] = i + 1
    sheet["B" + str(i + 2)] = r["user_id"]
    sheet["C" + str(i + 2)] = datetime.now()
    sheet["D" + str(i + 2)] = r["check"][i]["item"]
    sheet["E" + str(i + 2)] = r["check"][i]["price"]
    
book.save("data.xlsx")
book.close()
    """
if __name__ == "__main__":
    app.run()