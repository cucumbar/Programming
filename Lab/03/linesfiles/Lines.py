# -*- coding: utf-8 -*-

#-----------------
#----NEFENTHES----
#-----------------

#     4) исправить подсказку и прочие надписи
#     1) сделать шарики красивые альфа композитом
#     2) добавить звук
#     3) скомпилировать в ехе

import tkinter as tk
import random
import copy
from PIL import ImageTk as itk, Image

# import pyglet
# song = pyglet.media.load('file.mp3')
# song.play()
# pyglet.app.run()

MainFrame = tk.Tk()



class MARKED_LABEL(tk.Label):
    
    def __init__(self, row, col):
        
        tk.Label.__init__(self, master=MainFrame)
        self.row = row
        self.col = col
        self.coltype = "ntg"
        self.has_ball = False
        
        

actual_game = [[0 for i in range(9)] for j in range(9)]

MainFrame["bg"] = "#464646"
MainFrame.title("ЛИНИИ 76")

REDtileset = Image.open("./resources/ball-red.png").convert("RGBA")
VIOtileset = Image.open("./resources/ball-violet.png").convert("RGBA")
PNKtileset = Image.open("./resources/ball-pink.png").convert("RGBA")
GRNtileset = Image.open("./resources/ball-green.png").convert("RGBA")
YLWtileset = Image.open("./resources/ball-yellow.png").convert("RGBA")
BLUtileset = Image.open("./resources/ball-blue.png").convert("RGBA")
AQAtileset = Image.open("./resources/ball-aqua.png").convert("RGBA")

BALLSpictures = {
    "red":REDtileset, 
    "vio":VIOtileset, 
    "pnk":PNKtileset, 
    "grn":GRNtileset, 
    "ylw":YLWtileset, 
    "blu":BLUtileset, 
    "aqa":AQAtileset
        }

def sendCOORD():
    
    global clicked_first_cell
    clicked_first_cell = ()

sendCOORD()

MainFrame.geometry("1000x700")
MainFrame.resizable(width=False, height=False)
    
tileset = Image.open("./resources/cell-bgr.png")
img = itk.PhotoImage(tileset.crop((1, 0, 67, 66)))
img_2 = itk.PhotoImage(tileset.crop((1, 69, 67, 135)))
BALLS = {}


for i in ["red", "vio", "pnk", "grn", "ylw", "blu", "aqa"]:
    
    tileDEACT = itk.PhotoImage(tileset.crop((1, 0, 67, 66)))
    tileACT = itk.PhotoImage(tileset.crop((1, 69, 67, 135)))
    
    tileACT.paste(BALLSpictures[i], (1, 1))
    tileDEACT.paste(BALLSpictures[i], (1, 1))
    BALLS[i] = (tileDEACT, tileACT)


def globalSHID():
    
    global located
    global result
    global BALLSonAG 
    global rec_num
    rec_num = 0
    result = 0  
    located = []                                                               #говнокод ужасающий
    BALLSonAG = {
    "red":[], 
    "vio":[], 
    "pnk":[], 
    "grn":[],
    "ylw":[], 
    "blu":[],
    "aqa":[],
        }


def showSCORES():
    global result
    
    SCORES = tk.Label(MainFrame, 
                     text="Счёт: %d" % result, 
                     font=("Courier", "20"),
                     fg="White",
                     bg="#464646",
                     padx=5,
                     pady=5
                     )
    
    SCORES.grid(row=1,
               column=10,
               padx=10)
    
globalSHID()


