//  Created on and compiled for OSX with xCode
//
//  Contains implementation of the card class.
//
//  card.cpp
//  fis-2a-flip
//
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <stdio.h>
#include "card.h"
#include "d_except.h"

// check if value is in range
const bool card::valueValid(const string & valueToCheck)
{
    return ((valueToCheck == "2") || (valueToCheck == "3") ||
            (valueToCheck == "4") || (valueToCheck == "5") ||
            (valueToCheck == "6") || (valueToCheck == "7") ||
            (valueToCheck == "8") || (valueToCheck == "9") ||
            (valueToCheck == "10") || (valueToCheck == "jack") ||
            (valueToCheck == "queen") || (valueToCheck == "king") ||
            (valueToCheck == "ace"));
}

// check if suite is valid
const bool card::suitValid(const string & suiteToCheck)
{
    return ((suiteToCheck == "clubs") || (suiteToCheck == "diamonds") || (suiteToCheck == "hearts") || (suiteToCheck == "spades"));
}


// construct a new card with a value and suit
// enum value as an int from 2 - 14 where 11 - 14 represents in order:
//     jack, queen, king, ace
// enum suit as a int from 1 - 4 in order:
//     clubs, diamonds, hearts, spades
card::card(const string & newValue, const string & newSuit)
{
    // check if value is in range
    if (!valueValid(newValue))
    {
        throw range_error("card value out of range");
    }
    
    // check if suit is in range
    if (!suitValid(newSuit))
    {
        throw range_error("card suit out of range");
    }
    
    // set values
    value = newValue;
    suit = newSuit;
}

// copy constructor
card::card(const card & newCard)
{
    // set values
    value = newCard.value;
    suit = newCard.suit;
}

// set the value of a card
void card::setValue(const string & newValue)
{
    // check if value is in range
    if (!valueValid(newValue))
    {
        throw range_error("card value out of range");
    }
    
    // set value
    value = newValue;
}

// set the suit of a card
void card::setSuit(const string & newSuit)
{
    // check if suit is in range
    if (!suitValid(newSuit))
    {
        throw range_error("card suit out of range");
    }
    
    // set suit
    suit = newSuit;
}

// get the value of a card
const string card::getValue()
{
    return value;
}

// get the suit of a card
const string card::getSuit()
{
    return suit;
}

// print out the card
ostream& operator<<(ostream & ostr, const card & card)
{
    // print the card
    ostr << card.value << " of " << card.suit;
    
    //return output stream
    return ostr;
}

// overloaded assignment operator
card & card::operator=(const card & rhs)
{
    value = rhs.value;
    suit = rhs.suit;
    return *this;
}
