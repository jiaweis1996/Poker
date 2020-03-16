//
//  Player.hpp
//  Poker
//
//  Created by 宋嘉威 on 3/15/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <vector>
#include <stdio.h>

#include "Card.hpp"


class Player
{
public:
    Player(int buy_in, int seat);
    const int Get_Stake() const;
    const int Get_Seat() const;
    
    void Add_on(int money);
    void Action();
    void Change_Seat(int new_seat);
    
    std::vector<Card> m_player_card;
private:
    int m_stake;
    int m_seat;
    
    bool CHECK_ACTION(std::string action)
    {
        if (action != "check" && action != "fold" && action != "bet" && action != "all in")
        {
            std::cout << "INVALID ACTION!" << std::endl;
            std::cout << "Please type 'check' or 'fold' or 'bet' or 'all in'." << std::endl;
            return false;
        }
        else
        {
            return true;
        }
    }
    
    bool CHECK_BET(const int bet_size)
    {
        if (bet_size < 0 || bet_size > m_stake)
        {
            std::cout << "Bet Size should at least double the former bet and no more than your current stake." << std::endl;
            return false;
        }
        else
        {
            return true;
        }
    }
};



#endif /* Player_hpp */
