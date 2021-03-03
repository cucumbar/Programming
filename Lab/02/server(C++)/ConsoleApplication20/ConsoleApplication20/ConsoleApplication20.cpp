#include <iostream>
#include <fstream>
#include <string>
#include "include/cpp_httplib/httplib.h"
#include "include/json.hpp"

bool is_empty(std::ifstream& input) {
	return input.peek() == std::ifstream::traits_type::eof();
}

void replace(std::string& temp, const std::string& start, const std::string& finish) {
	size_t pos = temp.find(start);
	while (pos != std::string::npos) {
		temp.replace(pos, start.size(), finish);
		pos = temp.find(start, pos + finish.size());
	}
}

void trim_start(std::string& strink) {
	strink.erase(strink.begin(), std::find_if(strink.begin(), strink.end(), [](const unsigned char& cha) { return !std::isspace(cha); }));
}
void trim_end(std::string& strink) {
	strink.erase(std::find_if(strink.rbegin(), strink.rend(), [](const unsigned char& cha) { return !std::isspace(cha); }).base(), strink.end());
}
void trim(std::string& strink) {
	trim_start(strink);
	trim_end(strink);
}
std::string trim_copy_start(std::string strink) {
	trim_start(strink);
	return strink;
}
std::string trim_copy_end(std::string strink) {
	trim_end(strink);
	return strink;
}
std::string trim_copy(std::string strink) {
	trim(strink);
	return strink;
}
static std::ofstream logger("log.txt");
enum class message_type { info, warning, error, critical, fatal };
bool log(const std::string& message, const message_type& type = message_type::info) {
	if (!logger.is_open()) {
		return false;
	}

	const std::time_t time = std::time(nullptr);
	std::string message_type;

	switch (type) {
	case message_type::info:
		message_type = "inf";
		break;
	default:
		message_type = "hz";
		break;
	}
	char buffer[256];
	tm timeline;
	localtime_s(&timeline, &time);
	strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &timeline);
	logger << "[" << message_type << "](" << std::string(buffer) << ") " << message << std::endl;
	return true;
}
using json = nlohmann::json;
const std::string cfg_name = "config.json";
bool try_сonfig(json& config){
	config = json();
	std::ifstream configuration(cfg_name);
	if (configuration.is_open() && !is_empty(configuration)){
		log(u8"получена новая инфа: ", message_type::info);

		try{
			configuration >> config;
		}

		catch (std::exception& ex){
			log(std::string(u8"ууу ошибка: ") + ex.what(), message_type::error);
			configuration.close();
			return false;
		}

		log(u8"получена инфа: ", message_type::info);
		configuration.close();

		return true;
	}

	if (configuration.good()){
		log(u8"ууу новая ошибка: ", message_type::error);
	}
	else{
		log(u8"харе так делать: ", message_type::warning);
	}

	config["webhooks"] = json::array();

	return false;
}
bool try_save_config(const json& config){
	std::ofstream configuration(cfg_name);

	if (configuration.is_open()){
		log(u8"получена новая инфа: ", message_type::info);
		try{
			configuration << config.dump(4);
		}
		catch (std::exception& e){
			e.what();
			configuration.close();
			return false;
		}

		configuration.close();
		return true;
	}

	log(u8"ууу ошибка: ", message_type::error);
	return false;
}

using json = nlohmann::json;
const std::string page_name = "webhooks.html";
const std::string hook_template = R"(
    <div class="form-row align-items-center">
        <div class="col">
            <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
        </div>
    
        <div class="col">
            <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
        </div>
    </div>)";

json config;

std::string generate_hook_page(){
	std::ifstream webpage_base(page_name);
	std::string webpage_res;
	if (!webpage_base.is_open()){
		log(u8"Файл шаблона не удалось открыть", message_type::error);
		return "";
	}
	std::getline(webpage_base, webpage_res, '\0');
	webpage_base.close();
	if (config.empty()){
		try_сonfig(config);
	}

	std::string hooks;
	if (!config["webhooks"].empty()){
		for (const auto& hook : config["webhooks"]){
			if (!hook.is_string()){
				log(std::string("В файле конфигурации обнаружен неверный тип ") + hook.type_name(), message_type::error);
				continue;
			}

			std::string htemplate = hook_template;
			replace(htemplate, "{Webhook URL}", hook.get<std::string>());
			hooks += htemplate;
		}
	}

	replace(webpage_res, "{webhooks_list}", hooks);
	return webpage_res;
}

void hooks_get(const httplib::Request& req, httplib::Response& response){
	response.set_content(generate_hook_page(), "text/html; charset=UTF-8");
}

