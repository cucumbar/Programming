import openpyxl
import time
from flask import Flask, request

app = Flask(__name__)
siz_buf = 0
bufera = list()

def save():
    global bufera
    
    try:
        with open("pokupki.xlsx", "r"):
            flag = True
            
    except FileNotFoundError:
        flag = False
       
    if not flag:
        res_book = openpyxl.Workbook()
        res_book.active['A1'] = 'N'
        res_book.active['B1'] = 'User ID'
        res_book.active['C1'] = 'Datetime'
        res_book.active['D1'] = 'Item'
        res_book.active['E1'] = 'Prise'
        res_book.save('pokupki.xlsx')
      
    else:
        res_book = openpyxl.open("pokupki.xlsx")
                           
    listok = res_book.active
    row_big = len(listok['A'])
    now = time.strftime("%m/%d/%Y, %H:%M:%S", time.localtime())
    row = row_big + 1
    
    for dataset in bufera:
        uid = dataset['user_id']
        check = dataset['check']
        
        for item in check:
            listok[row][0].value = row - 1
            listok[row][1].value = uid
            listok[row][2].value = now
            listok[row][3].value = item['name']
            listok[row][4].value = item['price']
            row += 1

    res_book.save("pokupki.xlsx")
    res_book.close()
   
   
@app.route('/', methods=['POST', 'GET'])
def index():
    global bufera
   
    if request.method == 'POST':
        bufera += [request.json]
        print('req.body:', bufera[-1])
      
        if (len(bufera) > siz_buf):
            save()
            bufera.clear()
         
            return 'OK'
      
    elif request.method == 'GET':
        return 'Это GET запрос'


if __name__ == '__main__':
    app.run()