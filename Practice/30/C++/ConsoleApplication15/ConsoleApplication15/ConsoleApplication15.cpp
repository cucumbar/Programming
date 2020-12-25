#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

struct ItemType{
	union Item {
		struct Coins {
			int count;
		};
		struct Rune {
			int level;
			enum element {
				FIRE,
				WATER,
				AIR,
				EARTH
			};
		};
		struct Armor {
			int guard;
			int durability;
		};
		struct Weapon {
			int damage;
			int critical;
			int durability;
		};
	};

};

int main()
{
	std::string ans;
	setlocale(LC_ALL, "rus");
    std::cout << "Открыть сундук? (Yes/No)";
	std::cin >> ans;
	std::transform(ans.begin(), ans.end(), ans.begin(), [](unsigned char c) { return std::tolower(c); });
	if (ans == "y" || ans == "yes") {
	}
	else{
		std::cout << "Не хотите - как хотите.";
	}
	return 0;
}

