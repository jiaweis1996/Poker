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
#include "Player.hpp"


int main()
{
    std::unique_ptr<Deck> mydeck;
    mydeck.reset(new Deck());
    
   // Deck my_deck();
    
    Player p1 = Player(300,1);
    Player p2 = Player(300,2);
    
    p1.Action();
    p2.Action();
    
    
    std::cout<< "haha" << std::endl;
    
    return 0;
}
