//
//  Deck.cpp
//  Poker
//
//  Created by 宋嘉威 on 3/15/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#include <stdio.h>
#include <algorithm>
#include <random>
#include <chrono>

#include "Card.hpp"
#include "Deck.hpp"

Deck::Deck()
  : m_Deck()
{
    for (int value = MIN_CARD_VALUE; value < MAX_CARD_VALUE; value++)
    {
        m_Deck.push_back(Card(value,SPADE));
        m_Deck.push_back(Card(value,HEART));
        m_Deck.push_back(Card(value,CLUB));
        m_Deck.push_back(Card(value,DIAMOND));
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_Deck.begin(), m_Deck.end(), std::default_random_engine(seed));
    
}



void Deck::deal()
{
    
}
