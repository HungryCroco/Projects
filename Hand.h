#pragma once
#include <vector>
#include "Card.h"
#include <iostream>

class Hand
{
    
public:
    enum class HandStrenght
    {
        Empty = 0,
        HighCard = 1,
        OnePair = 2,
        TwoPairs = 3,
        ThreeOfAKind = 4,
        Straight = 5,
        Flush = 6,
        FullHouse = 7,
        FourOfAKind = 8,
        StraightFlush = 9,
        RoyalFlush = 10,
    };

    Hand() {};
    Hand(std::string& all_cards_param);
 /*   ~Hand();*/

	std::vector<Card> FullHand{};
	std::vector<Card> FinalHand{};
    HandStrenght HandPower{HandStrenght::Empty};

    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
    
private:

};