bool try_del_hook(const httplib::Request& request, httplib::Response& res){
	std::string value = request.get_param_value("del");

	if (value.empty()){
		log("пустое удаление вебхука.", message_type::warning);
		return false;
	}

	log(std::string("опа del=") + value, message_type::info);

	if (config["webhooks"].empty()){
		log("вебхуков 0.", message_type::warning);
		return true;
	}

	const size_t size = config["webhooks"].size();
	for (size_t i = 0; i < size; i++){
		std::string hook = config["webhooks"][i];
		if (hook == value){
			config["webhooks"].erase(config["webhooks"].begin() + i);
			log(std::string("вебхук сгинул") + hook, message_type::info);
		}
	}

	return true;
}

bool contains_hook(const std::string& znach){
	if (config["webhooks"].empty()){
		return false;
	}
	for (const auto& item : config["webhooks"]){
		if (item.is_string() && item.get<std::string>() == znach){
			return true;
		}
	}
	return false;
}

bool try_set_hook(const httplib::Request& req, httplib::Response& res){
	std::string znach = req.get_param_value("set");
	if (znach.empty()){
		log("Пустое создание вебхука.", message_type::info);
		return false;
	}
	log(std::string("послан set=") + znach, message_type::info);
	if (contains_hook(znach)){
		log(std::string("этат виб хукер ") + znach + std::string(" уже есть, зачем ты еще шлеш?."), message_type::warning);
		return true;
	}
	config["webhooks"].push_back(znach);
	log(std::string("Добавлен виб хукер ") + znach, message_type::info);
	return true;
}

void hooks_post(const httplib::Request& request, httplib::Response& res){
	if (config.empty()){
		try_сonfig(config);
	}
	if (request.has_param("set")){
		try_set_hook(request, res);
		try_save_config(config);
	}
	else if (request.has_param("del")){
		try_del_hook(request, res);
		try_save_config(config);
	}

	res.set_content(generate_hook_page(), "text/html; charset=UTF-8");
}
using json = nlohmann::json;
enum class voice_type{
	silent,
	voice
};
static std::map<voice_type, std::string> voice_type_to_string{
	{voice_type::silent, "silent"},
	{voice_type::voice, "voice"}
};
static std::map<std::string, voice_type> voice_type_from_string{
	{"silent", voice_type::silent},
	{"voice", voice_type::voice}
};
enum class skill_type{
	basic,
	help
};
static std::map<skill_type, std::string> skill_type_to_string{
	{skill_type::basic, "default"},
	{skill_type::help, "help"}
};
static std::map<std::string, skill_type> skill_type_from_string{
	{"default", skill_type::basic},
	{"help", skill_type::help}
};
static json sessions = json::array();
const json help_button{
	{
		{"title", u8"Помощь"},
		{"hide", true}
	},
};

const json voice_button{
	{"title", u8"Говорить"},
	{"hide", true}
};

const json silent_button{
	{"title", u8"Молчать"},
	{"hide", true}
};

const json help_buttons{
	{
		{"title", u8"Молчать"},
		{"hide", true}
	},
	{
		{"title", u8"Говорить"},
		{"hide", true}
	},
	{
		{"title", u8"Помощь"},
		{"hide", true}
	},
	{
		{"title", u8"Корзина"},
		{"hide", true}
	},
	{
		{"title", u8"Выйти из помощи"},
		{"hide", true}
	},
	{
		{"title", u8"Покупка завершена"},
		{"hide", true}
	},
};
struct message{
	std::string text;
	std::string tts;
	message() = default;
	message(const std::string& text, const char* tts){
		this->text = text;
		this->tts = tts;
	}
	message(const std::string& text, const std::string& tts){
		this->text = text;
		this->tts = tts;
	}
	message(const std::string& text, const bool& voice = true){
		this->text = text;
		if (voice){
			this->tts = text;
		}
	}
};

