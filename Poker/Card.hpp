//
//  Card.hpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <iostream>
#include <string>

enum SUIT
{
    CLUB = 0,
    DIAMOND = 1,
    HEART = 2,
    SPADE = 3
};

enum FACE_CARDS
{
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};


const int MIN_CARD_VALUE = 2;
const int MAX_CARD_VALUE = ACE;

const int NUM_SUITS = 4;
const int MIN_SUIT = CLUB;
const int MAX_SUIT = SPADE;


class Card
{
public:
    Card(const int value, const int suit);
    
    const int GetValue () const;
    const int GetSuit () const;
    
    std::string ToString() const;
    
    
    
private:
    int m_value;
    int m_suit;
};

std::ostream& operator << (std::ostream &os, const Card &card);
bool operator == (const Card &card1, const Card &card2);

std::string CardValueToString(const int value);
std::string CardSuitToString(const int suit);

#endif /* Card_h */
