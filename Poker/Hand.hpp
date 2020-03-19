//
//  Hand.h
//  Poker
//
//  Created by 宋嘉威 on 3/18/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#ifndef Hand_h
#define Hand_h

#include <vector>
#include <iostream>

#include "Card.hpp"

const unsigned int MAX_CARD_IN_HAND = 7;

enum HandType
{
    HT_NO_HAND,
    HT_HIGH_CARD,
    HT_PAIR,
    HT_TWO_PAIR,
    HT_SET,
    HT_STRAIGHT,
    HT_FLUSH,
    HT_FULL_HOUSE,
    HT_FOUR_OF_A_KIND,
    HT_STRAIGHT_FLUSH
};

typedef struct _HandType
{
    HandType type;
    const Card* PrimaryCard;
    const Card* SecondaryCard;
} HandValue;

class Hand
{
public:
    Hand();
    void AddCard(const Card& card); // When cards are dealt
    const Card& operator[] (int position) const; // For showing cards
    size_t GetCardCount() const {return m_hand.size();}
    
    const HandValue& GetBestHandValue() const {return m_best_hand;}
    std::string GetHandTextualDescription() const;
    std::string ToString() const;
    
private:
    std::vector<Card> m_hand;
    
    // Best hand is calculated when cards added
    HandValue m_best_hand;
    
    void CalculateHandScore();
    const Card* GetCardPtr(int suit, int value) const;
    const Card* GetCardPtrAnySuit(int value)    const;

    const HandValue GetStraightFlushValue() const;
    const HandValue GetFourOfAKindValue()   const;
    const HandValue GetFullHouseValue()     const;
//    const HandValue GetFlushValue()         const;
//    const HandValue GetStraightValue()      const;
//    const HandValue GetSetValue()           const;
//    const HandValue GetTwoPairValue()       const;
//    const HandValue GetPairValue()          const;
//    const HandValue GetHighCardValue()      const;

};

int hand_compare(const Hand* hand1, const Hand* hand2);
std::ostream& operator<< (std::ostream& os, const Hand& hand);


#endif /* Hand_h */
