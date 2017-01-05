//  Created on and compiled for OSX with xCode
//
//  Contains declaration of the card class.
//
//  card.h
//  fis-2a-flip
//
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef card_h
#define card_h

#include <string>
#include <iostream>

using namespace std;

class card
{
    public:
    
    // construct a new card with a value and suit
    // values as string in order:
    //     2, 3, 4, 5, 6, 7, 8, 9, 10, jack, queen, king, ace
    // suit as a stringin order:
    //     clubs, diamonds, hearts, spades
    card(const string & newValue, const string & newSuit);
    
    // copy constructor
    card(const card & newCard);
    
    // set the value of a card
    void setValue(const string & newValue);
    
    // set the value of a suit
    void setSuit(const string & newSuit);
    
    // get the value of a card
    const string getValue();
    
    // get the suit of a card
    const string getSuit();
    
    // print out the card
    friend ostream& operator<<(ostream & ostr, const card & card);
    
    // overloaded assignment operator
    card & operator=(const card & rhs);
    
    
    private:
    
    // member data
    string value;
    string suit;
    
    // check if value is in range
    const bool valueValid(const string & valueToCheck);
    
    // check if suite is valid
    const bool suitValid(const string & suiteToCheck);
};


#endif /* card_h */