def GAMEcheck():
    
    global result
    global free_cells
    global gameEND
    
    free_cells = []
    
    for j in range(9):
            for k in range(9):
                
                if not actual_game[j][k].has_ball:
                    free_cells.append((j, k))
                    
                else:
                    def lookSEQ(i, r):
                        same_col_row = True
                        while same_col_row:
                            try:
                                if not (actual_game[j+i][k+r].coltype == actual_game[j][k].coltype):
                                    same_col_row = False
                                    
                                else:
                                    if i != r:                #топ десять самых уродливых обходов массивов
                                        if i > r:
                                            if i > 0:
                                                i += 1
                                                
                                            else:
                                                i -= 1
                                                                                            
                                        else:
                                            if r > 0:
                                                r += 1
                                                
                                            else:
                                                r -= 1
                                            
                                    else:
                                        if i > 0:
                                            i += 1
                                            r += 1
                                            
                                        elif i == 0:
                                            i += 1
                                            r -= 1
                                            
                                        else:
                                            i -= 1
                                            r -= 1
                                            
                            except IndexError:
                                same_col_row = False
                                
                        return (i, r)
                    
                    count = [lookSEQ(i, r) for i, r in [(0, 0), (0, 1), (1, 0), (1, 1), (-1, 1), (1, -1)]]
                    
                    for i, r in count:
                        if max(abs(i), abs(r)) == 5:
                            result += max(abs(i), abs(r)) * 2
                            
                            for u in range(max(abs(i), abs(r))):
                                if max(abs(i), abs(r)) == abs(i) and i != r:   #говно собственной персоной
                                    
                                    actual_game[j+u][k].config(image=img)
                                    actual_game[j+u][k].coltype = "ntg"
                                    actual_game[j+u][k].has_ball = False
                                    
                                elif max(abs(i), abs(r)) == abs(r) and i != r:
                                    
                                    actual_game[j][k+u].config(image=img)
                                    actual_game[j][k+u].coltype = "ntg"
                                    actual_game[j][k+u].has_ball = False
                                
                                else:
                                    
                                    actual_game[j+u][k+u].config(image=img)
                                    actual_game[j+u][k+u].coltype = "ntg"
                                    actual_game[j+u][k+u].has_ball = False


    if not free_cells:
        gameEND = tk.Label(master=MainFrame, 
                           text="ВЫ LOSE.", 
                           font=("Courier", "40"),
                           borderwidth=0)
        gameEND.place(x=300, y=300)
        
        
def computerMOVE():
    
    global tipCONTENT
    global free_cells
    global gameEND
    
    balls_for_generate = ["red", "vio", "pnk", "grn", "ylw", "blu", "aqa", "ntg"]
    xy = [(random.randrange(0, 8), random.randrange(0, 8))]
    
    GAMEcheck()
    
    for i in range(3):
        
        b = random.randrange(0, 7)

        try:
            xprob, yprob = random.choice(free_cells)
            
        except IndexError:
            gameEND = tk.Label(master=MainFrame, 
                               text="ВЫ LOSE.", 
                               font=("Courier", "40"))
            gameEND.place(x=300, y=300)
            
        try:
            xy.append((xprob, yprob))
            BALLSonAG[balls_for_generate[b]].append(xy[i])  #если что искать ошибки тут
            if not actual_game[xy[i][0]][xy[i][1]].has_ball:
                actual_game[xy[i][0]][xy[i][1]].config(image=BALLS[balls_for_generate[b]][0])
                actual_game[xy[i][0]][xy[i][1]].coltype = balls_for_generate[b]
                actual_game[xy[i][0]][xy[i][1]].has_ball = True
            else:
                pass
            
        except UnboundLocalError:
            pass
        
    tipCONTENT = BALLSonAG.copy()
    showSCORES()
    xy.pop()
        
    
def MOVEpossibilty(i1, j1, i2, j2):
    
    # global located
    
    # located.append((i1, j1, True)) # XXX
    
    # node = located.pop()
    
    # if (node[0], node[1]) == (i2, j2):
    #     return True
    
    # else:
    #     for i in (-1, 0, 1):
    #         for j in (-1, 0, 1):
                
    #             if i != 0 or j != 0:
    #                 try:
                        
    #                 if not actual_game[i1+i][j1+j].has_ball
    # for i in (-1, 0, 1):
    #     for j in (-1, 0, 1):
            
    #         if i != 0 or j != 0:
    #             try:
    #                 if not actual_game[i1+i][j1+j].has_ball and (i1+i, j1+j) not in located:
    #                     if (i1+i, j1+j) == (i2, j2):
    #                         return True
    #                     elif (i1+i, j1+j, False) not in located:
    #                         located.append((i1+i, j1+j, False))
                        
                        
    #             except IndexError:
    #                 continue
                
    # for each in located:
    #     if not each[2]:
    #         MOVEpossibilty(each[0], each[1], i2, j2)
        
    # if (i2, j2) in located:
    #     located.clear()
    #     return True
    # else:
    #     return False
    
    if actual_game[i1][j1].has_ball:
        return True
    else:
        return False
    
    

