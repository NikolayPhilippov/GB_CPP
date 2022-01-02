#include <iostream>
#include <string>

template <class T>
class Pair1
{
private:
	T value1;
	T value2;
public:
	Pair1(const T& val1, const T& val2) : value1(val1), value2(val2) { };
	~Pair1() = default;
	const T& first() { return value1; };
	const T& second() { return value2; };
};


template <class T1, class T2>
class Pair
{
protected:
	T1 value1;
	T2 value2;
public:
	Pair(const T1& val1, const T2& val2) : value1(val1), value2(val2) {};
	~Pair() = default;
	const T1& first() { return value1; };
	const T2& second() { return value2; };

};

template <class H>
class StringValuePair : public Pair<std::string, H>
{
public:
	StringValuePair(const std::string& str, const H& val2) : Pair<std::string, H>(str, val2) { };
};

int main()
{
	Pair1<int> p1(50, 65);
	std::cout << "pair int : " << p1.first() << " / " << p1.second() << std::endl;
	Pair1<double> p2(50.55, 65.66);
	std::cout << "pair double : " << p2.first() << " / " << p2.second() << std::endl;

	Pair<int, double> p3(50, 65.66);
	std::cout << "pair int / double : " << p3.first() << "  /" << p3.second() << std::endl;
	Pair<double, int> p4(50.55, 65);
	std::cout << "pair double / int : " << p4.first() << " / " << p4.second() << std::endl;

	StringValuePair<int> svp("Five", 5);
	std::cout << "pair const string / int : " << svp.first() << " / " << svp.second() << std::endl;

}
