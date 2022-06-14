#include "black_jack.h"
#include <iostream>

#include <ctime>

namespace card 
{
	Card::Card()
		:suit_(CardSuit::CLUBS), value_(CardValue::ACE), is_open_card_(false) 
	{}

	Card::Card(CardSuit suit, CardValue value)
	: suit_(suit), value_(value), is_open_card_(true)
	{}

	void Card::SetSuit(CardSuit suit) noexcept
	{
		suit_ = suit;
	}

	void Card::SetValueCard(CardValue value) noexcept
	{
		value_ = value;
	}

	void Card::SetPositionCArd(bool pos) noexcept
	{
		is_open_card_ = pos;
	}

	CardValue Card::GetValue() const noexcept
	{
		return value_;
	}

	void Card::FlipCard() noexcept
	{
		is_open_card_ = !is_open_card_;
	}

	void Card::ShowCard(std::ostream& out) const noexcept
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

	bool Card::GetIsOpenCard() const noexcept
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
		cards_deck_ =CreateDeck();
		ShuffleDeck();
		it_ = cards_deck_.begin();
	}
	
	void CardDeck::ShowCardDeck(std::vector<Card>& cards_deck) const noexcept
	{
		int i = 0;
		for (auto& card : cards_deck)
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

	std::vector<Card>& CardDeck::GetCardDeck() noexcept
	{
		return cards_deck_;
	}

	CardDeck::Iterator CardDeck::GetIter() noexcept
	{
		return it_;
	}

	void CardDeck::ShiftIt()
	{
		if (it_ != cards_deck_.end())
		{
			++it_;
		}
		else
		{
			throw std::out_of_range(" ");
		}
	}

	void CardDeck::ShuffleDeck() noexcept
	{
		srand(time(NULL)); // инициализируем генератор случайных чисел
		const size_t count_deck_cards = 52;
		for (size_t i = 0; i < count_deck_cards / 2; ++i)
		{
			int k = rand() % 52; // выбираем случайную карту
			Card temp = cards_deck_[i]; // и меняем ее с текущей
			cards_deck_[i] = cards_deck_[k];
			cards_deck_[k] = temp;
		}		
	}	

	void CardDeck::operator()() noexcept
	{
		ShuffleDeck();
		it_ = cards_deck_.begin();
	}

	std::vector<Card> CardDeck::CreateDeck()
	{
		const size_t count_deck_cards = 52;
		std::vector<Card> cards_deck;
		for (size_t i = 0; i < count_deck_cards; ++i)
		{
			size_t num = (i % 13) + 2;
			CardSuit su = CardSuit(i / 13);			
			cards_deck.push_back(card::Card(su, static_cast<CardValue>(num)));
		}
		ShowCardDeck(cards_deck);
		return cards_deck;
	}
	
} // namespace card

namespace hand
{
	Hand::Hand() = default; 

	void Hand::AddCard(card::Card card) noexcept
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
				if (result + ace <= max_iner)
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

namespace game
{
	Game::Game(std::vector<std::string>&& players) : card_deck_()
	{
		diller_ = std::make_unique< hand::GamerAI>();
		for (const std::string& name : players)
		{
			players_.push_back(std::make_shared<hand::GamerUser>(name));
		}
	}

	void Game::Play()
	{
		GameRaund();
		std::string answer;
		std::cout << "Do you want to play agen? Please answer \"y\" if yes or click any button" << std::endl;
		std::cin >> answer;
		if (answer == "y")
		{
			ClearPlayers();
			card_deck_();
			Play();
		}
		else
		{
			std::cout << "Thanks for game! Good luck!" << std::endl;
		}
	}

	void Game::AddItinationalCards(std::shared_ptr<hand::GamerUser>& player)
	{
		if (player->GetSumCards() < 21)
		{
			std::string answer;
			std::cout << player->GetName() << ", do you have take card? Please \"y\" if yes or click any button" << std::endl;
			std::cin >> answer;
			if (answer == "y")
			{
				Deal(player);
				std::cout << *player << std::endl;
				AddItinationalCards(player);
			}
		}
		else if (player->GetSumCards() > 21)
		{
			player->Lose();
		}
	}

	void Game::AddItinationalCards(std::shared_ptr<hand::GamerAI>& player)
	{
		if (player->GetSumCards() < 19)
		{
			Deal(player);
			std::cout << *player << std::endl;
			AddItinationalCards(player);
		}
		else if (player->GetSumCards() > 21)
		{
			player->Lose();
		}
	}

