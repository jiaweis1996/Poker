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

const int Card::GetSuit() const
{
    return m_suit;
}

const int Card::GetValue() const
{
    return m_value;
}

std::string Card::ToString() const
{
    std::string retval;
    if (m_value <= 10)
        retval = std::to_string(m_value);
    else if (m_value == JACK)
        retval = "J";
    else if (m_value == QUEEN)
        retval = "Q";
    else if (m_value == KING)
        retval = "K";
    else if (m_value == ACE)
        retval = "A";
    
    switch (m_suit)
    {
        case CLUB:
            retval += "c";
            break;
        case DIAMOND:
            retval += "d";
            break;
        case HEART:
            retval += "h";
            break;
        case SPADE:
            retval += "s";
            break;
    }
    
    return retval;
}

std::ostream& operator << (std::ostream &os, const Card &card)
{
    os << card.ToString();
    return os;
}

bool operator == (const Card &card1, const Card &card2)
{
    return (card1.GetSuit() == card2.GetSuit() && card1.GetValue() == card2.GetValue());
}

std::string CardValueToString(const int value)
{
    std::string retval;
    if (value <= 10)
        retval = std::to_string(value);
    else if (value == JACK)
        retval = "J";
    else if (value == QUEEN)
        retval = "Q";
    else if (value == KING)
        retval = "K";
    else if (value == ACE)
        retval = "A";
    
    return retval;
}
    
std::string CardSuitToString(const int suit)
{
    switch (suit)
    {
        case (CLUB):
            return "Clubs";
        case (SPADE):
            return "Spades";
        case (DIAMOND):
            return "Diamonds";
        default:
            return "Hearts";
    }
}
