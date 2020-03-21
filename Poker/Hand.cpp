//
//  Hand.cpp
//  Poker
//
//  Created by 宋嘉威 on 3/18/20.
//  Copyright © 2020 宋嘉威. All rights reserved.
//

#include <vector>
#include <stdio.h>
#include <assert.h>
#include <map>

#include "Hand.hpp"
#include "Card.hpp"

const HandValue HANDVALUE_NO_HAND =
{
  HT_NO_HAND,
    nullptr,
    nullptr
};

Hand::Hand()
    :m_hand()
{
    m_hand.reserve(MAX_CARD_IN_HAND);
}

void Hand::AddCard(const Card& card)
{
    assert(m_hand.size() <= MAX_CARD_IN_HAND);
    m_hand.push_back(card);
    CalculateHandScore();
}

void Hand::CalculateHandScore()
{
   // typedef const HandValue (Hand::*scoringFunctionPtr) () const;
    typedef const HandValue (Hand::*scoringFunctionPtr)() const;
    
    //declare an array of scoring functions...
    scoringFunctionPtr funcs[] = {
            &Hand::GetStraightFlushValue,
            &Hand::GetFourOfAKindValue,
            &Hand::GetFullHouseValue,
            &Hand::GetFlushValue,
            &Hand::GetStraightValue,
            &Hand::GetSetValue,
            &Hand::GetTwoPairValue,
            &Hand::GetPairValue,
            &Hand::GetHighCardValue
    };
    
    HandValue hand_score;
    
    //invoke until one returns
    for (int i = 0; i < 9; i++)
    {
        hand_score = (this->*(funcs[i]))();
        
        if (hand_score.type != HT_NO_HAND)
            break;
    }
    m_best_hand = hand_score;
}

std::string Hand::GetHandTextualDescription() const
{
    if (m_hand.size() == 0)
        return "No Cards in hand";

    std::string firstCardStr = CardValueToString(m_best_hand.PrimaryCard->GetValue());

    std::string secondCardStr = "";

    if (m_best_hand.SecondaryCard != nullptr)
        secondCardStr = CardValueToString(m_best_hand.SecondaryCard->GetValue());

    switch(m_best_hand.type) {
        case (HT_HIGH_CARD):
            return "High Card of " + firstCardStr;
        case (HT_PAIR):
            return "Pair of " + firstCardStr + "s";
        case (HT_TWO_PAIR):
            return "Two Pair of " + firstCardStr + "s and " + secondCardStr + "s";
        case (HT_STRAIGHT):
            return "Straight, " + firstCardStr + " high";
        case (HT_SET):
            return "Three of a Kind with " + firstCardStr + "s";
        case (HT_FLUSH):
            return "Flush with " + CardSuitToString(m_best_hand.PrimaryCard->GetSuit());
        case (HT_FULL_HOUSE):
            return "Full House, " + firstCardStr + "s full of " + secondCardStr + "s";
        case (HT_FOUR_OF_A_KIND):
            return "Four of a Kind with " + firstCardStr + "s";
        case (HT_STRAIGHT_FLUSH):
            if (m_best_hand.PrimaryCard->GetValue() == ACE)
                return "Royal Flush!!! (" + CardSuitToString(m_best_hand.PrimaryCard->GetSuit()) + ")";
            else
                return "Straight Flush of " +
                        CardSuitToString(m_best_hand.PrimaryCard->GetSuit()) +
                        " " + firstCardStr + " high";
        default:
            throw new std::runtime_error("This can't happen."); //to silence gcc "may return void warning"
            //clause never hit, because with no cards I return early at top of function, with one card
            //I hit the HT_HIGH_CARD case.
    }
}

const Card* Hand::GetCardPtr(int suit, int value) const
{
    for (const Card& card : m_hand)
    {
        if (card.GetSuit() == suit && card.GetValue() == value)
            return &card;
    }
    return nullptr;
}

const Card* Hand::GetCardPtrAnySuit(int value) const
{
    const Card* tmp = GetCardPtr(HEART, value);
    if (tmp == nullptr)
        tmp = GetCardPtr(SPADE, value);
    if (tmp == nullptr)
        tmp = GetCardPtr(CLUB, value);
    if (tmp == nullptr)
        tmp = GetCardPtr(DIAMOND, value);
    assert(tmp != nullptr);
    return tmp;
}

std::string Hand::ToString() const
{
    std::string s;
    bool first = true;
    
    s = std::to_string(m_hand.size());
    s += " cards: ";
    
    for (const Card&c : m_hand)
    {
        if (!first)
            s += ", ";
        s += c.ToString();
        
        first = false;
    }
    
    return s;
}

