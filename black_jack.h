#pragma once
#include <vector>
#include <string>
#include <memory>


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
		TWO = 2,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE
	};

	class Card
	{
	public:
		Card();

    	Card(CardSuit suit, CardValue value);

		void SetSuit(CardSuit suit);

		void SetValueCard(CardValue value);

		void SetPositionCArd(bool pos);

		CardValue GetValue() const;

		void FlipCard();

		void ShowCard() const;		

	private:
		CardSuit suit_;
		CardValue value_;
		bool is_open_card_;
	};

	class CardDeck
	{
	public:
		CardDeck();		

		void ShowCardDeck();

		const std::vector<Card>& GetCardDeck() const
		{
			return cards_deck_;
		}

	private:
		std::vector<Card> cards_deck_;		

		std::vector<Card> MixDeck(std::vector<Card>&& cards_deck);		

		std::vector<Card> CreateDeck();		
	};
}

namespace hand
{
	class Hand
	{
	public:
		Hand();

		void AddCard(const card::Card& card) noexcept;

		void ShowCards() const noexcept;		

		size_t GetSumCards() const noexcept;	

		void Clear() noexcept;		

	private:
		std::vector<std::unique_ptr<card::Card>> user_cards_;
	};

	class GamerUser : public Hand
	{
	public:	

		GamerUser(const std::string& name); 

	private:
		std::string name_;
	};

	class GamerAI : public Hand
	{
	public:
		GamerAI();

	private:
		std::string name_ = "AI";
	};
}

void TestBlackJack();
