# -*- coding: utf-8 -*-
from json import load

with open("config.JSON", "r") as f:
    whs = load(f)
    
with open("webhooksfinal.html", "w", encoding="utf-8") as f1, open("webhooks.txt", "r", encoding="utf-8") as f2:
    template = "".join(f2.readlines())
    for i in whs['webhooks']:
        res = f"""<div class="form-row align-items-center">
                        <div class="col">
                          <input type="text" value="{i}" class="form-control mb-2" disabled>
                        </div>
                        
                        <div class="col">
                          <button type="submit" name="del" value="{i}" class="btn btn-danger mb-2">Удалить</button>
                        </div>
                      </div>"""
        res += "\n{}\n"
        template = template.format(res)
        
    template = template.format("")
    print(template, file=f1)