	void Game::ProcessGame()
	{
		for (auto& player : players_)
		{
			AddItinationalCards(player);
		}
		diller_->GetCards()[0]->FlipCard();
		std::cout << *diller_ << std::endl;
		AddItinationalCards(diller_);
		Winers();
	}

	void Game::GameRaund()
	{
		bool is_cards_out = false;
		while (card_deck_.GetIter() != card_deck_.GetCardDeck().end())
		{
			try
			{
				FirstDealCards();
				PrintPlayrsCards();
				ProcessGame();
				std::string answer;
				std::cout << "Do you want to play agen? Please answer \"y\" if yes or click any button" << std::endl;
				std::cin >> answer;
				if (answer == "y")
				{
					ClearPlayers();
				}
				else
				{
					break;
				}
			}
			catch (error::StopGame)
			{				
				is_cards_out = true;
			}
		}
		if (is_cards_out)
		{
			std::cout << "The cards are out. This game raund is over." << std::endl;
		}
		else
		{
			std::cout << "This game raund is over." << std::endl;
		}		
	}

	void Game::PrintPlayrsCards() const
	{
		std::cout << diller_->GetName() << "'s cards: ";
		diller_->ShowCards();
		for (const auto& player : players_)
		{
			std::cout << player->GetName() << "'s cards: ";
			player->ShowCards();
		}
	}

	void Game::FirstDealCards()
	{
		for (size_t i = 0; i < 2; ++i)
		{
			for (auto it = players_.begin(); it != players_.end(); ++it)
			{
				Deal(*it);
			}
			Deal(diller_);
		}
		diller_->GetCards()[0]->FlipCard();
	}

	void Game::ClearPlayers()
	{
		for (auto& player : players_)
		{
			player->Clear();
		}
		diller_->Clear();
	}

	std::vector<std::shared_ptr<hand::GenericPlayer>> Game::CreateVectorWiners() const noexcept
	{
		std::vector<std::shared_ptr<hand::GenericPlayer>> winers;
		if (diller_->GetSumCards() <= 21)
		{
			winers.push_back(diller_);
		}
		for (auto player : players_)
		{
			if (winers.empty() || player->GetSumCards() <= 21)
			{
				winers.push_back(player);
			}
		}
		std::sort(winers.begin(), winers.end()
			, [](std::shared_ptr<hand::GenericPlayer>lhs, std::shared_ptr<hand::GenericPlayer>rhs)
			{
				return lhs->GetSumCards() > rhs->GetSumCards();
			});
		return winers;
	}

	void Game::ShowWinersAndLose(std::vector<std::shared_ptr<hand::GenericPlayer>>&& winers) const noexcept
	{
		if (winers.size() == 1)
		{
			winers[0]->Win();
			std::cout << *winers[0] << std::endl;
		}
		else
		{
			size_t max_sum = winers[0]->GetSumCards();
			size_t count_push = std::count_if(winers.begin(), winers.end(),
				[&](std::shared_ptr<hand::GenericPlayer>player)
				{
					return player->GetSumCards() == max_sum;
				});
			if (count_push == 1)
			{
				winers[0]->Win();
				std::cout << *winers[0] << std::endl;
				for (size_t i = count_push; i < winers.size(); ++i)
				{
					winers[i]->Lose();
					std::cout << *winers[i] << std::endl;
				}
			}
			else
			{
				for (size_t i = 0; i < count_push; ++i)
				{
					winers[i]->Push();
					std::cout << *winers[i] << std::endl;
				}
				for (size_t i = count_push; i < winers.size(); ++i)
				{
					winers[i]->Lose();
					std::cout << *winers[i] << std::endl;
				}
			}
		}
	}

	void Game::Winers() const noexcept
	{
		ShowWinersAndLose(CreateVectorWiners());
	}

}// namespace game

std::vector<std::string> GreeateePlayers()
{
	size_t count = 0;
	std::cout << "Please enter count players from 1 to 7" << std::endl;
	std::cin >> count;
	std::vector<std::string> names;
	for (size_t i = 1; i <= count; ++i)
	{
		std::string name;
		std::cout << "Plase enter nicky " << i << " player" << std::endl;
		std::cin >> name;
		names.push_back(std::move(name));
	}
	return names;
}

void GameBlackJack()
{
	game::Game g(GreeateePlayers());
	g.Play();	
}