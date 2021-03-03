#pragma once

bool is_empty(std::ifstream& input) {
	return input.peek() == std::ifstream::traits_type::eof();
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
enum class message_type { info, error, critical, fatal, warning, };
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
