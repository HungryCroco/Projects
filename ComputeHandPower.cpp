#pragma once
#include "ComputeHandPower.h"
#include <vector>

std::vector<Card> flushHand{};
Card::CardColor flushColor{};

std::vector<Card> streightHand{};

std::vector<Card> rcs1{}; 
std::vector<Card> rcs2{};
std::vector<Card> rcs3{};

std::vector<Card> rcs1Ordered{}; // mb pointer/ref
std::vector<Card> rcs2Ordered{}; // mb pointer/ref

std::vector<Card> finalHand{};

void ClearHand(Hand& myHand_param)
{
	
	flushHand = std::vector<Card>{};
	flushColor = Card::CardColor{};

	streightHand = std::vector<Card>{};

	rcs1 = std::vector<Card>{};
	rcs2 = std::vector<Card>{};
	rcs3 = std::vector<Card>{};

	rcs1Ordered = std::vector<Card>{};
	rcs2Ordered = std::vector<Card>{};

	finalHand = std::vector<Card>{};
	myHand_param.FinalHand = std::vector<Card>{};
	myHand_param.HandPower = Hand::HandStrenght::Empty;
}

Hand ComputeHand(Hand& myHand_param)
{
	ClearHand(myHand_param);
	Hand output = myHand_param;

	OrderHandByCardFace(myHand_param);
	bool checkForFlush = CheckForFlush(myHand_param);

	
	if (checkForFlush)
	{
		ComputeAllFlushes(myHand_param);
	}
	if ((int)myHand_param.HandPower < 9)
	{
		ComputeFHandQuads(myHand_param);
	}
	if ((int)myHand_param.HandPower < 6)
	{
		ComputeStreight(myHand_param);
	}
	if ((int)myHand_param.HandPower < 5)
	{
		ComputeTRIPSminus(myHand_param);
	}	

	return output;
}

bool CheckForFlush(Hand& myHand_param)
{
	unsigned int clubs{ 0 }; //1
	unsigned int diamonds{ 0 }; //2
	unsigned int hearts{ 0 }; //3
	unsigned int spades{ 0 }; //4

	
	std::vector<Card> currFullHand = myHand_param.FullHand;

		for (Card card : currFullHand)
		{
			if ((int)card.MyCardColor == 1)
			{
				++clubs;
				if (clubs == 5)
				{
					flushColor = Card::CardColor::clubs;
					return true;
				}
			}
			else if ((int)card.MyCardColor == 3)
			{
				++diamonds;
				if (diamonds == 5)
				{
					flushColor = Card::CardColor::diamonds;
					return true;
				}
			}
			else if ((int)card.MyCardColor == 2)
			{
				++hearts;
				if (hearts == 5)
				{
					flushColor = Card::CardColor::hearts;
					return true;
				}
			}
			else if ((int)card.MyCardColor == 4)
			{
				++spades;
				if (spades == 5)
				{
					flushColor = Card::CardColor::spades;
					return true;
				}
			}
			
		}

		return false;
}