const Card& Hand::operator[](int position) const
{
    assert(position >= 0);
    assert(m_hand.size() > (unsigned int) position);
    return m_hand[position];
}

const HandValue Hand::GetStraightFlushValue() const
{
    // Make Element 0 be 0, more striaghtforward
    int NestValue[NUM_SUITS][MAX_CARD_VALUE+1];
    
    // initialize
    for (int suit = 0; suit < NUM_SUITS; suit++)
    {
        for (int val = 0; val < (MAX_CARD_VALUE+1); val++)
        {
            NestValue[suit][val] = 0;
        }
    }
    
    for (const Card& card : m_hand)
    {
        int c_suit = card.GetSuit();
        int c_val  = card.GetValue();
        
        if (card.GetValue() == ACE) // ACE HIGH OR LOW
        {
            NestValue[c_suit][1]++;
            NestValue[c_suit][c_val]++;
        }
        else
        {
            NestValue[c_suit][c_val]++;
        }
    }
    
    int seq = 0;
    int highestSuitSoFar  = -1;
    int highestValueSoFar = -1;
    
    for (int suit = 0; suit < NUM_SUITS; suit++)
    {
        for (int val = 1; val < (MAX_CARD_VALUE+1); val++)
        {
            if (NestValue[suit][val] == 0)
            {
                seq = 0;
            }
            else
            {
                seq++;
                if (seq >= 5)
                {
                    highestSuitSoFar  = suit;
                    highestValueSoFar = val;
                }
            }
        }
        seq = 0;
    }
    
    if (highestValueSoFar != -1)
    {
        HandValue retval;
        
        retval.type = HT_STRAIGHT_FLUSH;
        retval.PrimaryCard = GetCardPtr(highestSuitSoFar, highestValueSoFar);
        retval.SecondaryCard = nullptr;
        
        return retval;
    }
    else
    {
        return HANDVALUE_NO_HAND;
    }
}

const HandValue Hand::GetFourOfAKindValue() const
{
    std::map<int,int> occur;
    
    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; i++)
    {
        occur[i] = 0;
    }
    
    for (const Card& card: m_hand)
    {
        occur[card.GetValue()]++;
    }
    
    for (auto iter = occur.rbegin(); iter != occur.rend(); ++iter)
    {
        if (iter->second == 4)
        {
            HandValue retval;
            retval.type = HT_FOUR_OF_A_KIND;
            retval.PrimaryCard = GetCardPtrAnySuit(iter->first); //suit not matter here
            retval.SecondaryCard = nullptr;
            return retval;
        }
    }
    
    return HANDVALUE_NO_HAND;
}

const HandValue Hand::GetFullHouseValue() const
{    
    std::map <int,int> occur;

    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; i++)
    {
        occur[i] = 0;
    }
    
    for (const Card& card: m_hand)
    {
        occur[card.GetValue()]++;
    }
    
    int threes_value = -1;
    int twos_value = -1;
    
    for (auto iter = occur.rbegin(); iter != occur.rend(); ++iter)
    {
        if (iter->second >= 3 && threes_value == -1)
            threes_value = iter->first;
        else if (iter->second >= 2 && twos_value == -1)
            twos_value   = iter->first;
    }
    
    if (threes_value != -1 && twos_value != -1)
    {
        HandValue retval;
        retval.type = HT_FULL_HOUSE;
        
        retval.PrimaryCard   = GetCardPtrAnySuit(threes_value);
        retval.SecondaryCard = GetCardPtrAnySuit(twos_value);
        
        return retval;
    }
    else
    {
        return HANDVALUE_NO_HAND;
    }
}

const HandValue Hand::GetFlushValue() const
{
    std::map <int,int> occur = {
        {CLUB , 0},
        {DIAMOND , 0},
        {HEART, 0},
        {SPADE, 0}
        
    };
    
    // Count card by suit
    for (const Card& card: m_hand)
    {
        occur[card.GetSuit()]++;
    }
    
    const Card* best_card = nullptr;
    
    for (int suit = 0; suit < NUM_SUITS; ++suit)
    {
        // Found Flush
        if (occur[suit] >= 5)
        {
            // find highest card
            for (const Card& card: m_hand)
            {
                if (card.GetSuit() == suit)
                {
                    if (best_card == nullptr || best_card ->GetValue() < card.GetValue())
                        best_card = &card;
                }
            }
            
            assert(best_card != nullptr);
            
            HandValue retval;
            retval.type = HT_FLUSH;
            retval.PrimaryCard = best_card;
            retval.SecondaryCard = nullptr;
            return retval;
        }
    }
    return HANDVALUE_NO_HAND;
}

