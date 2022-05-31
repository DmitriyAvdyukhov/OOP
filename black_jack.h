#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

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

		void ShowCard(std::ostream& out = std::cout) const;

		bool GetIsOpenCard() const;		

	private:
		CardSuit suit_;
		CardValue value_;
		bool is_open_card_;
	};

	std::ostream& operator<< (std::ostream& out, const Card& c);
	
	class CardDeck
	{
	public:
		CardDeck();		

		void ShowCardDeck();

		const std::vector<Card>& GetCardDeck() const;
		
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

		const std::vector<std::unique_ptr<card::Card>>& GetCards() const;		

	private:
		 std::vector<std::unique_ptr<card::Card>> user_cards_;
	};

	class GenericPlayer : public Hand
	{
	public:
		GenericPlayer(const std::string& name);

		virtual bool IsHitting() const = 0;

		bool IsBoosted() const;		

		void Bust(std::ostream& out = std::cout) const;

		std::string GetName() const;		
		
		void Win()const;

		void Lose() const;

		void Push() const;
		
	private:
		std::string name_;
	};

	std::ostream& operator<< (std::ostream& out, const GenericPlayer& g);	
	
	class GamerUser : public GenericPlayer
	{
	public:	
		GamerUser(const std::string& name); 

		bool IsHitting() const  override;
		
	};
	
	class GamerAI : public GenericPlayer
	{
	public:
		GamerAI();	

		bool IsHitting() const override;	

		void FlipFirstCard();		
	};
}

void TestBlackJack();
