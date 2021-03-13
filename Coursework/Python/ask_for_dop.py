# -*- coding: utf-8 -*-
"""
When request for completing sentence, this.

@author: NEFENTHES
"""

import requests
import json


req = requests.post("https://api.deepai.org/api/text-generator", data={
        'text': 'Billy Herrington is a legendary wrestler who',
    },
    headers={'api-key': 'eefe8151-c1e7-4531-871f-6b8b78472954'}
)

result = json.loads(req.text)
print(result["output"])