const HandValue Hand::GetStraightValue() const
{
    std::map<int,int> occur;
    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; ++i)
        occur[i] = 0;
    
    for (const Card& card: m_hand)
    {
        if (card.GetValue() == ACE) // Low Ace or High Ace
        {
            occur[1]++;
            occur[ACE]++;
        }
        else
        {
            occur[card.GetValue()]++;
        }
    }
    
    int seq = 0;
    int highestSoFar = -1;
    
    for (auto iter = occur.begin(); iter != occur.end(); iter++)
    {
        if (iter->second == 0)
        {
            seq = 0;
        }
        else
        {
            seq++;
            if (seq >= 5)
                highestSoFar = iter->first;
        }
    }
    
    if (highestSoFar != -1)
    {
        HandValue retval;
        retval.type = HT_STRAIGHT;
        retval.PrimaryCard = GetCardPtrAnySuit(highestSoFar);
        retval.SecondaryCard = nullptr;
        return retval;
    }
    else
    {
        return HANDVALUE_NO_HAND;
    }
}

const HandValue Hand::GetSetValue() const
{
    std::map<int,int> occur;
    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; ++i)
    {
        occur[i] = 0;
    }
    
    for (const Card& card: m_hand)
    {
        occur[card.GetValue()]++;
    }
    
    for (auto iter = occur.rbegin(); iter != occur.rend(); iter++)
    {
        if (iter->second == 3)
        {
            HandValue retval;
            retval.type = HT_SET;
            retval.PrimaryCard = GetCardPtrAnySuit(iter->first);
            retval.SecondaryCard = nullptr;
            return retval;
        }
    }
    
    return HANDVALUE_NO_HAND;
}

const HandValue Hand::GetTwoPairValue() const
{
    std::map <int,int> occur;
    
    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; ++i)
    {
        occur[i] = 0;
    }
    
    for (const Card& card: m_hand)
    {
        occur[card.GetValue()]++;
    }
    
    int first_pair_value = -1;
    
    for (auto iter = occur.rbegin(); iter != occur.rend(); iter++)
    {
        if (iter->second == 2)
        {
            if (first_pair_value == -1)
                first_pair_value = iter->first;
            else
            {
                HandValue retval;
                retval.type = HT_TWO_PAIR;
                retval.PrimaryCard = GetCardPtrAnySuit(first_pair_value);
                retval.SecondaryCard = GetCardPtrAnySuit(iter->first);
                return retval;
            }
        }
    }
    return HANDVALUE_NO_HAND;
}

const HandValue Hand::GetPairValue() const
{
    std::map <int,int> occur;
    for (int i = MIN_CARD_VALUE; i < MAX_CARD_VALUE; ++i)
    {
        occur[i] = 0;
    }
    
    for (const Card& card: m_hand)
    {
        occur[card.GetValue()]++;
    }
    
    for (auto iter = occur.rbegin(); iter != occur.rend(); iter++)
    {
        if (iter->second == 2)
        {
            HandValue retval;
            retval.type = HT_PAIR;
            retval.PrimaryCard = GetCardPtrAnySuit(iter->first);
            retval.SecondaryCard = nullptr;
            return retval;
        }
    }
    return HANDVALUE_NO_HAND;
}

const HandValue Hand::GetHighCardValue() const
{
    const Card* best_card = nullptr;
    
    for (const Card& card: m_hand)
    {
        if (best_card == nullptr)
            best_card = &card;
        else if (best_card->GetValue() < card.GetValue())
            best_card = &card;
    }
    
    HandValue retval;
    retval.type = HT_HIGH_CARD;
    retval.PrimaryCard = best_card;
    retval.SecondaryCard = nullptr;
    return retval;
}

int hand_compare(const Hand* hand1, const Hand* hand2)
{
    const HandValue& score1 = hand1->GetBestHandValue();
    const HandValue& score2 = hand2->GetBestHandValue();
    
    if (score1.type > score2.type)
        return -1;
    else if (score1.type < score2.type)
        return 1;
    
    // Same type of hands, need to compare high cards. (e.g: straight or flush)
    if (score1.PrimaryCard->GetValue() > score2.PrimaryCard->GetValue())
        return -1;
    else if (score1.PrimaryCard->GetValue() < score2.PrimaryCard->GetValue())
        return 1;
    
    // Primary Card equal, compare secondary card
    
    if (score1.type == HT_FULL_HOUSE || score1.type == HT_TWO_PAIR)
    {
        if (score1.SecondaryCard->GetValue() > score2.SecondaryCard->GetValue())
            return -1;
        else if (score1.SecondaryCard->GetValue() < score2.SecondaryCard->GetValue())
            return 1;
    }
    
    // No Need to Compare suit
    return 0; // exact same hand value
}

std::ostream& operator <<(std::ostream& os, const Hand& hand)
{
    os << hand.ToString();
    return os;
}





