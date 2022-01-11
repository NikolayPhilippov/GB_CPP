#include <iostream>
#include <string>

int checkInt()
{
	std::string str;
	bool flag = true;
	do {
		std::cout << "Введите числа" << std::endl;
		std::cin >> str;
		for (auto it : str) {
			if (it >= 48 && it <= 57) { //char ASCII 0 = 48 && 9 = 57
				flag = false;
			}
			else {
				flag = true;
				break;
			}
		}
	} while (flag);
	std::cout << "Корректный ввод" << std::endl;
	return std::stoi(str);
};

class ENDLL
{
	friend std::ostream& operator << (std::ostream& out, const ENDLL& endll)
	{
		out << std::endl << std::endl << std::flush;
		return out;
	};
};

int main()
{
	setlocale(LC_ALL, "Russian");
	// part 1
	int num = checkInt();

	// part 2

	ENDLL endll;
	std::cout << std::endl << "Тест 2 endl >>" << endll << " << конец теста" << std::endl;

	
}