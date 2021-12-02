#include <iostream>

enum class suitCard:int
{
	Spades,
	Hearts,
	Clubs,
	Diamonds
};

enum class valueCard:int
{
	Ace = 1,
	King = 10,
	Queen = 10,
	Jack = 10,
	Ten = 10,
	Nine = 9,
	Eight = 8,
	Seven = 7,
	Six = 6,
	Five = 5,
	Four = 4,
	Three = 3,
	Two = 2
};


class Card
{
public:
	Card() = default;
	~Card() {};

	valueCard GetValue() {
		return value;
	};

	bool Flip() {
		return (isOpened = !isOpened);
	};

private:
	suitCard suit;
	valueCard value;
	bool  isOpened = false;
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

}

