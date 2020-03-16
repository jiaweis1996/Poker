//
//  Player.cpp
//  Poker
//
//  Created by 宋嘉威 on 3/15/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//
#include <assert.h>
#include <iostream>

#include "Player.hpp"

Player::Player(int buyin, int seat)
 : m_stake(buyin)
 , m_seat(seat)
{
    assert(m_stake > 0);
    assert(m_seat > 0);
}

const int Player::Get_Stake() const
{
    return m_stake;
}

const int Player::Get_Seat() const
{
    return m_seat;
}

//TODO: MAX Buyin
void Player::Add_on(int money)
{
    m_stake += money;
}

void Player::Action()
{
    std::cout << "Player " << m_seat << "'s action (stake: " << m_stake << "). (check, fold, bet, all in)" << std::endl;
    
    std::string action;
    
    // Check Player's Action Validity
    while (std::getline(std::cin, action))
    {
        if (CHECK_ACTION(action)) {break;}
    }
    
    if (action == "bet")
    {
        std::cout << "How much?" << std::endl;
        std::string bet_size;
        while (std::getline(std::cin, bet_size))
        {
            // TODO: Bet Size check, larger than formal bet, smaller than player stake
            const int size = std::stoi(bet_size);
            if (CHECK_BET(size))
            {
                std::cout << "Player " << m_seat << " bet " << size << "." << std::endl;
                m_stake -= size;
                break;
            }
        }
    }
    else if (action == "check")
    {
        std::cout << "Player " << m_seat << " check." << std::endl;
    }
    else if (action == "fold")
    {
        std::cout << "Player " << m_seat << " fold." << std::endl;
    }
    else if (action == "all in")
    {
        std::cout << "Player " << m_seat << " all in " << m_stake << "." << std::endl;
        m_stake = 0;
    }

}

void Player::Change_Seat(int new_seat)
{
    assert(new_seat > 0);
    m_seat = new_seat;
}



