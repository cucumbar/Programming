import tkinter as tk
import requests
# import time
import json
# from threading import Thread
# from os import startfile

# now = time.time()

def get_res():
    res = requests.get(r"http://localhost:3000")
    res = res.text.split('\n')
    cashfile = json.loads(res[43])
    return cashfile

# def timecheck():
#     while True:
#         if time.time() >= now + 10:
#             startfile(r"MainClient.pyw")
#             exit(0)
#         else:
#             time.sleep(1)
#             return

JSONData = get_res()
weather = JSONData["list"][0]["weather"][0]["main"]
temperature = round(JSONData["list"][0]["main"]["temp"] - 273.15)

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

# with open("PublicData.json", "r") as f:
#     jsonData = f.readline()

label = tk.Label(
    text=f"{weather}\n" + f"{temperature}°C",
    fg="black",
    bg="white",
    font="Arial 28",
    width=5,
    height=3
)
label.pack(fill=tk.BOTH, side=tk.TOP)

# if __name__ == '__main__':
window.mainloop()
    # Thread(target=timecheck()).start()
    
    



