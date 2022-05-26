#include "black_jack.h"
#include <iostream>

#include <ctime>

namespace card 
{
	Card::Card()
		:suit_(CardSuit::CLUBS), value_(CardValue::ACE), is_open_card_(false) 
	{}

	Card::Card(CardSuit suit, CardValue value)
	: suit_(suit), value_(value), is_open_card_(false)
	{}

	void Card::SetSuit(CardSuit suit)
	{
		suit_ = suit;
	}

	void Card::SetValueCard(CardValue value)
	{
		value_ = value;
	}

	void Card::SetPositionCArd(bool pos)
	{
		is_open_card_ = pos;
	}

	CardValue Card::GetValue() const
	{
		return value_;
	}

	void Card::FlipCard()
	{
		if (is_open_card_)
		{
			is_open_card_ = false;
		}
		else
		{
			is_open_card_ = true;
		}
	}

	void Card::ShowCard() const
	{		
		switch (suit_)
		{
		case CardSuit::CLUBS:
			std::cout << "CLUBS ";
			break;
		case CardSuit::DIAMONDS:
			std::cout << "DIAMONDS ";
			break;
		case CardSuit::WORMS:
			std::cout << "WORMS ";
			break;
		case CardSuit::SPANDES:
			std::cout << "SPANDES ";
			break;
		}
		if (value_ == CardValue::ACE 
			|| value_ == CardValue::JACK 
			|| value_ == CardValue::QUEEN 
			|| value_ == CardValue::KING)
		{
			switch (value_)
			{
			case CardValue::ACE:
				std::cout << "A";
				break;
			case CardValue::JACK:
				std::cout << "J";
				break;
			case CardValue::QUEEN:
				std::cout << "Q";
				break;
			case CardValue::KING:
				std::cout << "K";
				break;
			}
		}
		else
		{
			std::cout << static_cast<int>(value_);
		}
	}

	CardDeck::CardDeck()
	{
		cards_deck_ = MixDeck(CreateDeck());
	}

	std::vector<Card> CardDeck::CreateDeck()
	{
		const size_t count_deck_cards = 52;
		std::vector<Card> cards_deck;
		for (size_t i = 0; i < count_deck_cards; ++i)
		{
			int num = (i % 13) + 2;
			CardSuit su = CardSuit(i / 13);
			cards_deck.push_back(card::Card(su, static_cast<CardValue>(num)));
		}
		return cards_deck;
	}

	
	void CardDeck::ShowCardDeck()
	{
		int i = 0;
		for (const auto& card : cards_deck_)
		{
			card.ShowCard();
			std::cout << " ";
			if (!((i + 1) % 13))
			{
				std::cout << std::endl;
			}
			++i;
		}
		std::cout << std::endl;
	}	

	std::vector<Card> CardDeck::MixDeck(std::vector<Card>&& cards_deck)
	{
		srand(time(NULL)); // инициализируем генератор случайных чисел
		const size_t count_deck_cards = 52;
		for (size_t i = 0; i < count_deck_cards / 2; ++i)
		{
			int k = rand() % 52; // выбираем случайную карту
			Card temp = cards_deck[i]; // и меняем ее с текущей
			cards_deck[i] = cards_deck[k];
			cards_deck[k] = temp;
		}
		return cards_deck;
	}	
}

namespace hand
{
	Hand::Hand() = default; 

	void Hand::AddCard(const card::Card& card) noexcept
	{
		user_cards_.push_back(std::make_unique<card::Card>(card));
	}

	void Hand::ShowCards() const noexcept
	{
		if (!user_cards_.size())
		{
			std::cout << "No cards";
		}
		bool is_first = true;
		for (const auto& card : user_cards_)
		{			
			if (is_first)
			{
				card->ShowCard();
				is_first = false;
			}
			else
			{
				std::cout << ", ";
				card->ShowCard();
			}			
		}
		std::cout << std::endl;
	}

	size_t Hand::GetSumCards() const noexcept
	{
		size_t result = 0;
		if (user_cards_.size())
		{			
			size_t count_ace = 0;
			const size_t ace = 11;
			const size_t max_iner = 21;
			for (const auto& card : user_cards_)
			{
				card::CardValue temp = card->GetValue();
				if (temp == card::CardValue::ACE
					|| temp == card::CardValue::JACK
					|| temp == card::CardValue::QUEEN
					|| temp == card::CardValue::KING)
				{
					switch (temp)
					{
					case card::CardValue::ACE:
						++count_ace;
						break;
					case card::CardValue::JACK:
						result += 10;
						break;
					case card::CardValue::QUEEN:
						result += 10;
						break;
					case card::CardValue::KING:
						result += 10;
						break;
					case card::CardValue::TEN:
						result += 10;
						break;
					}
				}
				else
				{
					result += static_cast<size_t>(temp);
				}
			}

			for (size_t i = 0; i < count_ace; ++i)
			{
				if (result + ace < max_iner)
				{
					result += ace;
				}
				else
				{
					++result;
				}
			}
		}
		return result;
	}

	void Hand::Clear() noexcept
	{		
		user_cards_.erase(user_cards_.begin(), user_cards_.end());		
	}

	GamerUser::GamerUser(const std::string& name) : name_(name)
	{}

	GamerAI::GamerAI() = default;
}

void TestBlackJack()
{
	card::CardDeck card_deck;
	card_deck.ShowCardDeck();
	hand::GamerUser user1("Ivan");
	hand::GamerUser user2("Oleg");
	hand::GamerAI ai;

	auto it = card_deck.GetCardDeck().begin();
	for (size_t i = 0; i < 2; ++i)
	{
		user1.AddCard(*it++);
		user2.AddCard(*it++);
		ai.AddCard(*it++);
	}
	std::cout << "User1 shows his cards" << std::endl;
	user1.ShowCards();
	std::cout << "User1's value: " << user1.GetSumCards() << std::endl;
	std::cout << "User2 shows his cards" << std::endl;
	user2.ShowCards();
	std::cout << "User2's value: " << user2.GetSumCards() << std::endl;
	std::cout << "AI shows its cards" << std::endl;
	ai.ShowCards();
	std::cout << "Ai's value: " << ai.GetSumCards() << std::endl;
}