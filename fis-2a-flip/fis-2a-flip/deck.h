//  Created on and compiled for OSX with xCode
//
//  Contains declaration of the deck class.
//
//  deck.h
//  fis-2a-flip
//
//  Created by Oliver Fishstein on 9/25/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef deck_h
#define deck_h

#include "card.h"
#include "d_node.h"

using namespace std;

class deck
{
    public:
    
    // initializes a deck of 52 cards in order (2 - A) (clubs - spades)
    // builds deck in reverse so stored in order
    deck();
    
    //initializes a deck with a head;
    deck(node<card>* newHead);
    
    // copy constructor
    deck(const deck & newDeck);
    
    // destructor
    ~deck();
    
    // print out the deck
    friend ostream& operator<<(ostream & ostr, const deck & deck);
    
    // assignement operator
    deck & operator=(const deck & rhs);
    
    // deals a card by value and deletes it
    const card deal();
    
    // adds a card to the bottom of the deck
    void replace(card newCard);
    
    // shuffles the cards
    // sets the head to the result of the recursive merge shuffle
    void shuffle();

    private:
    
    // member data
    node<card> * head;
    
    // shuffle the linked list recursively for O(nlogn)
    // adapted from merge sort algorithm to shuffle randomly
    node<card> * recursiveShuffle(node<card> * head);
    
    // merge helper function for recursive shuffle
    // merges by randomly selecting from two lists
    node<card> * shuffledMerge(node<card> * leftNode, node<card> * rightNode);
    
    // helper function for recursive shuffle
    // finds the node in the middle of the linked list to seperate lists in two
    // for recursive shuffling
    node<card> * getMiddle(node<card> * head);
    
};

#endif /* deck_h */
