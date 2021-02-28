﻿#include <iostream>
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
// В этой функции формируем ответ сервера на запрос

void gen_get1response(const Request& req, Response& res) {
	system(u8"..\\ConsoleApplication11\\whpedito.py");
	std::cout << "0\n";
	std::string path1 = u8"..\\ConsoleApplication11\\webhooksfinal.html"; // ..\\ConsoleApplication11\\ConsoleApplication11
	std::string pathjsonwork = u8"..\\ConsoleApplication11\\config.txt"; //data:text/html,<form action=http://localhost:1234 method=post><input name=key></form>
	std::ifstream fin1;
	std::ofstream fout1(pathjsonwork, std::ios::app);
	std::cout << "3\n";
	fin1.open(path1);
	char ch;
	std::string htmlres1 = "";
	if (req.method == "POST" && fout1) {
		std::string x;
		x = req.body.c_str();
		fout1 << x << '\n';
		system(u8"..\\ConsoleApplication11\\whpedito.py");
	}
	if (!(fin1.is_open())) {
		std::cout << "no connection\n";
	}
	else {
		getline(fin1, htmlres1, '\0');
	}
	if (htmlres1 != "") {
		res.set_content(htmlres1, "text/html");
	}
	fin1.close();
	fout1.close();
}

void gen_get2response(const Request& req, Response& res) {
	// Выводим на экран тело запроса
	std::cout << req.body.c_str();
	// Здесь будет ответ, пока-что взят пример из документации
	std::string str = u8R"({
		"response": {
		"text": "Здравствуйте! Это мы, хороводоведы.",
			"tts" : "Здравствуйте! Это мы, хоров+одо в+еды.",
			"end_session" : false
		},
		"session_state" : {
			"value": 10
			},
			"version" : "1.0"
	})";
	// Отправляем ответ
	res.set_content(str, "text/json; charset=UTF-8");
}

int main() {
	Server svr;                            // Создаём сервер
	svr.Get("/webhooks", gen_get1response);
	svr.Post("/webhooks", gen_get1response);
	svr.Post("/", gen_get2response);// Вызвать функцию gen_response на post запрос
	std::cout << "Start server... OK\n"; // cout использовать нельзя
	svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
}