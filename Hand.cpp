#pragma once
#include "Hand.h"
#include "Card.h"


Hand::Hand(std::string& all_cards_param)
{
	Card myCard;
	//Card* p_myCard = &myCard;
	for (size_t i = 0; i < all_cards_param.size(); i++)
	{
		
		if (isupper(all_cards_param[i])||isdigit(all_cards_param[i])) // add condition
		{
			myCard.MyCardFace = myCard.ConvertCharToCardFace(all_cards_param[i]);
		}
		else if (islower(all_cards_param[i])) // add condition
		{
			myCard.MyCardColor = myCard.ConvertCharToCardColor(all_cards_param[i]);
		}

		if(myCard.MyCardFace != (Card::CardFace)0 && myCard.MyCardColor != (Card::CardColor)0)
		{
			FullHand.push_back(myCard);
			myCard = Card();
		}
		
	}
	
}

std::ostream& operator<<(std::ostream& out, const Hand& hand)
{
	const std::string nameHS[] = { "Empty", "HC", "1P", "2Ps", "TRIPS", "STR8", "FL", "FH", "QUADS", "STR8FL", "RFL"};
	return out << "HandStrength: " << nameHS[(int)hand.HandPower];
	
}

//Hand::~Hand() 
//{
//	/*std::cout << "HAND DESTR CALLED" << std::endl;*/
//}