void ComputeAllFlushes(Hand& myHand_param)
{
	unsigned int flushHandSize;

	for (Card card : myHand_param.FullHand)
	{
		if (card.MyCardColor == flushColor)
		{
			if (flushHand.size() == 0)
			{
				flushHand.push_back(card);
			}
			else
			{
				flushHandSize = flushHand.size();

				for (unsigned int i = 0; i < flushHandSize; i++)
				{
					if (card.MyCardFace > flushHand[i].MyCardFace)
					{
						flushHand.insert(flushHand.begin() + i, card);
						i = flushHand.size();
					}
					else if (i + 1 == flushHand.size())
					{
						flushHand.push_back(card);
					}
				}	
			}	
		}
	}

	flushHandSize = flushHand.size();

	//check for STR8FL/RoyalFL
	bool streightFound = false;
	for (unsigned int i = 0; i < flushHandSize-4; i++)
	{
		if (streightFound == false && ((int)flushHand[i].MyCardFace - (int)flushHand[i + 4].MyCardFace) == 4)
		{
			finalHand.push_back(flushHand[i]);
			finalHand.push_back(flushHand[i + 1]);
			finalHand.push_back(flushHand[i + 2]);
			finalHand.push_back(flushHand[i + 3]);
			finalHand.push_back(flushHand[i + 4]);
			streightFound = true;
			myHand_param.FinalHand = finalHand;
			if (flushHand[0].MyCardFace != Card::CardFace::Ace)
			{
				myHand_param.HandPower = Hand::HandStrenght::StraightFlush;
			}
			else
			{
				myHand_param.HandPower = Hand::HandStrenght::RoyalFlush;
			}
		}	
	}
	if (streightFound == false && (flushHand[0].MyCardFace == Card::CardFace::Ace) &&
		(flushHand[flushHand.size() - 4].MyCardFace == Card::CardFace::Five))
	{
		finalHand.push_back(flushHand[flushHand.size() - 4]);
		finalHand.push_back(flushHand[flushHand.size() - 3]);
		finalHand.push_back(flushHand[flushHand.size() - 2]);
		finalHand.push_back(flushHand[flushHand.size() - 1]);
		finalHand.push_back(flushHand[0]);

		streightFound = true; 
		myHand_param.HandPower = Hand::HandStrenght::StraightFlush;
		myHand_param.FinalHand = finalHand;
	}

	

	if (streightFound == false)
	{
		if (flushHandSize > 5)
		{
			for (unsigned int i = 5; i < flushHandSize; i++)
			{
				flushHand.pop_back();
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::Flush; // run only after CheckFlush == true;
		myHand_param.FinalHand = flushHand;
	}
}
void ComputeTRIPSminus(Hand& myHand_param)
{
	if (rcs1Ordered.size() == 3)
	{
		finalHand = rcs1Ordered;
		for (unsigned int i = 0; finalHand.size() < 5; i++)
		{
			if (streightHand[i].MyCardFace != rcs1Ordered[0].MyCardFace)
			{
				finalHand.push_back(streightHand[i]);
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::ThreeOfAKind;
		myHand_param.FinalHand = finalHand;
	}
	else if (rcs1Ordered.size() == 2 && rcs2Ordered.size() == 2)
	{
		finalHand = rcs1Ordered;
		for (Card card : rcs2Ordered)
		{
			finalHand.push_back(card);
		}
		for (unsigned int i = 0; finalHand.size() < 5; i++)
		{
			if (streightHand[i].MyCardFace != rcs1Ordered[0].MyCardFace && 
				streightHand[i].MyCardFace != rcs2Ordered[0].MyCardFace)
			{
				finalHand.push_back(streightHand[i]);
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::TwoPairs;
		myHand_param.FinalHand = finalHand;
	}
	else if (rcs1Ordered.size() == 2)
	{
		finalHand = rcs1Ordered;
		for (unsigned int i = 0; finalHand.size() < 5; i++)
		{
			if (streightHand[i].MyCardFace != rcs1Ordered[0].MyCardFace)
			{
				finalHand.push_back(streightHand[i]);
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::OnePair;
		myHand_param.FinalHand = finalHand;
	}
	else
	{
		for (unsigned int i = 0; finalHand.size() < 5; i++)
		{
			finalHand.push_back(streightHand[i]);
		}
		myHand_param.HandPower = Hand::HandStrenght::HighCard;
		myHand_param.FinalHand = finalHand;
	}
}
void ComputeFHandQuads(Hand& myHand_param)
{
	OrderRCs(myHand_param);
	// Quads:
	if (rcs1.size() == 4)
	{
		for (Card card : rcs1)
		{
			finalHand.push_back(card);
			if (rcs1[0].MyCardFace != streightHand[0].MyCardFace)
			{
				finalHand.push_back(streightHand[0]);
			}
			else
			{
				finalHand.push_back(streightHand[1]);
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::FourOfAKind;
		myHand_param.FinalHand = finalHand;
	}
	else if (rcs2.size() == 4)
	{
		for (Card card : rcs2)
		{
			finalHand.push_back(card);
			if (rcs2[0].MyCardFace != streightHand[0].MyCardFace)
			{
				finalHand.push_back(streightHand[0]);
			}
			else
			{
				finalHand.push_back(streightHand[1]);
			}
		}
		myHand_param.HandPower = Hand::HandStrenght::FourOfAKind;
		myHand_param.FinalHand = finalHand;
	}

	// FH: 
	
	else if (rcs1Ordered.size() == 3 && rcs2Ordered.size() > 1)
	{
		for (Card card : rcs1Ordered)
		{
			finalHand.push_back(card);
		}
		for (unsigned int i = 0; i < 2; i++)
		{
			finalHand.push_back(rcs2Ordered[i]);
		}
		myHand_param.FinalHand = finalHand;
		myHand_param.HandPower = Hand::HandStrenght::FullHouse;
	}
	
}

void ComputeStreight(Hand& myHand_param)
{
	bool streightFound = false;
	//finalHand = std::vector<Card>();
	
	if (streightHand.size() > 4)
	{
		for (unsigned int i = 0; i < streightHand.size()-4; i++)
		{
			if (streightFound == false && ((int)streightHand[i].MyCardFace - (int)streightHand[i+4].MyCardFace) == 4)
			{
				finalHand.push_back(streightHand[i]);
				finalHand.push_back(streightHand[i+1]);
				finalHand.push_back(streightHand[i+2]);
				finalHand.push_back(streightHand[i+3]);
				finalHand.push_back(streightHand[i+4]);
				streightFound = true;
				myHand_param.HandPower = Hand::HandStrenght::Straight;
				myHand_param.FinalHand = finalHand;
			}
		}

		if (streightFound == false && (streightHand[0].MyCardFace == Card::CardFace::Ace) && 
			(streightHand[streightHand.size()-4].MyCardFace == Card::CardFace::Five))
		{
			finalHand.push_back(streightHand[streightHand.size() - 4]);
			finalHand.push_back(streightHand[streightHand.size() - 3]);
			finalHand.push_back(streightHand[streightHand.size() - 2]);
			finalHand.push_back(streightHand[streightHand.size() - 1]);
			finalHand.push_back(streightHand[0]);
			
			streightFound = true; // mb delete;
			myHand_param.HandPower = Hand::HandStrenght::Straight;
			myHand_param.FinalHand = finalHand;
		}
	}
}
void OrderRCs(Hand& myHand_param)
{
	if (rcs1.size() != 0)
	{
		std::vector<Card> rcsOrderedByStrength{ rcs1[0] };

		if (rcs1.size() == 3 && rcs2.size() == 3)
		{
			if (rcs1[0].MyCardFace > rcs2[0].MyCardFace)
			{
				rcs1Ordered = rcs1;
				rcs2Ordered = rcs2;
			}
			else
			{
				rcs1Ordered = rcs2;
				rcs2Ordered = rcs1;
			}
		}
		else if (rcs1.size() == 3)
		{
			rcs1Ordered = rcs1;
			if (rcs2.size() == 2)
			{
				if (rcs3.size() == 2)
				{
					if (rcs2[0].MyCardFace > rcs3[0].MyCardFace)
					{
						rcs2Ordered = rcs2;
					}
					else
					{
						rcs2Ordered = rcs3;
					}
				}
				else
				{
					rcs2Ordered = rcs2;
				}
			}
		}
		else if (rcs2.size() == 3)
		{
			rcs1Ordered = rcs2;

			if (rcs3.size() == 2)
			{
				if (rcs1[0].MyCardFace > rcs3[0].MyCardFace)
				{
					rcs2Ordered = rcs1;
				}
				else
				{
					rcs2Ordered = rcs3;
				}
			}
			else
			{
				rcs2Ordered = rcs1;
			}
		}
		else if (rcs3.size() == 3)
		{
			rcs1Ordered = rcs3;

			if (rcs1[0].MyCardFace > rcs2[0].MyCardFace)
			{
				rcs2Ordered = rcs1;
			}
			else
			{
				rcs2Ordered = rcs2;
			}
		}
		else if (rcs3.size() == 2)
		{
			if (rcs2[0].MyCardFace  > rcsOrderedByStrength[0].MyCardFace)
			{
				rcsOrderedByStrength.insert(rcsOrderedByStrength.begin(), rcs2[0]);
			}
			else
			{
				rcsOrderedByStrength.push_back(rcs2[0]);
			}
			for (unsigned int i = 0; i < rcsOrderedByStrength.size(); i++)
			{
				if (rcs3[0].MyCardFace > rcsOrderedByStrength[i].MyCardFace)
				{
					rcsOrderedByStrength.insert(rcsOrderedByStrength.begin()+i, rcs3[0]);
					i = rcsOrderedByStrength.size();
				}
				else if(i+1 == rcsOrderedByStrength.size())
				{
					rcsOrderedByStrength.push_back(rcs3[0]);
					i = rcsOrderedByStrength.size();
				}
			}

			if (rcsOrderedByStrength[0].MyCardFace == rcs1[0].MyCardFace)
			{
				rcs1Ordered = rcs1;
				if (rcsOrderedByStrength[1].MyCardFace == rcs2[0].MyCardFace)
				{
					rcs2Ordered = rcs2;
				}
				else
				{
					rcs2Ordered = rcs3;
				}
			}
			else if (rcsOrderedByStrength[0].MyCardFace == rcs2[0].MyCardFace)
			{
				rcs1Ordered = rcs2;
				if (rcsOrderedByStrength[1].MyCardFace == rcs1[0].MyCardFace)
				{
					rcs2Ordered = rcs1;
				}
				else
				{
					rcs2Ordered = rcs3;
				}
			}
			else if (rcsOrderedByStrength[0].MyCardFace == rcs3[0].MyCardFace)
			{
				rcs1Ordered = rcs3;
				if (rcsOrderedByStrength[1].MyCardFace == rcs1[0].MyCardFace)
				{
					rcs2Ordered = rcs1;
				}
				else
				{
					rcs2Ordered = rcs2;
				}
			}
		}
		else if (rcs2.size() == 2)
		{
			if (rcs1[0].MyCardFace > rcs2[0].MyCardFace)
			{
				rcs1Ordered = rcs1;
				rcs2Ordered = rcs2;
			}
			else
			{
				rcs1Ordered = rcs2;
				rcs2Ordered = rcs1;
			}
		}
		else if (rcs1.size() == 2)
		{
			rcs1Ordered = rcs1;
		}
	}
}

void OrderHandByCardFace(Hand& myHand_param)

{
	/*compute:
		* vector<Card> streightHand - only unique CardFaces by Cardstrength for checking for Streights
		* vector<Card> rcs1 - repeating Cards for checking for Pair+
		* vector<Card> rcs2 - -//-//--//-//-  for checking for 2PS+
		* vector<Card> rcs3 - -//-
	*/

	std::vector<Card> currFullHand = myHand_param.FullHand;
	
	streightHand.push_back(currFullHand[0]);
	for (unsigned int i = 1; i < currFullHand.size(); i++)
	{	
		for (unsigned int j = 0; j < streightHand.size(); j++)
		{
			if ((int)currFullHand[i].MyCardFace > (int)streightHand[j].MyCardFace)
			{
				streightHand.insert(streightHand.begin() + j, currFullHand[i]);
				j = i;
			}
			else if ((int)currFullHand[i].MyCardFace == (int)streightHand[j].MyCardFace)
			{
				if (rcs1.size() == 0 )
				{
					rcs1.push_back(streightHand[j]);
					rcs1.push_back(currFullHand[i]);
				}
				else if (rcs1.size() != 0 && currFullHand[i].MyCardFace == rcs1[0].MyCardFace)
				{
					rcs1.push_back(currFullHand[i]);
				}
				else if (rcs2.size() == 0)
				{
					rcs2.push_back(streightHand[j]);
					rcs2.push_back(currFullHand[i]);
				}
				else if (rcs2.size() != 0 && currFullHand[i].MyCardFace == rcs2[0].MyCardFace)
				{
					rcs2.push_back(currFullHand[i]);
				}
				else if (rcs3.size() == 0)
				{
					rcs3.push_back(streightHand[j]);
					rcs3.push_back(currFullHand[i]);
				}
				else if (rcs3.size() != 0 && currFullHand[i].MyCardFace == rcs3[0].MyCardFace)
				{
					rcs3.push_back(currFullHand[i]);
				}

				j = i;
			}
			else if (j + 1 == streightHand.size())
			{
				streightHand.push_back(currFullHand[i]);
				j = i;
			}
		}
	}
		
}


