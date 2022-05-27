#pragma once
#include <string>
#include<vector>



class Card
{
public:
    enum class CardColor
    {
        clubs = 1,
        hearts = 2,
        diamonds = 3,
        spades = 4
    };

    enum class CardFace
    {

        Empty = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13,
        Ace = 14
    };

    Card(CardFace& CARDFACE, CardColor& CARDCOLOR);
    Card(char& cardFace, char& cardColor);
    Card();
 /*   ~Card();*/

    char ConvertCardFaceToChar();
    char ConvertCardColorToChar();
    CardFace ConvertCharToCardFace(char& cardFace);
    CardColor ConvertCharToCardColor(char& cardColor);
    

public:
    CardFace MyCardFace{};
    CardColor MyCardColor{};
};