#include <iostream>

class Figure
{
public:
	Figure() { };
	virtual ~Figure() = default;
	virtual void area() = 0;
};

class Parallelogram : public Figure
{
public:
	Parallelogram() { };
	~Parallelogram() override {};
	void area() override {};
};

class Circle : public Figure
{
public:
	Circle(size_t rad) : radius(rad) { };
	~Circle() {};
	void area() override
	{
		std::cout << "Площадь круга = " << (pow(radius, 2) * pi) << std::endl;
	}
private:
	double pi = 3.141592;
	size_t radius;
};

class Rectangle : public Parallelogram
{
public:
	Rectangle(size_t X, size_t Y) : sideX(X), sideY(Y) { };
	~Rectangle() {};
	void area() override
	{
		std::cout << "Площадь прямоугольника = " << (sideX * sideY) << std::endl;
	}
private:
	size_t sideX = 0;
	size_t sideY = 0;
};

class Square : public Parallelogram
{
public:
	Square(size_t X, size_t Y) : sideX(X), sideY(Y) { };
	~Square() {};
	void area() override
	{
		std::cout << "Площадь квадрата = " << (sideX * sideY) << std::endl;
	}
private:
	size_t sideX = 0;
	size_t sideY = 0;
};

class Rhombus : public Parallelogram
{
public:
	Rhombus(size_t X, size_t H) : sideX(X), sideH(H) { };
	~Rhombus() {};
	void area() override
	{
		std::cout << "Площадь ромба = " << (sideX * sideH) << std::endl;
	}
private:
	size_t sideX = 0;
	size_t sideH = 0;
};



class Car
{
public:
	Car() { std::cout << "Класс машина" << std::endl; };
	virtual ~Car() {};
	std::string company;
	std::string model;
};

class PassengerCar : public virtual Car
{
public:
	PassengerCar() { std::cout << "Класс пассажирская машина" << std::endl; };
	~PassengerCar() {};
};

class Bus : public virtual Car
{
public:
	Bus() { std::cout << "Класс автобус" << std::endl; };
	~Bus() {};
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan() { std::cout << "Класс микроавтобус" << std::endl; };
	~Minivan() {};
};


class Fraction
{
public:
	Fraction() : Numerator(0), Denominator(0) {};
	~Fraction() {};

	Fraction operator +(const Fraction& other)
	{
		Fraction tmp;
		tmp.Numerator = (this->Numerator * other.Denominator) + (other.Numerator * this->Denominator);
		tmp.Denominator = this->Denominator * other.Denominator;
		return tmp;
	};

	Fraction operator -(const Fraction& other)
	{
		Fraction tmp;
		tmp.Numerator = (this->Numerator * other.Denominator) - (other.Numerator * this->Denominator);
		tmp.Denominator = this->Denominator * other.Denominator;
		return tmp;
	};

	Fraction operator *(const Fraction& other)
	{
		Fraction tmp;
		tmp.Numerator = this->Numerator * other.Numerator;
		tmp.Denominator = this->Denominator * other.Denominator;
		return tmp;
	};

	Fraction operator /(const Fraction& other)
	{
		Fraction tmp;
		tmp.Numerator = this->Numerator * other.Denominator;
		tmp.Denominator = this->Denominator * other.Numerator;
		return tmp;
	};

	Fraction operator -() const
	{
		Fraction tmp;
		tmp.Numerator = this->Numerator * -1;
		tmp.Denominator = this->Denominator;
		return tmp;
	};

	bool operator >(const Fraction& other)
	{
		if ((this->Numerator * other.Denominator) - (other.Numerator * this->Denominator) > 0) { return true; }
		else { return false; }
	};

	bool operator <(const Fraction& other)
	{
		if ((other.Numerator * this->Denominator) - (this->Numerator * other.Denominator) > 0) { return true; }
		else { return false; }
	};

	bool operator ==(const Fraction& other)
	{
		return ((this->Numerator = other.Numerator && this->Denominator == other.Numerator));
	};
	bool operator !=(const Fraction& other)
	{
		return !((this->Numerator = other.Numerator && this->Denominator == other.Numerator));
	};




	int GetNumerator() { return Numerator; };
	int GetDenominator() { return Denominator; };
	void SetNumerator()
	{
		int val_1;
		std::cout << "Введите числитель :";
		std::cin >> val_1;
		Numerator = val_1;
	};
	void SetDenominator()
	{
		int val_2;
		std::cout << "Введите знаменатель :";
		do
		{
			std::cin >> val_2;
			if (val_2 == 0) { std::cout << "Знаменатель не может быть 0 ! пропробуйте еще раз" << std::endl; };
		} while (val_2 == 0);
		Denominator = val_2;
	};;

private:
	int Numerator;
	int Denominator;
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	std::cout << "---------========== Задание №1 ==========---------" << std::endl;

