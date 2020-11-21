import tkinter as tk
import os

ServerPath = r"..\server(C++)\supscripts\jsonrework.py"
os.startfile(ServerPath)

datapath = r"..\server(C++)\supscripts\PDataCash.txt"
with open(datapath, "r") as f:
    rData = f.readlines()

window = tk.Tk()


frame1 = tk.Frame(master=window, width=50, height=50, bg="gold")
frame1.pack(fill=tk.BOTH, side=tk.TOP, expand=True)

# label1 = tk.Label(
#     text=f"""{rData}""",
#     fg="black",
#     bg="white",
#     font="Arial 30",
#     width=10,
#     height=7
# )
 
frame3 = tk.Frame(master=window, width=50, height=50, bg="gold")
frame3.pack(fill=tk.BOTH, side=tk.BOTTOM, expand=True)

# datapath = os.path.join(os.path.dirname(__file__),r'01\server(C++)\supscripts',r'b',r'PData.txt')

label = tk.Label(
    text=f"""{rData[1]}""",
    fg="black",
    bg="white",
    font="Arial 40",
    width=3,
    height=2
)
label.pack(fill=tk.BOTH, side=tk.TOP, expand=True)
 
 
window.mainloop()