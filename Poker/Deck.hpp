//
//  Deck.hpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Deck_h
#define Deck_h

#include "Card.hp">

Class Deck
{
public:
    Deck()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                m_Deck.push_back(Card(i,j));
            }
        }
    }
    
private:
    vector<Card> m_Deck;
}

#endif /* Deck_h */
