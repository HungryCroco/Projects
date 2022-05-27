#pragma once
#include "ComputeHandPower.h"
#include <iostream>
//#include "Card.h"
//#include "Hand.h"
#include <tuple>
#include <vector>

static std::vector<Card> GetAllCardCombos();
static std::vector<Card> GetUsedCardCombos(Hand& myHand1_param, Hand& myHand2_param);
static std::vector<Card> DeleteCardFromVector(Card& card_param, std::vector<Card>& cardList_param);
static std::vector<Card> DeleteCardFromVector(std::vector<Card>& cardsToDelete_param, std::vector<Card>& cardList_param);

void CompareHandStrength(Hand& myHand1_param, Hand& myHand2_param);
float ComputeOdds(Hand& myHand1_param, Hand& myHand2_param);
void ComputeOddsRiver(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param );

void SimulateFlop(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param);
void SimulateTurn(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param);
void SimulateRiver(Hand& myHand1_param, Hand& myHand2_param, std::vector<Card> combosLeft_param);

