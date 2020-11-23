import tkinter as tk
import os
from threading import Thread

os.startfile(r"..\server(C++)\supscripts\jsonrework.py")

datapath = r"PDataCash.txt"
with open(datapath, "r") as f:
    rData = f.readline()

window = tk.Tk()
window.geometry('150x230')
window.resizable(width=False, height=False)

x = (window.winfo_screenwidth() - window.winfo_reqwidth()) / 2
y = (window.winfo_screenheight() - window.winfo_reqheight()) / 2
window.wm_geometry("+%d+%d" % (x, y))

frame1 = tk.Frame(master=window, width=50, height=50, bg="gold")
frame1.pack(fill=tk.BOTH, side=tk.TOP)
 
frame3 = tk.Frame(master=window, width=50, height=50, bg="gold")
frame3.pack(fill=tk.BOTH, side=tk.BOTTOM)

label = tk.Label(
    text=f"{rData.split()[0]}\n" + f"{rData.split()[1]}°C",
    fg="black",
    bg="white",
    font="Arial 28",
    width=5,
    height=3
)
label.pack(fill=tk.BOTH, side=tk.TOP)

os.startfile(r"widgetparser.py")

if __name__ == '__main__':
    Thread(target=os.startfile(r"..\server(C++)\ConsoleApplication1\Debug\ConsoleApplication1.exe")).start()
    Thread(target=window.mainloop()).start()





