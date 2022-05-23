#pragma once
#include <vector>
#include <string>

namespace card
{
	enum class CardSuit
	{
		CLUBS,
		DIAMONDS,
		WORMS,
		SPANDES
	};

	enum class CardValue
	{
		ACE = 1,
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9,
		TEN = 10,
		JACK = 10,
		QUEEN = 10,
		KING = 10
	};

	class Card
	{
	public:
		Card();

		explicit Card(CardSuit suit, CardValue value);

		void SetSuit(CardSuit suit);

		void SetValueCard(CardValue value);

		void SetPositionCArd(bool pos);

		size_t GetValue() const;

		void FlipCard();

	private:
		CardSuit suit_;
		CardValue value_;
		bool is_open_card_;
	};

	class CardsDeck
	{
	public:
		CardsDeck();

		void MixeCardDeck();

		Card GetCard();

		void ShowCardDeck();
	private:
		std::vector<Card> cards_deck_;
	};
}

class Gamer
{
public:
	Gamer();

	void TakeCard(card::Card card);

	void ShowCards();

	size_t GetSumCards();

	bool CheckWiner();

private:
	std::vector<card::Card> user_cards_;
};

class GamerUser : public Gamer
{
public:

	GamerUser();

	explicit GamerUser(const std::string& name);

private:
	std::string name_;
};

class GamerAI : public Gamer
{
public:
	GamerAI();

private:
	std::string name_ = "AI";
};

template<class User1, class User2>
class Game
{
public:
	explicit Game(User1 user1, User2 user2);

	void GameProgress();

	void FirstCardDistribution();

	void CardDistribution();

	void ProgressUser1();

	void ProgressUser2();

private:
	card::CardsDeck cards_deck_;
	User1& user1_;
	User2& user2_;
};
