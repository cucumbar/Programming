from json import load, dump, decoder


try:
    with open("config.json", "r") as f:
        for i in f.readlines():
            if i != '':
                flag = True
                break
            else:
                flag = False
                break
        flag = True
        
except FileNotFoundError or decoder.JSONDecodeError:
    flag = False
    
    
if flag:
    with open("config.json", "w") as f, open("config.txt", "r") as ff:
        shit_container = ff.readlines()
        shit_dictionary = {"webhooks": shit_container for j in range(1)}
        dump(shit_dictionary, f)    
else:
    with open("config.json", "r") as fin:
        shit_old = load(fin)
        
    with open("config.json", "w") as f, open("config.txt", "r") as ff:
        shit_container = ff.readlines()
        if set(shit_container) not in set(shit_old["webhooks"]):
            for i in shit_container:
                if i not in shit_old["webhooks"]:
                    shit_old["webhooks"].append(i)
        dump(shit_old, f)


with open("config.json", "r") as f:
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

if __name__ != "__main__":
    with open('log.txt', 'w') as f:
        print("lol", file=f)