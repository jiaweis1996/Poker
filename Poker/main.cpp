//
//  main.cpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>

#include "Deck.hpp"


int main()
{
    std::unique_ptr<Deck> mydeck;
    mydeck.reset(new Deck());
    
   // Deck my_deck();
    
    std::vector<Card> my_card = mydeck-> m_Deck;
    
    Card test = my_card[0];
    
    
    std::cout<< test << std::endl;
    
    return 0;
}
