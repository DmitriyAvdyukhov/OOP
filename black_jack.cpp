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
		is_open_card_ = !is_open_card_;
	}

	void Card::ShowCard(std::ostream& out) const
	{		
		switch (suit_)
		{
		case CardSuit::CLUBS:
			out << "CLUBS ";
			break;
		case CardSuit::DIAMONDS:
			out << "DIAMONDS ";
			break;
		case CardSuit::WORMS:
			out << "WORMS ";
			break;
		case CardSuit::SPANDES:
			out << "SPANDES ";
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
				out << "A";
				break;
			case CardValue::JACK:
				out << "J";
				break;
			case CardValue::QUEEN:
				out << "Q";
				break;
			case CardValue::KING:
				out << "K";
				break;
			}
		}
		else
		{
			out << static_cast<int>(value_);
		}
	}

	bool Card::GetIsOpenCard() const
	{
		return is_open_card_;
	}

	std::ostream& operator<< (std::ostream& out, const Card& c)
	{
		if (c.GetIsOpenCard())
		{
			c.ShowCard(out);
		}
		else
		{
			out << "XX";
		}
		return out;
	}

	CardDeck::CardDeck()
	{
		cards_deck_ = MixDeck(CreateDeck());
	}
	
	void CardDeck::ShowCardDeck()
	{
		int i = 0;
		for (const auto& card : cards_deck_)
		{
			std::cout << card;
			std::cout << " ";
			if (!((i + 1) % 13))
			{
				std::cout << std::endl;
			}
			++i;
		}
		std::cout << std::endl;
	}	

	const std::vector<Card>& CardDeck::GetCardDeck() const
	{
		return cards_deck_;
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
				std::cout << *card;
				is_first = false;
			}
			else
			{
				std::cout << ", ";
				std::cout << *card;
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

	const std::vector<std::unique_ptr<card::Card>>& Hand::GetCards() const
	{
		return user_cards_;
	}

	GenericPlayer::GenericPlayer(const std::string& name) : name_(name)
	{}
	bool GenericPlayer::IsBoosted() const
	{
		if (GetSumCards() > 21)
		{
			return true;
		}
		return false;
	}
	void GenericPlayer::Bust(std::ostream& out) const
	{
		out << "Gamer: " << name_ << " bust" << std::endl;
	}

	std::string GenericPlayer::GetName() const
	{
		return name_;
	}

	void GenericPlayer::Win()const
	{
		std::cout << "Player: " << GetName() << " is winer" << std::endl;
	}

	void GenericPlayer::Lose() const
	{
		std::cout << "Player: " << GetName() << " is lose" << std::endl;
	}

	void GenericPlayer::Push() const
	{
		std::cout << "Player: " << GetName() << " is push" << std::endl;
	}

	std::ostream& operator<< (std::ostream& out, const GenericPlayer& g)
	{
		out << "Player: " << g.GetName() << " his cards: ";
		if (g.GetCards().size())
		{
			for (size_t i = 0; i < g.GetCards().size(); ++i)
			{
				if (!g.GetCards()[i]->GetIsOpenCard())
				{
					g.GetCards()[i]->FlipCard();
				}
				out << *g.GetCards()[i] << " ";
			}
			out << "value his cards: " << g.GetSumCards() << std::endl;
		}
		else
		{
			out << " empty" << std::endl;
		}
		return out;
	}

	GamerUser::GamerUser(const std::string& name) : GenericPlayer(name)
	{}

	bool GamerUser::IsHitting() const
	{
		if (GetSumCards() < 21)
		{
			return true;
		}
		return false;
	}

	GamerAI::GamerAI() : GenericPlayer("AI")
	{}

	bool GamerAI::IsHitting() const
	{
		if (GetSumCards() < 16)
		{
			return true;
		}
		return false;
	}

	void GamerAI::FlipFirstCard()
	{
		GetCards()[0]->FlipCard();
	}
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
	std::cout << user1;
	std::cout << "User1's value: " << user1.GetSumCards() << std::endl;
	std::cout << "User2 shows his cards" << std::endl;
	user2.ShowCards();
	std::cout << "User2's value: " << user2.GetSumCards() << std::endl;
	std::cout << "AI shows its cards" << std::endl;
	ai.FlipFirstCard();
	ai.ShowCards();
	std::cout << "Ai's value: " << ai.GetSumCards() << std::endl;
	std::cout << ai;
}