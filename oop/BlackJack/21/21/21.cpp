#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Card
{
	friend std::ostream& operator << (std::ostream& out, const Card& aCard);

public:

	enum rank
	{
		ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7,
		eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10
	};

	enum suit 
	{
		spades = 1, clubs = 2, hearts =3, diamonds =4
	//	"♠"			"♣"		   "♥"		  "♦"
	};

	Card(rank r, suit s, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { };

	void Flip()
	{
		m_IsFaceUp = !(m_IsFaceUp);
	};

	int GetValue() const
	{
		int value = 0;
		if (m_IsFaceUp)
		{
			value = m_Rank;
		}
		return value;
	};


private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

class Hand
{
public:
	Hand()
	{
		m_Cards.reserve(7); 
	};

	~Hand() { Clear(); };
	
	void AddCard(Card* ptrCard)
	{
		m_Cards.push_back(ptrCard);
	};

	void Clear()
	{
		for (auto it : m_Cards) {
			delete it;
			it = NULL;
		}
		m_Cards.clear();
	};

	int GetTotal() const 
	{
		if (m_Cards.empty()) {
			return 0;
		}

		if (m_Cards[0]->GetValue() == 0) {
			return 0;
		}

		int total{ 0 };
		
		for (auto const it : m_Cards) {
			total += it->GetValue();
		}

		bool containsAce = false;
		for (const auto it : m_Cards) {
			if (it->GetValue() == Card::ace) {
				containsAce = true;
			}
		}

		if (containsAce && (total <= 11)) {
			total += 10;
		}
		return total;
	};

protected:
	std::vector<Card*> m_Cards;

};


class GenericPlayer : public Hand
{
	friend std::ostream& operator << (std::ostream& out, const GenericPlayer& aGenericPlayer);

public:

	GenericPlayer(const std::string& name) : m_Name(name) { };

	virtual ~GenericPlayer() {};
	
	virtual bool IsHitting() const = 0;
	
	bool IsBusted() const
	{
		return (GetTotal() > 21);
	};

	void Bust() const 
	{
		std::cout << m_Name << " busts :( " << std::endl;
	};

protected:
	std::string m_Name;
};

class Player : public GenericPlayer
{
public:

	Player(const std::string& name = "") : GenericPlayer(name) { };
	virtual ~Player() { };
	
	virtual bool IsHitting() const 
	{
		std::cout << m_Name << ", do you want a hit? Y or N : ";
		char response;
		std::cin >> response;
		return (response == 'y' || response == 'Y');
	};
	
	void Win() const
	{
		std::cout << m_Name << " wins :)" << std::endl;
	};
	
	void Lose() const
	{
		std::cout << m_Name << " loses :(" << std::endl;
	};

	void Push() const 
	{
		std::cout << m_Name << " pushes :o" << std::endl;
	};
};

class House : public GenericPlayer
{
public:

	House(const std::string & name = "House") : GenericPlayer(name) { };
	virtual ~House() { };
	virtual bool IsHitting() const
	{
		return (GetTotal() <= 16);
	};

	void FlipFirstCard() 
	{
		if ( !(m_Cards.empty()) )	{
			m_Cards[0]->Flip();
		}
		else {
			std::cout << "No card to flip!" << std::endl;
		}
	};
};

class Deck : public Hand
{
public:

	Deck();
	virtual ~Deck() { };
	void Populate();
	void Shuffle();
	void Deal(Hand& aHend);
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
	m_Cards.reserve(52);
	Populate();
};

void Deck::Populate()
{
	Clear();
	for (int s = Card::spades; s <= Card::diamonds; ++s) {
		for (int  r = Card::ace; r <=  Card::king; ++r) {
			AddCard(new Card(static_cast<Card::rank>(r),static_cast<Card::suit>(s)));
		}
	}
};

void Deck::Shuffle()
{
	std::random_shuffle(m_Cards.begin(), m_Cards.end());
};

void Deck::Deal(Hand& aHend)
{
	if (!m_Cards.empty()) {
		aHend.AddCard(m_Cards.back());
		m_Cards.pop_back();
	}
	else {
		std::cout << "Out of cards. Unable to deal";
	}
};

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
	std::cout << std::endl;

	while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
	{
		Deal(aGenericPlayer);
		std::cout << aGenericPlayer << std::endl;

		if (aGenericPlayer.IsBusted())
		{
			aGenericPlayer.Bust();
		}
	}
}

class Game
{
public:
	Game(const std::vector<std::string>& names);
	~Game() { };
	void Play();

private:
	Deck m_Deck;
	House m_House;
	std::vector<Player> m_Players;
};

Game::Game(const std::vector<std::string>& names)
{
	for (auto it = names.begin(); it != names.end(); ++it) {
		m_Players.push_back(Player(*it));
	}
	srand(static_cast<unsigned int>(time(0)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}

void Game::Play()
{
	for (int i = 0; i < 2; ++i) {
		for (auto it = m_Players.begin(); it != m_Players.end(); ++it) {
			m_Deck.Deal(*it);
		}
		m_Deck.Deal(m_House);
	}
	for (auto  it = m_Players.begin(); it != m_Players.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << m_House  << " " << std::endl;

	for (auto it = m_Players.begin(); it != m_Players.end(); ++it) {
		m_Deck.AdditionalCards(*it);
	}
	m_House.FlipFirstCard();
	std::cout << std::endl << m_House;
	m_Deck.AdditionalCards(m_House);
	if (m_House.IsHitting()) { 
		for (auto it = m_Players.begin(); it != m_Players.end(); ++it) {
			if ( ! (it->IsBusted()) ) {
				it->Win();
			}
		}
	}
	else {
		for (auto it = m_Players.begin(); it != m_Players.end(); ++it) {
			if (!it->IsBusted()) {
				it->Win();
			}
			else if (it->GetTotal() < m_House.GetTotal()) {
					it->Lose();
			}
			else
			{
				it->Push();
			}
		}
	}
	for (auto it = m_Players.begin(); it != m_Players.end(); ++it) {
		it->Clear();
	}
	m_House.Clear();
};


std::ostream& operator << (std::ostream& out, const Card& aCard)
{
	const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const std::string SUITS[] = { "s", "c", "h", "d" };

	if (aCard.m_IsFaceUp) {
		out << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
	}
	else {
		out << "XX";
	}

	return out;
};

std::ostream& operator << (std::ostream& out, const GenericPlayer& aGenericPlayer)
{
	out << aGenericPlayer.m_Name << ": \t";
	if (!aGenericPlayer.m_Name.empty()) {
		for (auto it : aGenericPlayer.m_Cards) {
			out << *it << " \t";
		}
		if (aGenericPlayer.GetTotal() != 0) {
			std::cout << "(" << aGenericPlayer.GetTotal() << ")";
		}
	}
	else {
		out << "(empty)";
	}
	return out;
};


int main()
{
	setlocale(LC_ALL, "Russian");
	
	int players{ 0 };
	std::vector<std::string> names;
	std::string name;
	char gotoPlay = 'y';

	while ((players < 1) || (players > 7))
	{
		std::cout << "How many players ? 1-7 = ";
		std::cin >> players;
	}

	for (size_t i = 0; i < players; ++i) {
		std::cout << "Enter name player ";
		std::cin >> name;
		names.push_back(name);
	}

	std::cout << std::endl << std::endl;

	Game game(names);
	while ((gotoPlay != 'n') || (gotoPlay != 'N')) {
		game.Play();
		std::cout << std::endl << "let's play again ? Y or N : ";
		std::cin >> gotoPlay;
	}
	return 0;
}