	int enter;
	size_t sideX;
	size_t sideY;
	size_t sideH;
	do
	{
		std::cout << "Выберите форму линии : 1 - кривая, 2 - прямая :";
		std::cin >> enter;

	} while (enter != 1 && enter != 2);

	if (enter == 1)
	{
		std::cout << "Введите радиус :";
		std::cin >> enter;
		Figure* figure;
		Circle circle(enter);
		figure = &circle;
		figure->area();
	}
	else
	{
		do
		{
			std::cout << "Выберите форму 1 - прямоугольник, 2 - квадрат, 3 - ромб :";
			std::cin >> enter;

		} while (enter != 1 && enter != 2 && enter != 3);
		if (enter == 1)
		{
			std::cout << "Введите размер стороны Х :";
			std::cin >> sideX;
			std::cout << "Введите размер стороны Y :";
			std::cin >> sideY;
			Figure* figure;
			Rectangle rectangle(sideX, sideY);
			figure = &rectangle;
			figure->area();
		}
		else if (enter == 2)
		{
			std::cout << "Введите размер стороны Х :";
			std::cin >> sideX;
			std::cout << "Введите размер стороны Y :";
			std::cin >> sideY;
			Figure* figure;
			Square square(sideX, sideY);
			figure = &square;
			figure->area();
		}
		else if (enter == 3)
		{
			std::cout << "Введите размер стороны :";
			std::cin >> sideX;
			std::cout << "Введите размер высоты Н :";
			std::cin >> sideH;
			Figure* figure;
			Rhombus rhombus(sideX, sideH);
			figure = &rhombus;
			figure->area();
		}
	}

	std::cout << "---------========== Задание №2 ==========---------" << std::endl;

	Minivan minivan;

	std::cout << "---------========== Задание №3 ==========---------" << std::endl;

	Fraction A;
	Fraction B;
	Fraction result;
	bool result_bool;


	std::cout << "Введите дробь №1" << std::endl;
	A.SetNumerator();
	A.SetDenominator();
	std::cout << "Дробь №1 = " << A.GetNumerator() << "/" << A.GetDenominator() << std::endl;

	std::cout << "Введите дробь №2" << std::endl;
	B.SetNumerator();
	B.SetDenominator();
	std::cout << "Дробь №2 = " << B.GetNumerator() << "/" << B.GetDenominator() << std::endl;
	
	do
	{
		std::cout << "Выберите действие над дробями : 1. математическое ; 2. унарное ; 3 логическое ";
		std::cin >> enter;
	} while (enter != 1 && enter != 2 && enter != 3);
	
	if (enter == 1)
	{
		do
		{
			std::cout << "1. сложение ; 2. вычитание ; 3. умножение ; 4. деление ";
			std::cin >> enter;
		} while (enter != 1 && enter != 2 && enter != 3 && enter != 4);
		if (enter == 1) { result = A + B; };
		if (enter == 2) { result = A - B; };
		if (enter == 3) { result = A * B; };
		if (enter == 4) { result = A / B; };
		enter = 0;
		std::cout << "результат операции = " << result.GetNumerator() << "/" << result.GetDenominator() << std::endl;
	}
	else if (enter == 2)
	{
		result = -A;
		enter = 0;
		std::cout << "результат операции = " << result.GetNumerator() << "/" << result.GetDenominator() << std::endl;
		result = -B;
		std::cout << "результат операции = " << result.GetNumerator() << "/" << result.GetDenominator() << std::endl;
	}
	else if (enter == 3)
	{
		do
		{
			std::cout << "1. сравнение ; 2. проверка неравенства ; 3. дробь №1 больше дроби №2 ; 4. дробь №1 меньше дроби №2 ";
			std::cin >> enter;
		} while (enter != 1 && enter != 2 && enter != 3 && enter != 4);
		if (enter == 1) { result_bool = (A == B); };
		if (enter == 2) { result_bool = (A != B); };
		if (enter == 3) { result_bool = (A > B); };
		if (enter == 4) { result_bool = (A < B); };

		if (result_bool) { std::cout << "результат операции ИСТИНА" << std::endl; }
		else { std::cout << "результат операции ЛОЖНО" << std::endl; }
	}
	
	   
	

}
