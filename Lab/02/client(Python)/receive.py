# -*- coding: utf-8 -*-
from requests import post
from time import sleep

try:
    t = post("http://localhost:5000",
    json='{"user_id": "9359F683B13A18A1", "check":[{"item": "SANDALIANS","price": 250},{"item": "SOCKIANS","price": 100}]}'
    )
    print(t.text)
    
except Exception as e:
    print('\n', e)
    sleep(20)