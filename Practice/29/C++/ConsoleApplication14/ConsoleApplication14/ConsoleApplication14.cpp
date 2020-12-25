#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>

std::string discips[] = { "math", "phys", "hist", "prog" };

struct Student{
	std::string name;
	
	std::map<std::string, int>::iterator disciplinesITER;
	std::map<std::string, int> disciplines;
	int group;
	int n;

	void initialize(){
		std::cout << "imya uchenika: ";
		std::cin >> name;
		std::cout << "klass uchenika: ";
		std::cin >> group;

		for (int i = 0; i < 4; i++){
			std::cout << discips[i] << " grade is: ";
			std::cin >> disciplines[discips[i]];
		}
		std::cout << '\n';
	}

};

std::ostream& operator<<(std::ostream& oout, Student stud){

	oout << "+------------+-------+------+------+------+------+";
	oout << '\n';
	oout << "| Name       | Group |";

	for (int i = 0; i < 4; i++){
		oout << std::setw(6) << discips[i] << "|";
	}

	oout << '\n';
	oout << "+------------+-------+------+------+------+------+";
	oout << '\n';


	oout << '|' << std::setw(12) << stud.name << '|' << std::setw(7) << stud.group << '|';

	for (stud.disciplinesITER = stud.disciplines.begin(); stud.disciplinesITER != stud.disciplines.end(); stud.disciplinesITER++){
		oout << std::setw(6) << stud.disciplinesITER->second << '|';
	}

	oout << '\n';
	oout << "+------------+-------+------+------+------+------+";
	oout << '\n';
	return oout;
}


int main(){
	int n;
	std::cout << "Skolko nado uchenikov?\n";
	std::cin >> n;

	std::vector<Student> students(n);
	for (auto& student : students)
		student.initialize();

	std::cout << students[0];
}