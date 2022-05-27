#pragma once
#include "ComputeOdds.h"


unsigned int hand1_Won{};
unsigned int hand2_Won{};
unsigned int split{};

long combos{};
long combosf1{};
long combosf2{};
long combosf3{};

std::vector<Card> combosLeft{};
std::vector<Card> combosUsed{};

void CompareHandStrength(Hand& myHand1_param, Hand& myHand2_param)
{
	if (myHand1_param.HandPower > myHand2_param.HandPower)
	{
		++hand1_Won;
	}
	else if (myHand1_param.HandPower < myHand2_param.HandPower)
	{
		++hand2_Won;
	}
	else if (myHand1_param.HandPower == myHand2_param.HandPower)
	{
		for (unsigned int i = 0; i < myHand1_param.FinalHand.size(); i++)
		{
			if (myHand1_param.FinalHand[i].MyCardFace > myHand2_param.FinalHand[i].MyCardFace)
			{
				++hand1_Won;
				i = myHand1_param.FinalHand.size(); // mb improve i = 5;
			}
			else if (myHand1_param.FinalHand[i].MyCardFace < myHand2_param.FinalHand[i].MyCardFace)
			{
				++hand2_Won;
				i = myHand1_param.FinalHand.size();
			}
			else if (i+1 == myHand1_param.FinalHand.size())
			{
				split++;
			}
		}
		
	}
}

float ComputeOdds(Hand& myHand1_param, Hand& myHand2_param)
{
	combosLeft = GetAllCardCombos();
	combosUsed = GetUsedCardCombos(myHand1_param,myHand2_param);
	combosLeft = DeleteCardFromVector(combosUsed, combosLeft);
	
	if (myHand1_param.FullHand.size() == 2)
	{
		SimulateFlop(myHand1_param, myHand2_param, combosLeft);
	}
	else if (myHand1_param.FullHand.size() == 5)
	{
		SimulateTurn(myHand1_param, myHand2_param, combosLeft);
	}
	else if (myHand1_param.FullHand.size() == 6)
	{
		SimulateRiver(myHand1_param, myHand2_param, combosLeft);
	}
	
	return ((float)(hand1_Won + (float)split / 2) * 100 / (float)(hand1_Won + hand2_Won + split));	
}

void SimulateRiver(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param)
{
	std::vector<Card> combosLeft_River{};
	for (Card card : combosUsed)
	{
		/*for (unsigned int i = 0; i < combosLeft.size(); i++)
		{
			if (card.MyCardFace == combosLeft[i].MyCardFace &&
				card.MyCardColor == combosLeft[i].MyCardColor)
			{
				combosLeft.erase(combosLeft.begin() + i);
				i = combosLeft.size();
			}
		}*/
		combosLeft_River = DeleteCardFromVector(card,combosLeft_param);
	}

	ComputeOddsRiver(myHand1_param, myHand2_param, combosLeft_River);
}

void SimulateTurn(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param)
{
	std::vector<Card> combosLeft_Turn{ combosLeft_param };
	std::vector<Card> combosLeft_River{ combosLeft_param };
	for (Card card : combosLeft_Turn)
	{
		
		if (myHand1_param.FullHand.size() == 5)
		{
			myHand1_param.FullHand.push_back(card);
			myHand2_param.FullHand.push_back(card);
		}
		else
		{
			myHand1_param.FullHand[5] = card;
			myHand2_param.FullHand[5] = card;
		}
		combosLeft_River = DeleteCardFromVector(card, combosLeft_River);
		SimulateRiver(myHand1_param, myHand2_param, combosLeft_River);
	}
}
void SimulateFlop(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param)
{
	std::vector<Card> fC1CombosLeft{ combosLeft_param };
	std::vector<Card> fC2CombosLeft{ fC1CombosLeft };

	for (size_t i = 0; i < fC1CombosLeft.size(); i++)
	{
		++combosf1;
		Card FC1 = fC1CombosLeft[i];
		//replace with function in simflop/simturn
		if (myHand1_param.FullHand.size() == 2) 
		{
			myHand1_param.FullHand.push_back(FC1);
			myHand2_param.FullHand.push_back(FC1);
		}
		else
		{
			myHand1_param.FullHand[2] = FC1;
			myHand2_param.FullHand[2] = FC1;
		}

		//fC1CombosLeft = DeleteCardFromVector(FC1, fC1CombosLeft);
		fC2CombosLeft = DeleteCardFromVector(FC1, fC2CombosLeft);
		std::vector<Card> fC3CombosLeft{ fC2CombosLeft };

		for (size_t j = 0; j < fC2CombosLeft.size(); j++)
		{
			++combosf2;
			Card FC2 = fC2CombosLeft[j];
			if (myHand1_param.FullHand.size() == 3)
			{
				myHand1_param.FullHand.push_back(FC2);
				myHand2_param.FullHand.push_back(FC2);
			}
			else
			{
				myHand1_param.FullHand[3] = FC2;
				myHand2_param.FullHand[3] = FC2;
			}
			//fC2CombosLeft = DeleteCardFromVector(FC2, fC2CombosLeft);
			fC3CombosLeft = DeleteCardFromVector(FC2, fC3CombosLeft);
			std::vector<Card> combosLeft_Turn{ fC3CombosLeft };
			for (size_t z = 0; z < fC3CombosLeft.size(); z++)
			{
				
				++combosf3;
				Card FC3 = fC3CombosLeft[z];
				if (myHand1_param.FullHand.size() == 4)
				{
					myHand1_param.FullHand.push_back(FC3);
					myHand2_param.FullHand.push_back(FC3);
				}
				else
				{
					myHand1_param.FullHand[4] = FC3;
					myHand2_param.FullHand[4] = FC3;
				}
				//fC3CombosLeft = DeleteCardFromVector(FC3, fC3CombosLeft);
				combosLeft_Turn = DeleteCardFromVector(FC3, combosLeft_Turn);
				SimulateTurn(myHand1_param, myHand2_param, combosLeft_Turn);
			}
		}
	}
}