std::map<std::string, message> help_messages{
	{u8"помощь", message(u8"Список моих способностей...")},
	{u8"молчать", message(u8"Я перестану говорить.")},
	{u8"выйти из помощи", message(u8"Обращайся еще")},
	{u8"говорить", message(u8"Я буду говорить.")},
	{u8"корзина",message(u8"Чтобы добавить в козину, скажите \"Добавить в корзину [предмет] [цена] рублей\".\nЧтобы удалить предмет из корзины, скажите \"Удалить из корзины [предмет]\".")},
	{u8"сумма", message(u8"Посчитать стоимость товаров в корзине.")},
	{u8"покупка завершена", message(u8"Ваш чек будет отправлен в клиент.")}
};
bool is_help_mode(const json& ses){
	return ses["skill_type"].get<std::string>() == skill_type_to_string[skill_type::help];
}
bool is_new_session(const json& req) {
	return req["session"]["new"].get<bool>();
}
bool is_silent_mode(const json& ses){
	return ses["voice_type"].get<std::string>() == voice_type_to_string[voice_type::silent];
}
json generate_response_al(const message& mes, const json& buttons, const json& session = nullptr, const bool& end = false){
	json response{
		{
			"response",
			{
				{"buttons", buttons},
				{"end_session", end}
			}
		},
		{"version", "1.0"}
	};
	if (!mes.text.empty()){
		response["response"]["text"] = mes.text;
	}
	if (session != nullptr){
		if (is_silent_mode(session)){
			response["response"]["buttons"].push_back(voice_button);
			response["response"]["tts"] = std::string("sil <[500]>"); 
			return response;
		}

		if (!mes.tts.empty()){
			response["response"]["tts"] = mes.tts;
		}

		response["response"]["buttons"].push_back(silent_button);
		return response;
	}

	return response;
}

json do_help(const std::string& com_line, json& session){
	if (com_line == u8"выйти из помощи"){
		session["skill_type"] = skill_type_to_string[skill_type::basic];
		return generate_response_al(help_messages[com_line], help_button, session);
	}
	return generate_response_al((help_messages.find(com_line) != help_messages.end()) ? message(help_messages[com_line].text + std::string(u8"\nЧем я могу быть полезен?")) : message(u8"Это вне моих способностей", u8"+Это вне мо+их спос+обностей"), help_buttons, session);
}

void set_response(httplib::Response& response, const message& message, const json& buttons, const json& session, const bool& end = false){
	response.set_content(generate_response_al(message, buttons, session, end).dump(4), "application/json; charset=UTF-8");
}

void if_silent(httplib::Response& response, json& session){
	session["voice_type"] = voice_type_to_string[voice_type::silent];
	set_response(response, message(u8"Молчу, молчу", false), help_button, session);
}
void if_voice(httplib::Response& response, json& session){
	session["voice_type"] = voice_type_to_string[voice_type::voice];
	set_response(response, message(u8"Хорошо.", u8"Хорош+о."), help_button, session);
}
void on_help_command(httplib::Response& response, json& session){
	const static std::string text =
		std::string(u8"Говорить/Молчать - Включает/выключает голосовой режим.\n") +
		std::string(u8"Корзина. Позволяет вести список покупок, а так же их совершать.\n") +
		std::string(u8"Помощь. Рассказывает о возможностях этого навыка.\n") +
		std::string(u8"Совершить покупку. Очищает корзину и сохраняет данные в формате эксель.\n") +
		std::string(u8"Сумма. Считает сумму товаров и называет её вам.\n") +
		std::string(u8"О чём рассказать подробнее?");

	session["skill_type"] = skill_type_to_string[skill_type::help];
	set_response(response, message(text), help_buttons, session);
}

void if_empty(httplib::Response& res, json& session){ // pustaya korzina
	if (session["cart"].empty()){
		set_response(res, message(u8"Корзина и так пуста.", u8"Корз+ина и так пуста."), help_button, session);
		return;
	}
	session.erase("cart");
	session["cart"] = json::array();
	set_response(res, message(u8"Корзина пуста.", u8"Корз+ина пуста."), help_button, session);
}

void what_inside(httplib::Response& res, json& session){
	if (session["cart"].empty()){
		set_response(res, message(u8"Ваша корзина пуста.", u8"Ваша корзина пуста."), help_button, session);
		return;
	}
	std::string text = u8"На данный момент в вашей корзине:";
	for (auto& item : session["cart"]){
		const int price = item["price"].get<int>();
		text += "\n" + item["item"].get<std::string>() + u8" что стоит " + std::to_string(price);
		if (price >= 10 && price <= 20 || price % 10 == 0){
			text.append(u8" рублей,");
		}
		else if (price % 10 == 1){
			text.append(u8" рубль,");
		}
		else if (price % 10 > 0 && price % 10 < 5){
			text.append(u8" рубля,");
		}
		else{
			text.append(u8" рублей,");
		}
	}
	text[text.size() - 1] = '.';
	set_response(res, message(text), help_button, session);
}

