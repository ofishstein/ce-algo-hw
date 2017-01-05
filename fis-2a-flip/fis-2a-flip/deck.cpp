//  Created on and compiled for OSX with xCode
//
//  Contains implementation of the deck class.
//
//  deck.cpp
//  fis-2a-flip
//
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <stdio.h>
#include "deck.h"
#include "d_except.h"
#include "d_random.h"

using namespace std;

// initializes a deck of 52 cards in order (2 - A) (clubs - spades)
// builds deck in reverse so stored in order
deck::deck()
{
    string suits[] = {"clubs", "diamonds", "hearts", "spades"};
    string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "jack",
        "queen", "king", "ace"};
    
    // initialize head to null for the new list
    head = NULL;
    
    // iterate through the four suits from spades to clubs
    for (int i = 3; i > -1; i--)
    {
        // iterate through the 14 values from A to 2
        for (int j = 12; j > -1; j--)
        {
            // create a new card with value j and suit i
            card newCard = card(values[j], suits[i]);
            
            // create a new node with the new card
            node<card> * newNode = new node<card>(newCard, head);
            
            // sets newNode to head
            head = newNode;
        }
    }
}

//initializes a deck with a head;
deck::deck(node<card>* newHead){
    head = newHead;
}

// copy constructor
deck::deck(const deck & newDeck){
    head = newDeck.head;
}

// destructor
deck::~deck()
{
    node<card> * next;
    
    // delete nodes
    while (head != NULL) {
        next = head->next;
        delete head;
        head = next;
    }
}

// print out the deck
ostream& operator<<(ostream & ostr, const deck & deck)
{
    // initialize the current node
    node<card> * current;
    current = deck.head;
    
    // iterate through link list
    while(current != NULL)
    {
        // print the node
        ostr << current->nodeValue << endl;
        
        // switch current node to the next node
        current = current->next;
    }
    
    // return outstream
    return ostr;
}

// assignment operator
deck& deck::operator=(const deck & rhs)
{
    // set head and return object
    head = rhs.head;
    return *this;
}

// deals a card by value and deletes it
const card deck::deal()
{
    // temporary node
    node<card> * nodeToDelete = head;
    
    // get value
    card topCard = nodeToDelete->nodeValue;
    
    // switch head and delet old
    head = head->next;
    delete nodeToDelete;
    
    // return card
    return topCard;
    
}

// adds a card to the bottom of the deck
void deck::replace(card newCard)
{
    // initialize the current node
    node<card> * current;
    current = head;
    
    // iterate through link list to get to bottom
    while(current->next != NULL)
    {
        // switch current node to the next node
        current = current->next;
    }
    
    current->next = new node<card>(newCard, NULL);
}

//shuffles the cards
// sets the head to the result of the recursive merge shuffle
void deck::shuffle()
{
    // head is the result of a recursive shuffle
    head = recursiveShuffle(head);
}

// shuffle the linked list recursively for O(nlogn)
// adapted from merge sort algorithm to shuffle randomly
node<card> * deck::recursiveShuffle(node<card> * head)
{
    // check if valid head
    if (head == NULL){
        throw referenceError("Head is null.");
    }
    
    // if next is null return head
    if (head->next == NULL)
    {
        return head;
    }
    
    // get the middle value to seperate list into two
    node<card> * middle = getMiddle(head);
    // create the right list
    node<card> * rightNode = middle->next;
    // seperate the left list from the right list
    middle->next = NULL;
    
    // merge the results of the recursive shuffles on both lists
    node<card> * mergedResult = shuffledMerge(recursiveShuffle(head), recursiveShuffle(rightNode));
    
    // return the results
    return mergedResult;
}

// merge helper function for recursive shuffle
// merges by randomly selecting from two lists
node<card> * deck::shuffledMerge(node<card> * leftNode, node<card> * rightNode)
{
    // create random number generator
    randomNumber random = randomNumber();
    
    // create a dummyHead with a dummy card to build the list off of
    node<card> * dummyHead = new node<card>(card("2", "spades"));
    node<card> * currentNode = dummyHead;
    
    // iterate until both lists are null
    while (leftNode != NULL || rightNode != NULL)
    {
        // generate a random number to determine which list to merge
        int rand = (int)random.random(2);
        
        // if 0 try leftNode else rightNode
        if (rand == 0)
        {
            // if leftNode isn't null merge it else merge right
            if (leftNode != NULL)
            {
                currentNode->next = leftNode;
                leftNode = leftNode->next;
            }
            else
            {
                currentNode->next = rightNode;
                rightNode = rightNode->next;
            }
        }
        else
        {
            // if rightNode isn't null merge it else merge left
            if (rightNode != NULL)
            {
                currentNode->next = rightNode;
                rightNode = rightNode->next;
            }
            else
            {
                currentNode->next = leftNode;
                leftNode = leftNode->next;
            }
        }
        
        // increment current node
        currentNode = currentNode->next;
    }
    
    //return list without dummy node
    return dummyHead->next;
}

// helper function for recursive shuffle
// finds the node in the middle of the linked list to seperate lists in two
// for recursive shuffling
node<card> * deck::getMiddle(node<card> * head)
{
    // if head is last element in list no middle
    if (head->next == NULL){
        return head;
    }
    
    //initialize fast and slow pointers
    node<card> * fast, * slow;
    fast = slow = head;
    
    // iterate until the middle
    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // return middle
    return slow;
}

