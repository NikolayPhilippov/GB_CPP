#include <iostream>
#include <string>


template<class T>
T div(const T & val1, const T & val2)
{
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
	void set_a(double a)
	{
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

const int SIZE = 10;

class RobotException
{
public:
	RobotException(int curX, int curY, int newX, int newY) : currentPosX(curX), currentPosY(curY), newPosX(newX), newPosY(newY), message("") { };
	~RobotException() = default;

	const std::string& GetInfo()
	{
		return message;
	};

	const std::string& GetCoordinates()
	{
		coords = "Ход из ( " + std::to_string(currentPosX) + " , " + std::to_string(currentPosY) +
					" ) в новую точку ( " + std::to_string(newPosX) + " , " + std::to_string(newPosY) + " )";
		return coords;
	};

protected:
	int currentPosX{ 0 };
	int currentPosY{ 0 };
	int newPosX{ 0 };
	int newPosY{ 0 };
	std::string message{};
	std::string coords{};
};

class OffTheField : public RobotException
{
public:
	OffTheField(int curX, int curY, int newX, int newY) : RobotException(curX, curY, newX, newY)
	{
		if (newPosX > SIZE || newPosX < 1) {
			message = "Ошибка: выход за граници по оси Х ";
		};

		if (newPosY > SIZE || newPosY < 1) {
			message = "Ошибка: выход за граници по оси Y ";
		};

		GetCoordinates();
	};

	~OffTheField() = default;
};

class IllegalCommand : public RobotException
{
public:
	IllegalCommand(int curX, int curY, int newX, int newY) : RobotException(curX, curY, newX, newY)
	{
		if (std::abs(currentPosX - newPosX) > 1) {
			message = "Ошибка: смещение по оси Х больше чем 1 ";
		}

		if (std::abs(currentPosY - newPosY) > 1) {
			message = "Ошибка: смещение по оси Х больше чем 1 ";
		}

		if ((currentPosX == newPosX) && (currentPosY == newPosY)) {
			message = "Ошибка: ваше местоположение уже здесь ";
		};

		GetCoordinates();
	};

	~IllegalCommand() = default;
};

class Robot
{
public:
	Robot(int x = (SIZE / 2), int y = (SIZE / 2)) : posX(x), posY(y)
	{
		std::cout << "Начаная точка координат ( " << posX << " , " << posY << " )" << std::endl;
	};

	~Robot() = default;
	
	void Move(int x, int y)
	{
		if ((abs(posX - x) > 1) || (abs(posY - y) > 1) || (posX == x && posY == y))
			throw IllegalCommand(posX, posY, x, y);
		if ((x > SIZE) || (x < 1) || (y > SIZE) || (y < 1))
			throw OffTheField(posX, posY, x, y);

		std::cout << "Ход из ( " << posX << " , " << posY << " ) в новую точку ( " << x << ", " << y << " )" << std::endl;

		posX = x;
		posY = y;
	};

private:
	int posX;
	int posY;
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
	};

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
	};

	int x = 0;
	int y = 0;
	bool exitFlag = true;
	Robot robot;

	std::cout << "Координаты поля для хода по Х 1..10 по Y 1..10" << std::endl;
	std::cout << "шаг перемещения 1 в любую сторону (король в шахматах)" << std::endl;
	std::cout << "выходить за пределы поля - нельзя" << std::endl;
	std::cout << "для выхода из программы введите 0 в Х и Y координатах" << std::endl;
	
	while (exitFlag) {

		std::cout << "Введите позицию по координатам Х : ";
		std::cin >> x;
		std::cout << "Введите позицию по координатам Y : ";
		std::cin >> y;

		if (x == 0 && y == 0) {
			exitFlag = false;
			continue;
		}

		try {
			robot.Move(x, y);
		}
		catch (IllegalCommand& exIlleg) {
			std::cout << exIlleg.GetInfo() << std::endl;
		}
		catch (OffTheField& exFail) {
			std::cout << exFail.GetInfo() << std::endl;
		}
	};

};