def playerMOVE(event):
    
    this_cell = actual_game[event.widget.row][event.widget.col]
    global clicked_first_cell
    global BALLSonAG
    global gameEND
    # global result
    
    GAMEcheck()
    
    if this_cell.has_ball: # XXX желательно чтоб когда на разные шары нажимаешь, выделение предыдущего уходило
        
        event.widget.config(image=BALLS[this_cell.coltype][1])        
        clicked_first_cell = (event.widget.row, event.widget.col)
        print(clicked_first_cell)
        
    elif clicked_first_cell:
        
        if MOVEpossibilty(clicked_first_cell[0], clicked_first_cell[1], this_cell.row, this_cell.col):
            # r = copy.copy(result)
            this_cell.has_ball = True
            this_cell.coltype = copy.copy(actual_game[clicked_first_cell[0]][clicked_first_cell[1]].coltype)
            BALLSonAG[this_cell.coltype].remove(clicked_first_cell)
            BALLSonAG[this_cell.coltype].append((this_cell.row, this_cell.col))
            actual_game[this_cell.row][this_cell.col].config(image=BALLS[this_cell.coltype][0])
            
            actual_game[clicked_first_cell[0]][clicked_first_cell[1]].has_ball = False
            actual_game[clicked_first_cell[0]][clicked_first_cell[1]].coltype = "ntg"
            actual_game[clicked_first_cell[0]][clicked_first_cell[1]].config(image=img)
            # GAMEcheck()
            
            # while r != result:
            #     if MOVEpossibilty(clicked_first_cell[0], clicked_first_cell[1], this_cell.row, this_cell.col):
            #         r = copy.copy(result)
            #         this_cell.has_ball = True
            #         this_cell.coltype = copy.copy(actual_game[clicked_first_cell[0]][clicked_first_cell[1]].coltype)
            #         BALLSonAG[this_cell.coltype].remove(clicked_first_cell)
            #         BALLSonAG[this_cell.coltype].append((this_cell.row, this_cell.col))
            #         actual_game[this_cell.row][this_cell.col].config(image=BALLS[this_cell.coltype][0])
                    
            #         actual_game[clicked_first_cell[0]][clicked_first_cell[1]].has_ball = False
            #         actual_game[clicked_first_cell[0]][clicked_first_cell[1]].coltype = "ntg"
            #         actual_game[clicked_first_cell[0]][clicked_first_cell[1]].config(image=img)
            #         GAMEcheck()
            
            computerMOVE()
            
        print(this_cell.row, this_cell.col)
        
    else:
        pass


for row in range(9):
    for col in range(9):
        cell = MARKED_LABEL(row, col)
        actual_game[row][col] = cell
        cell.config(image=img, borderwidth=0)
        cell.bind("<Button-1>", playerMOVE)
        cell.grid(row=row, 
                  column=col, 
                  padx=1, 
                  pady=1
                  )      

computerMOVE()


def createNEWgame():
    
    global result
    global gameEND
    
    for i in range(9):
        for j in range(9):
            actual_game[i][j].config(image=img)
            actual_game[i][j].coltype = "ntg"
            actual_game[i][j].has_ball = False
            
    computerMOVE()
    result = 0
    
    gameEND.destroy()
    
    showSCORES()
    GAMEcheck()
    

new_game = tk.Button(master=MainFrame, 
                     text="Начать заново",
                     padx=5,
                     pady=5,
                     font=("Courier", "16"),
                     background="grey",
                     activebackground="#460046",
                     command=createNEWgame)

new_game.grid(row=8,
              column=10,
              padx=10)

def nothing():
    pass

make_comp_move = tk.Button(master=MainFrame, 
                     text="Сделать ход",
                     padx=4,
                     pady=4,
                     font=("Courier", "16"),
                     background="grey",
                     activebackground="#460046",
                     command=computerMOVE)

make_comp_move.grid(row=7,
              column=10,
              padx=10)


TITLE = tk.Label(MainFrame, 
                 text="Линии 2", 
                 font=("Courier", "24"),
                 fg="White",
                 bg="#464646",
                 )

TITLE.grid(row=0,
           column=10,
           padx=10)


Tip = tk.Label(MainFrame, 
               text="подсказка(не поможет):", 
               font=("Courier", "20"),
               fg="White",
               bg="#464646",
               )

Tip.grid(row=3,
         column=10,
         padx=10)



def showTIP(): # XXX
    
    for i in tipCONTENT.keys():
        count = 0
        if tipCONTENT[i]:
            
            for j in tipCONTENT[i]:
                tipBALLS = tk.Label(MainFrame,
                                    image=BALLS[i][0],
                                    borderwidth=0
                                    )
                
                tipBALLS.grid(row=4+count,
                      column=10,
                      padx=10)
            
                count += 1

showTIP()

MainFrame.mainloop()
