#include <iostream>
#include <fstream>
#include "include/cpp_httplib/httplib.h"
#include <string>
using namespace httplib;
//using namespace fstream;
//using namespace string;

// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
	std::string path1 = "..\\ConsoleApplication1\\WidgetPage.html"; //server(C++)\\ConsoleApplication1\\ConsoleApplication1\\.
	std::string path2 = "WidgetPage.html";
	std::ifstream fin1, fin2;
	fin1.open(path1);
	fin2.open(path2);
	char ch;
	std::string htmlres1 = "";
	if (!(fin1.is_open())) {
		std::cout << "no connection";
	}
	else {
		while (fin1.get(ch)) {
			htmlres1 += ch;
		}
	}
	std::string htmlres2 = "";
	if (!(fin2.is_open())) {
		std::cout << "no connection";
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
	fin1.close();
	fin2.close();
}

int main() {
	Server svr;                    // Создаём сервер (пока что не запущен)
	svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратится к корню "сайта"
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 1234
}