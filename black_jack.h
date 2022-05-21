#pragma once
#include <vector>
#include <string>

namespace card
{
	enum class CardSuit;

	enum class CardValue;	

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

	class CardDeck
	{
	public:
		CardDeck() = default;

		void MixeCardDeck();

		Card GetCard();

		void ShowCardDeck();
	private:
		std::vector<Card> card_deck_;
	};

	class Gamer
	{
	public:
		Gamer();

		void TakeCard(Card card);

		void ShowCards();

		size_t GetSumCards();

		bool CheckWiner();

	private:

		std::vector<Card> user_card_;
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
		CardDeck card_deck_;
		User1& user1_;
		User2& user2_;
	};
}