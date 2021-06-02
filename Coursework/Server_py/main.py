# This Python file uses the following encoding: utf-8
import json
import requests
from flask import *
from PIL import Image, ImageDraw, ImageFont


class Buffer_msg():
    def __init__(self, *args):
        self.buff = []

        for i in args:
            self.buff.append(i)

    def bring(self):
        tempo = self.buff.pop()
        return tempo

    def release(self):
        self.buff.clear()
        return

    def __iadd__(self, other):
        self.buff.extend(other)
        return self


global_buff = Buffer_msg()
new_imgs = 0

server = Flask(__name__)

@server.route("/", methods=['POST'])
def index():
    global global_buff

    global_buff.release()

    req_res = request.get_json()

    print(req_res["len"])
    print("vse slomal")
    print(req_res)
    print(req_res["user_text"])

    if not len(req_res["user_text"]):
        return ""

    print(1111111111111)
    res = requests.post("https://pelevin.gpt.dobro.ai/generate/", json={"prompt" : req_res["user_text"], "length" : req_res["len"]})
    print(2222222222222)
    #print(res.content)
    #print(res.text)

    print(3333333333333)
    print(res.json())
    print("{\"result_list\" : %r" % (res.json()["replies"][0]) + r"}") #str.encode('unicode_escape')

    resp = Response("{\"result_list\" : \"%r\"" % (res.json()["replies"][0]) + r"}")

    resp.headers['Access-Control-Allow-Origin'] = '*'
    resp.headers['Content-Type'] = 'applicaion/json;charset=utf-8'

    temp = res.json()["replies"][1:]
    global_buff += temp

    return resp


@server.route("/vars",  methods=["GET"])
def answering():
    if len(global_buff.buff):
        return global_buff.bring()

    else:
        return ""


@server.route("/get_handwrite", methods=["POST"])
def receive_img():
    global new_imgs
    req_res = request.get_json()
    print(req_res)

    t_r = Image.open("Bg_best.png") #продолжить и закончить

    idraw = ImageDraw.Draw(t_r)
    text = req_res["to_handwrite"]
    fsize = req_res["f_size"]

    print(text)

    text_f = text
    text_f_list = []
    i = 0

    while i < len(text_f):
        if round(2.5 * i * fsize * 5 * 1.3333333333333333 / 4) > (t_r.width - 15): # рассчет длины рукописной строки.
            text_f_list.append(text_f[0:i] )
            #text_f_list.append()

            text_f_list.append(text_f[i:len(text_f)])
            text_f = text_f[i:len(text_f)]
            i = 0

        i += 1

    font = ImageFont.truetype("Gogol.ttf", size=fsize * 5)
    text_f_list = "\n".join(text_f_list)
    print(text_f_list)

    #for line in range(len(text_f_list)):
    idraw.text((10, 20), text_f_list, (0, 0, 0), font=font)

    new_imgs += 1
    t_r.save(f"result{new_imgs}.png")

    return send_file(f"result{new_imgs}.png", mimetype='image/png')

#@server.route("/g", methods=["GET"])
#def index_2():
#    t_r = Image.open("bg_right.png")
#    t_l = Image.open("bg_left.png")

#    idraw = ImageDraw.Draw(t_r)
#    text = "Bruh & Брох"

#    font = ImageFont.truetype("Gogol.ttf", size=14)
#    idraw.text((10, 10), text, font=font)

#    t_r_BA = t_r.crop()
#    t_r_byte_arr = io.BytesIO()
#    t_r_BA.save(t_r_byte_arr, format='PNG')
#    t_r_byte_arr = t_r_byte_arr.getvalue() #это

#    return str(t_r.tobytes())

if __name__ == "__main__":
    server.run(debug=True)