bool send_try(const std::string& id, json& ses){ // po pokupke otpravlenie
	try{
		const json cart{
			{"user_id", id},
			{"cart", ses["cart"]}
		};
		json cfg;
		try_сonfig(cfg);
		for (std::string hook : cfg["webhooks"]){
			trim(hook);
			replace(hook, "https://", "http://");
			if (hook.find("http://") != 0){
				continue;
			}
			if (hook.find('/', 7) == std::string::npos){
				hook.push_back('/');
			}

			const size_t index = hook.find('/', static_cast<std::string>("http://").size());

			if (index == std::string::npos){
				log(std::string(u8"При отправке запроса было обнаружена ошибка вебхука: ") + hook, message_type::warning);
				continue;
			}

			httplib::Client client(hook.substr(0, index).c_str());
			client.Post(hook.substr(index, std::string::npos).c_str(), cart.dump(4), "application/json; charset=UTF-8");
			log(std::string(u8"Отправляется запрос на ") + hook, message_type::info);
		}

		return true;
	}
	catch (const std::exception& e){
		log(std::string(u8"Произошел ужас: ") + e.what(), message_type::critical);
		return false;
	}
}

void if_sold(httplib::Response& response, json& session, std::string& id){
	if (session["cart"].empty()){
		set_response(response, message(u8"Ваша корзина пуста.", u8"Ваша корзина пуста."), help_button, session);
		return;
	}
	if (!send_try(id, session)){
		set_response(response, message(u8"Какая то ошибка,\nПопробуйте еще раз."), help_button, session);
		return;
	}
	session.erase("cart");
	session["cart"] = json::array();
	set_response(response, message(u8"Заходите ещё!", u8"Заход+ите ещ+ё!"), help_button, session, true);
}
void if_summ(httplib::Response& response, json& session, const json& request){
	size_t size = request["request"]["nlu"]["tokens"].size();
	size_t fullprice = 0;
	for (auto& item : session["cart"]){
		fullprice += item["price"].get<size_t>();
	}
	if (fullprice <= 0){
		set_response(response, message(u8"У вас корзина пуста.", u8"У вас корз+ина пуст+а."), help_button, session);
		return;
	}
	std::string text = u8"В общей сумме у вас товаров на " + std::to_string(fullprice);
	std::string tts = u8"В +общей с+умме у вас тов+аров на " + std::to_string(fullprice);
	if (fullprice >= 10 && fullprice <= 20 || fullprice % 10 == 0){
		text.append(u8" рублей.");
		tts.append(u8" рубл+ей.");
	}
	else if (fullprice % 10 == 1){
		text.append(u8" рубль.");
		tts.append(u8" рубль.");
	}
	else if (fullprice % 10 > 0 && fullprice % 10 < 5){
		text.append(u8" рубля.");
		tts.append(u8" рубл+я.");
	}
	else{
		text.append(u8" рублей.");
		tts.append(u8" рубл+ей.");
	}
	set_response(response, message(text, tts), help_button, session);
}
void if_adding(httplib::Response& response, json& ses, const json& request)
{
	const size_t size = request["request"]["nlu"]["tokens"].size();
	std::string item_name;
	size_t price = 0;
	int index = 0;
	bool ns_index = false;
	for (auto item : request["request"]["nlu"]["entities"]){
		if (item["type"].get<std::string>() == "YANDEX.NUMBER"){
			index = item["tokens"]["start"];
			const auto val = item["value"].get<long long int>();
			if (val <= 0){
				set_response(response, message(u8"Каждому придется поплатиться. И Вам тоже.", u8"К+аждому прид+ется поплат+иться. И Вам т+оже."), help_button, ses);
				return;
			}
			price = val;
			ns_index = true;
			break;
		}
	}
	if (size == 3){
		set_response(response, message(u8"Не указано что добавить в корзину."), help_button, ses);
		return;
	}
	if (!ns_index){
		set_response(response, message(u8"Не указана цена товара"), help_button, ses);
		return;
	}
	if (index == 3){
		set_response(response, message(u8"Не указано название товара"), help_button, ses);
		return;
	}
	for (int i = 3; i < index; ++i){
		item_name.append(request["request"]["nlu"]["tokens"][i].get<std::string>());

		if (i < index - 1){
			item_name.append(" ");
		}
	}
	const json item{
		{"item", item_name},
		{"price", price}
	};
	ses["cart"].push_back(item);
	set_response(response, message(u8"Хорошо.", u8"Хорош+о"), help_button, ses);
}
void if_deleting(httplib::Response& response, json& session, const json& request){
	const size_t size = request["request"]["nlu"]["tokens"].size();
	std::string item_name;
	for (size_t i = 3; i < size; ++i){
		item_name.append(request["request"]["nlu"]["tokens"][i].get<std::string>());
		item_name.append(" ");
	}
	if (item_name.empty()){
		set_response(response, message(u8"Ещё раз, что пожелаете удалить?"), help_button, session);
		return;
	}
	item_name.pop_back();
	for (size_t i = 0; i < session.size(); i++){
		auto& item = session[i];
		if (item["item"].get<std::string>() == item_name){
			session["cart"].erase(session["cart"].begin() + i);
			set_response(response, message(u8"Устранение успешно.", u8"Устран+ение усп+ешно."), help_button, session);
			return;
		}
	}
	log(u8"Предмет не найден", message_type::info);
	set_response(response, message(u8"Такого предмета в вашей корзине нету.", u8"Так+ого предмета в в+ашей корз+ине н+ету."), help_button, session);
}
void if_def(httplib::Response& response, json& session){
	set_response(response, message(u8"Я не понимаю, что Вы приказываете", u8"Я не поним+аю, что Вы прик+азываете"), help_button, session);
}
json* find_session(const std::string& ID){
	for (auto& session : sessions){
		if (session["user_id"].get<std::string>() == ID){
			return &session;
		}
	}

	return nullptr;
}
void on_new_session(httplib::Response& res, const std::string& id){
	json* session_ptr = find_session(id);
	if (session_ptr == nullptr){
		const json session{
			{"user_id", id},
			{"skill_type", skill_type_to_string[skill_type::basic]},
			{"voice_type", voice_type_to_string[voice_type::voice]},
			{"cart", json::array()}
		};
		sessions.push_back(session);
		set_response(res, message(u8"Здравствуйте! Я помогу вам с покупками.", u8"Здр+авствуйте! Я помог+у вам с пок+упками."), help_button, session);
		return;
	}

	json& session = *session_ptr;
	session["skill_type"] = skill_type_to_string[skill_type::basic];
	session["voice_type"] = voice_type_to_string[voice_type::voice];
	set_response(res, message(u8"Здравствуйте! Я помогу вам с покупками.", u8"Здр+авствуйте! Я помог+у вам с пок+упками."), help_button, session);
}

