//
//  Card.cpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//
#include <assert.h>

#include "Card.hpp"

Card::Card(const int value, const int suit)
 : m_value(value)
 , m_suit(suit)
{
    assert(m_suit == HEART || m_suit == CLUB || m_suit == SPADE || m_suit == DIAMOND);
    assert(m_value >= MIN_CARD_VALUE && m_value <= MAX_CARD_VALUE);
}

const int Card::get_suit() const
{
    return m_suit;
}

const int Card::get_value() const
{
    return m_value;
}

std::string Card::ToString() const
{
    std::string revert;
    if (m_value <= 10)
        revert = std::to_string(m_value);
    else if (m_value == JACK)
        revert = "J";
    else if (m_value == QUEEN)
        revert = "Q";
    else if (m_value == KING)
        revert = "K";
    else if (m_value == ACE)
        revert = "A";
    
    switch (m_suit)
    {
        case CLUB:
            revert += "c";
            break;
        case DIAMOND:
            revert += "d";
            break;
        case HEART:
            revert += "h";
            break;
        case SPADE:
            revert += "s";
            break;
    }
    
    return revert;
}

std::ostream& operator << (std::ostream &os, const Card &card)
{
    os << card.ToString();
    return os;
}

bool operator == (const Card &card1, const Card &card2)
{
    return (card1.get_suit() == card2.get_suit() && card1.get_value() == card2.get_value());
}

//std::string CardValueToString(const int value);
//std::string CardSuitToString(const int suit);
