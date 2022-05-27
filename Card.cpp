#pragma once
#include "Card.h"
#include <iostream>



Card::Card(CardFace& CARDFACE , CardColor& CARDCOLOR)
	:MyCardFace{CARDFACE} , MyCardColor{ CARDCOLOR }
{
}

Card::Card(char& cardFace, char& cardColor)
	: MyCardFace{ ConvertCharToCardFace(cardFace) }, 
    MyCardColor{ ConvertCharToCardColor(cardColor) }
{
}
Card::Card()
{}

//Card::~Card()
//{
//    
//    /*std::cout << "CARD DESTR CALLED" << std::endl;*/
//}



char Card::ConvertCardFaceToChar() 
{
    switch (MyCardFace)
    {
    case CardFace::Two:
        return '2';
        break;
    case CardFace::Three:
        return '3';
        break;
    case CardFace::Four:
        return '4';
        break;
    case CardFace::Five:
        return '5';
        break;
    case CardFace::Six:
        return '6';
        break;
    case CardFace::Seven:
        return '7';
        break;
    case CardFace::Eight:
        return '8';
        break;
    case CardFace::Nine:
        return '9';
        break;
    case CardFace::Ten:
        return 'T';
        break;
    case CardFace::Jack:
        return 'J';
        break;
    case CardFace::Queen:
        return 'Q';
        break;
    case CardFace::King:
        return 'K';
        break;
    case CardFace::Ace:
        return 'A';
        break;

    }
    // return CardFace(Empty);
}

char Card::ConvertCardColorToChar()
{
    switch (MyCardColor)
    {
    case CardColor::spades:
        return 's';
        break;
    case CardColor::diamonds:
        return 'd';
        break;
    case CardColor::hearts:
        return 'h';
        break;
    case CardColor::clubs:
        return 'c';
        break;
    }
    // return CardFace(Empty);
}

Card::CardFace Card::ConvertCharToCardFace(char& cardFace)
{
    switch (cardFace)
    {
    case '2':
        return CardFace::Two;
        break;
    case '3':
        return CardFace::Three;
        break;
    case '4':
        return CardFace::Four;
        break;
    case '5':
        return CardFace::Five;
        break;
    case '6':
        return CardFace::Six;
        break;
    case '7':
        return CardFace::Seven;
        break;
    case '8':
        return CardFace::Eight;
        break;
    case '9':
        return CardFace::Nine;
        break;
    case 'T':
        return CardFace::Ten;
        break;
    case 'J':
        return CardFace::Jack;
        break;
    case 'Q':
        return CardFace::Queen;
        break;
    case 'K':
        return CardFace::King;
        break;
    case 'A':
        return CardFace::Ace;
        break;

    }
    // return CardFace(Empty);
}

Card::CardColor Card::ConvertCharToCardColor(char& cardColor)
{
    switch (cardColor)
    {
    case 's':
        return CardColor::spades;
        break;
    case 'd':
        return CardColor::diamonds;
        break;
    case 'h':
        return CardColor::hearts;
        break;
    case 'c':
        return CardColor::clubs;
        break;
    }
    // return CardFace(Empty);
}
