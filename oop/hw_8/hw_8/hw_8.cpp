#include <iostream>

template<class T>
T div(const T & val1, const T & val2) {
		if (val2 == 0) {
			throw std::runtime_error("!!! 0 !!!");
		}
		else {
			return (val1 / val2);
		}
};

class Ex
{
public:
	Ex(double val) : x(val) { };
	~Ex() = default;
	double get_x() { return x; };
private:
	double x;
};

class Bar
{
public:
	Bar() : y{0} { };
	~Bar() = default;
	void set_a(double a) {
		if ( (a + y) > 100) {
			throw Ex( a * y );
		}
		else {
			y = a;
		}
	};
private:
	double y;
};

int main()
{
	setlocale(LC_ALL, "Russian");

	try {
		int v1, v2;
		do
		{
			std::cout << "Введите перво число :";
			std::cin >> v1;
			std::cout << "Введите второе число :";
			std::cin >> v2;
			std::cout << "Первое число поделенное на второе = " << div<int>(v1, v2) << std::endl;
		} while (true);
	}
	catch (const std::runtime_error&) {
		std::cout << "Второе число = 0 , деление на 0 запрещено" << std::endl;
	}


	try {
		double n;
		Bar bar;
		do
		{
			std::cout << "Введите вещественное число :";
			std::cin >> n;
			bar.set_a(n);
		} while (true);
	}
	catch (Ex& exep) {
		std::cout << "В классе Bar a * y = " << exep.get_x() << std::endl;
	}

}
