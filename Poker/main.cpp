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
#include "Hand.hpp"


int main()
{
    //Card (value,suit)
//    std::unique_ptr<Deck> mydeck;
//    mydeck.reset(new Deck());
//
//   // Deck my_deck();
//
//    Player p1 = Player(300,1);
//    Player p2 = Player(300,2);
//
//    p1.Action();
//    p2.Action();
    
    Hand myhand;
    
    Card c1 = Card(2,1);
    Card c2 = Card(2,0);
    Card c3 = Card(2,3);
    Card c4 = Card(6,2);
    Card c5 = Card(6,1);
    Card c6 = Card(7,0);
    
    myhand.AddCard(c1);
    myhand.AddCard(c2);
    myhand.AddCard(c3);
    myhand.AddCard(c4);
    myhand.AddCard(c5);
    myhand.AddCard(c6);
    
    std::string result = myhand.GetHandTextualDescription();

    
    std::cout<< result << std::endl;
    
    return 0;
}
