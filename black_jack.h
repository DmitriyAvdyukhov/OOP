#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

namespace error
{
	class StopGame
	{};
}

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

		void SetSuit(CardSuit suit) noexcept;

		void SetValueCard(CardValue value) noexcept;

		void SetPositionCArd(bool pos) noexcept;

		CardValue GetValue() const noexcept;

		void FlipCard() noexcept;

		void ShowCard(std::ostream& out = std::cout) const noexcept;

		bool GetIsOpenCard() const noexcept;

	private:
		CardSuit suit_;
		CardValue value_;
		bool is_open_card_;
	};

	std::ostream& operator<< (std::ostream& out, const Card& c);
	
	class CardDeck
	{
	public:
		using Iterator = std::vector<Card>::iterator;		

		CardDeck();		

		void ShowCardDeck(std::vector<Card>& cards_deck) const noexcept;

		std::vector<Card>& GetCardDeck() noexcept;
		
		Iterator GetIter() noexcept;

		void ShiftIt();

		void ShuffleDeck() noexcept;

		void operator()() noexcept;		

	private:
		Iterator it_; 
		std::vector<Card> cards_deck_;	

		std::vector<Card> CreateDeck();		
	};
}// namespace card

namespace hand
{
	class Hand
	{
	public:
		Hand();

		void AddCard(card::Card card) noexcept;

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

} //------------namespace hand

namespace game
{
	class Game
	{
	private:
		card::CardDeck card_deck_;
		std::shared_ptr<hand::GamerAI> diller_;
		std::vector<std::shared_ptr<hand::GamerUser>> players_;

	public:
		Game(const std::vector<std::string>& players);

		void Play();

	private:
		template<class Ptr>
		void Deal(Ptr& user);

		void AddItinationalCards(std::shared_ptr<hand::GamerUser>& player);

		void AddItinationalCards(std::shared_ptr<hand::GamerAI>& player);

		void ProcessGame();

		void GameRaund();

		void PrintPlayrsCards() const;

		void FirstDealCards();

		void ClearPlayers();

		std::vector<std::shared_ptr<hand::GenericPlayer>> CreateVectorWiners() const noexcept;

		void ShowWinersAndLose(std::vector<std::shared_ptr<hand::GenericPlayer>> winers) const noexcept;

		void Winers() const noexcept;
	};

	template<class Ptr>
	void Game::Deal(Ptr& user)
	{
		if (card_deck_.GetIter() != (card_deck_.GetCardDeck().end()))
		{
			user->AddCard(*(card_deck_.GetIter()));
			card_deck_.ShiftIt();
		}
		else
		{
			throw error::StopGame();
		}
	}

 } // --------------namespace game

void GameBlackJack();