void ComputeOddsRiver(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param)
{
	//riverCombosLeft = combosLeft_param;
	for (Card card : combosLeft_param)
	{
		if (myHand1_param.FullHand.size() == 6)
		{
			myHand1_param.FullHand.push_back(card);
			myHand2_param.FullHand.push_back(card);
		}
		else
		{
			myHand1_param.FullHand[6] = card;
			myHand2_param.FullHand[6] = card;
		}
		
		ComputeHand(myHand1_param);
		ComputeHand(myHand2_param);
		CompareHandStrength(myHand1_param, myHand2_param);
		++combos;
	}
}
static std::vector<Card> DeleteCardFromVector(Card& card_param, std::vector<Card>& cardList_param)
{
	std::vector<Card> output = cardList_param;
	for (unsigned int i = 0; i < output.size(); i++)
	{
		if (card_param.MyCardFace == output[i].MyCardFace &&
			card_param.MyCardColor == output[i].MyCardColor)
		{
			output.erase(output.begin() + i);
			i = output.size();
		}
	}
	return output;
}
static std::vector<Card> DeleteCardFromVector(std::vector<Card>& cardsToDelete_param, std::vector<Card>& cardList_param)
{
	std::vector<Card> output = cardList_param;
	for (Card card : cardsToDelete_param)
	{
		for (unsigned int i = 0; i < output.size(); i++)
		{
			if (card.MyCardFace == output[i].MyCardFace &&
				card.MyCardColor == output[i].MyCardColor)
			{
				output.erase(output.begin() + i);
				i = output.size();
			}
		}
	}
	return output;
}

static std::vector<Card> GetUsedCardCombos(Hand& myHand1_param, Hand& myHand2_param)
{
	std::vector<Card> output{ myHand1_param.FullHand };

	output.push_back(myHand2_param.FullHand[0]);
	output.push_back(myHand2_param.FullHand[1]);

	return output;
}

static std::vector<Card> GetAllCardCombos()
{
	std::vector<Card> output{};

	std::vector<Card::CardFace> allCardFaces{
		Card::CardFace::Ace ,
		Card::CardFace::King ,
		Card::CardFace::Queen ,
		Card::CardFace::Jack ,
		Card::CardFace::Ten ,
		Card::CardFace::Nine ,
		Card::CardFace::Eight ,
		Card::CardFace::Seven ,
		Card::CardFace::Six ,
		Card::CardFace::Five ,
		Card::CardFace::Four ,
		Card::CardFace::Three ,
		Card::CardFace::Two };

	std::vector<Card::CardColor> allCardColors{
		Card::CardColor::clubs,
		Card::CardColor::diamonds,
		Card::CardColor::hearts,
		Card::CardColor::spades };

	for (unsigned int i = 0; i < allCardFaces.size(); i++)
	{
		for (unsigned int j = 0; j < allCardColors.size(); j++)
		{
			output.push_back(Card(allCardFaces[i], allCardColors[j]));
		}
	}

	return output;
}