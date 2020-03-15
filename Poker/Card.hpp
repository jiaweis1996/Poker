//
//  Card.hpp
//  Poker
//
//  Created by 宋嘉威 on 3/14/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <string>

struct Color
{
    
}

class Card
{
public:
    Card(int value, std::string color)
    : m_value(value)
    , m_color(color)
    {
        
    }
private:
    int m_value;
    std::string m_color;
};

#endif /* Card_h */