void alice_stealin(const httplib::Request& req, httplib::Response& res){
	json request = json::parse(req.body);
	std::string id = request["session"]["application"]["application_id"].get<std::string>();
	json response;
	json* session_ptr = find_session(id);
	if (is_new_session(request)){
		on_new_session(res, id);
		return;
	}
	if (session_ptr == nullptr){
		set_response(res, message(u8"Извините, произошла ошибка. Возможно сессия была сброшена.", u8"Извин+ите, произошл+а ош+ибка. Возможно сессия была сброшена."), help_button,nullptr, true);
		return;
	}
	json& session = *session_ptr;
	const std::string command = request["request"]["command"].get<std::string>();
	if (is_help_mode(session)){
		res.set_content(do_help(command, session).dump(4), "application/json; charset=UTF-8");
		return;
	}

	if (command == u8"молчать"){
		if_silent(res, session);
	}
	else if (command == u8"говорить"){
		if_voice(res, session);
	}
	else if (command == u8"помощь"){
		on_help_command(res, session);
	}
	else if (command == u8"очистить корзину" || command == u8"очисти корзину"){
		if_empty(res, session);
	}
	else if (command == u8"что в корзине" || command == u8"корзина"){
		what_inside(res, session);
	}
	else if (command == u8"покупка завершена" || command == u8"завершить"){
		if_sold(res, session, id);
	}
	else if (command == u8"цена" || command == u8"сумма" || command == u8"стоимость"){
		if_summ(res, session, request);
	}
	else if (command.find(u8"добавить в корзину") == 0 || command.find(u8"добавь в корзину") == 0){
		if_adding(res, session, request);
	}
	else if (command.find(u8"удалить из корзины") == 0 || command.find(u8"удали из корзины") == 0 || command. find(u8"убрать из корзины") == 0 || command.find(u8"убери из корзины") == 0){
		if_deleting(res, session, request);
	}
	else{
		if_def(res, session);
	}
}
using json = nlohmann::json;
using namespace httplib;
const std::string host{ "localhost" };
int port{ 3000 };
int main(){
	Server srv;
	srv.Get("/webhooks", hooks_get);
	srv.Post("/webhooks", hooks_post);
	srv.Post("/alice", alice_stealin);
	log(std::string("Server ") + host + std::string(u8":") + std::to_string(port), message_type::info);
	srv.listen("localhost", port);
}