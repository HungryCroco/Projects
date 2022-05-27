#pragma once
#include <iostream>
#include "Card.h"
#include "Hand.h"

Hand ComputeHand(Hand& myHand_param);
bool CheckForFlush(Hand& myHand_param);

void ComputeFHandQuads(Hand& myHand_param);
void ComputeAllFlushes(Hand& myHand_param);
void ComputeStreight(Hand& myHand_param);
void ComputeTRIPSminus(Hand& myHand_param);

void OrderHandByCardFace(Hand& myHand_param);
void OrderRCs(Hand& myHand_param);

void ClearHand(Hand& myHand_param);
