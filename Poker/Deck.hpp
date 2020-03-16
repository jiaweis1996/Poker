//
//  Deck.hpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Deck_h
#define Deck_h

#include <vector>

#include "Card.hpp"


class Deck
{
public:
    Deck();
    
    //void deck_shuffle(std::vector<Card> Card_Vector);

    void deal();
    
    
    std::vector<Card> m_Deck;
private:
    
};

#endif /* Deck_h */
