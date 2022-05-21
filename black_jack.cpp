#include "black_jack.h"

namespace card 
{
	enum class CardSuit
	{
		CLUB,
		DIAMOND,
		WORM,
		SPANDES
	};

	enum class CardValue
	{
		ONE = 1,
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
		KING = 10,
		ACE = 11
	};

	Card::Card()
		:suit_(CardSuit::CLUB), value_(CardValue::ACE), is_open_card_(false) 
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

	size_t Card::GetValue() const
	{
		return static_cast<size_t>(value_);
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
}