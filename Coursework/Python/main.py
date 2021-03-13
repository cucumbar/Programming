# -*- coding: utf-8 -*-

#-------------------------
#--------NEFENTHES--------
#-------------------------

import requests
# import urllib, urllib3
import json
# import handwritingio as hw


# tempo = hw.Client("N3C9JYP4C41G1V2D", "Q26BVMWS93BV20QZ")

req = requests.post("https://api.deepai.org/api/text-generator", data={
        'text': 'Billy Herrington is a legendary wrestler who',
    },
    headers={'api-key': 'eefe8151-c1e7-4531-871f-6b8b78472954'}
)

result = json.loads(req.text)
print(result["output"])


# BASE_URL = "https://api.handwriting.io"
# API_TOKEN = "N3C9JYP4C41G1V2D"
# API_SECRET = "Q26BVMWS93BV20QZ"
# OUT_FILE = "out.png"


# message_to_render = """Billy Herrington is a legendary wrestler who has worked his way up from world-class judo instructor - currently with TNA - to "Superstar" in the world of performance arts.
# Watch the latest episode of Bravo Presents The Ultimate Step: From Performance Arts to Performance Fitness"""
# #result["output"]


# headers={"Authorization" : "Basic {0}:{1}".format(API_TOKEN, API_SECRET)}
# s = requests.get(url=BASE_URL + '/render/png?',
#                   headers={"authorization" : "basic {0}:{1}".format(API_TOKEN, API_SECRET)},
#                   json={
#   'text': message_to_render,
#   'handwriting_id': '31SAZEF000DX', # find more ids at /handwritings
#   'handwriting_size': '15pt',
#   'height': '2in',
#   'width': '4in'
# })
# # now encode the params to go in the URL

# import base64





# # now encode the params to go in the URL
# params = urllib.parse.urlencode({ 
#   'text': message_to_render,
#   'handwriting_id': '31SAZEF000DX', # find more ids at /handwritings
#   'handwriting_size': '15pt',
#   'height': '2in',
#   'width': '4in'
# })
# # this is the actual rendering request for a PDF.
# url = BASE_URL + '/render/pdf?' + params
# req = requests.post(url)

# # now add our auth header
# base64string = base64.b64encode('%s:%s' % (API_TOKEN, API_SECRET))
# req.add_header("Authorization", "Basic %s" % base64string)

# # make the request
# resp = urllib3.urlopen(req)

# # save the response
# with open(OUT_FILE, 'wb') as f:
#   for chunk in resp:
#     f.write(chunk)
# print("results written to %s" % OUT_FILE)