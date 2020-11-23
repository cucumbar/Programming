#include <iostream>
#include <fstream>
#include "include/cpp_httplib/httplib.h"
#include <string>
using namespace httplib;
//using namespace fstream;
//using namespace string;

// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
	std::string path = "C:\\Users\\Михондрус\\myGitRepoCloned\\Programming\\Lab\\01\\server(C++)\\ConsoleApplication1\\ConsoleApplication1\\WidgetPage.html"; //УЗНАТЬ КАК ПОЛЬЗОВАТЬСЯ ОТНОСИТЕЛЬНЫМ ПУТЕМ
	std::ifstream fin;
	fin.open(path);
	char ch;
	std::string htmlres = "";
	if (!(fin.is_open())) {
		std::cout << "нет";
	}
	else {
		while (fin.get(ch)) {
			htmlres += ch;
		}
	}
	res.set_content(htmlres, "text/html");
	fin.close();
}

int main() {
	Server svr;                    // Создаём сервер (пока что не запущен)
	svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратится к корню "сайта"
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 1234
}