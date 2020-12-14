<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-201(1)<br>
Кривошапко Михаила Игоревича<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

## Постановка задачи

Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса.  В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.

Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Цель работы
Цель: Получить представления о структуре post-запроса, изучить webhooks как метод взаимодействия web-приложений;
Каталоги:
[[Сервер]](./server(C++)) [[Клиент]](./client(Python))
## Выполнение работы

Первым шагом было изучение Webhook'ов. Была прочитаны и созданы требуемые запросы.

Следующим шагом был разработан c++ сервер с вставками python.

Файл [ConsoleApplication1.cpp](./server(C++)/ConsoleApplication1/ConsoleApplication1/ConsoleApplication1.cpp) содержит функцию входа *main*.

Проект имеет несколько существенных изъянов, однако их планируется исправить в ближайшие сроки.

### Информация о проекте

Для разработки сервера былb использованы: IDE Visual Studio 2017 15.9.27 (С++), IDE Spyder реализации Anaconda для Windows(Python 3.8.3)
Для разработки клиента была использована IDE Spyder реализации Anaconda для Windows(Python 3.8.3)
### Обязательная информация

1. На сайте openweathermap.org был получен следующий ключ api: **a50134af28c2718b67c6f87a3f126eef**
2. Был составлен следующий запрос: http://api.openweathermap.org/data/2.5/find?q=Simferopol,UA&type=like&APPID=a50134af28c2718b67c6f87a3f126eef
3. Для пункта 2 был использован метод localetime(), контактирующий с API сервисов всемирного времени, из библиотеки time языка Python
4. Полный исходный код сервера:
```c++
//ConsoleApplication1
#include <iostream>
#include <fstream>
#include "include/cpp_httplib/httplib.h"
#include <string>
using namespace httplib;
//using namespace fstream;
//using namespace string;

// В этой функции формируем ответ сервера на запрос
#include <iostream>
#include <string>
#include "include/cpp_httplib/httplib.h"
#include <fstream>

std::ofstream logger("log.txt");
using namespace httplib;

/*
#include <iostream>
#include "include/cpp_httplib/httplib.h"
using namespace httplib;

int main() {
	// Создаём клиент и привязываем к домену. Туда пойдут наши запросы
	Client cli("http://webhook.site");
	// Отправляем post в теле которого будет текст {"Hello": "world"}
	auto res = cli.Post("/6ef5a6b1-be3c-4dae-8f1d-16f6f94d6620", R"({"Hello": "world"})", "text/json");
	// res преобразуется в true, если запрос-ответ прошли без ошибок
	if (res) {
		// Проверяем статус ответа, т.к. может быть 404 и другие
		if (res->status == 200) {
			// В res->body лежит string с ответом сервера
			std::cout << res->body << std::endl;
		}
		else {
			std::cout << "Status code: " << res->status << std::endl;
		}
	}
	else {
		auto err = res.error();
		std::cout << "Error code: " << err << std::endl;
	}
}
*/

void gen_get1response(const Request& req, Response& res){
	system(u8"..\\ConsoleApplication11\\ConsoleApplication11\\whpedito.py");
	std::cout << "0\n";
	std::string path1 = u8"..\\ConsoleApplication11\\ConsoleApplication11\\webhooksfinal.html";
	std::string path2 = u8"webhooksfinal.html"; // ..\\ConsoleApplication11\\ConsoleApplication11
	std::string pathjsonwork = u8"..\\ConsoleApplication11\\ConsoleApplication11\\config.txt"; //data:text/html,<form action=http://localhost:1234 method=post><input name=key></form>
	std::ifstream fin1;
	std::cout << "1\n";
	std::ifstream fin2;
	std::cout << "2\n";
	std::ofstream fout1(pathjsonwork);
	std::cout << "3\n";
	fin1.open(path1);
	fin2.open(path2);
	char ch;
	std::string htmlres1 = "";
	if (req.method == "POST" && fout1) {
			std::string x;
			x = req.body.c_str();
			fout1 << x;
			system(u8"..\\ConsoleApplication11\\ConsoleApplication11\\whpedito.py");
	}
	else {
		if (!(fin1.is_open())) {
			std::cout << "no connection\n";
		}
		else {
			while (fin1.get(ch)) {
				htmlres1 += ch;
			}
		}
		std::string htmlres2 = "";
		if (!(fin2.is_open())) {
			std::cout << "no connection\n";
		}
		else {
			while (fin2.get(ch)) {
				htmlres1 += ch;
			}
		}
		if (htmlres1 != "") {
			res.set_content(htmlres1, "text/html");
		}
		else {
			res.set_content(htmlres2, "text/html");
		}
	}
	fin1.close();
	fin2.close();
	fout1.close();
}

void gen_get2response(const Request& req, Response& res) {
	// Выводим на экран тело запроса
	std::cout << req.body.c_str();
	// Здесь будет ответ, пока-что взят пример из документации
	std::string str = u8"KU KU";
	// Отправляем ответ
	res.set_content(str, "text/json; charset=UTF-8");
}

int main() {
	Server svr;                            // Создаём сервер
	svr.Get("/webhooks", gen_get2response);
	svr.Post("/", gen_get1response);// Вызвать функцию gen_response на post запрос
	std::cout << "Start server... OK\n"; // cout использовать нельзя
	svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
}

```
```py
#whpedito.py
# -*- coding: utf-8 -*-
from json import load, dump


try:
    with open("config.json", "r") as f:
        flag = True
        
except FileNotFoundError:
    flag = False
    
    
if not flag:
    with open("config.json", "w") as f, open("config.txt", "r") as ff:
        shit_container = ff.readlines()
        shit_dictionary = {"webhooks": shit_container for j in range(1)}
        dump(shit_dictionary, f)    
else:
    with open("config.json", "r") as fin:
        shit_old = load(fin)
        
    with open("config.json", "w") as f, open("config.txt", "r") as ff:
        shit_container = ff.readlines()
        if shit_container[0] not in shit_old["webhooks"]:
            shit_old["webhooks"].append(shit_container[0])
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
        print("lol", file-f)
```
```py
#WebHookWork.py
# -*- coding: utf-8 -*-
import json

from flask import Flask, request
 
app = Flask(__name__)
 
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        return "Это POST запрос"
    if request.method == 'GET':
        return "Это GET запрос"
 
if __name__ == "__main__":
    app.run()
```
5. Полный код Клиента:
```py
...............
```
6. Скриншот клиентского приложения:

![](./labakartinki/1.jpg)

Рисунок 1. Графический интерфейс программы-клиента.

7. Скриншот браузерного виджета:

![](./labakartinki/2.jpg)

Рисунок 2. HTML-виджет на local-hostе.

Каталоги:
[[Сервер]](./server(C++)) [[Клиент]](./client(Python))
## Вывод
Были выполнены поставленные задачи, а также формально достигнута цель данной работы - были получены представления о структуре post-запроса, изучены webhooks как метод взаимодействия web-приложений, однако экспериментальная часть лабораторной(программа) все еще требует некоторой доработки.

Разработка сервера была выполнена с использованием сторонних библиотек: cpp-httplib для работы с http запросами, json для работы с JSON файлами. Клиент использует такие библиотеки как: openpyxl для работы с электронными таблицами, os для работы с файловой системой, json для работы с JSON файлами.