//  Created on and compiled for OSX with xCode
//
//  Contains main function that creates a deck and prints it out.
//
//  main.cpp
//  fis-2a-flip
//.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <iostream>
#include "deck.h"

using namespace std;

void playFlip(deck & newDeck);

int main(int argc, const char * argv[])
{
    try {
        deck newGame = deck();
        
        // it wasn't clear if this should be removed so I left it in from 2a
        cout << newGame << endl;
        
        // plays a game of flip
        playFlip(newGame);
        
    } catch (const range_error & re) {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }

    // return with no errors
    return 0;
}

void playFlip(deck & newDeck)
{
    // initialize a new game
    int points = 0;
    
    // print the instructions and rules
    cout << "Let's play Flip! "
        << "Try to score the most points by drawing cards until you want to stop.\n\n"
        << "Scoring rules:\n- 10 points for an ace.\n"
        << "- 5 points for a king, queen, or jack.\n"
        << "- 0 points for an 8, 9, or 10\n- Lose half your points for a 7.\n"
        << "- Lose all your points for a 2, 3, 4, 5, or 6\n"
        << "- Recieve one point extra, in addition to the above, if the card is a heart.\n"
        << endl;
    
    // shuffle the deck 3 times
    for (int i = 0; i < 3; i++)
    {
        newDeck.shuffle();
    }
    
    // enter game loop
    while(true)
    {
        // prompt user for response
        string response;
        cout << "Do you want to draw a card? (Enter 'y' or 'n)" << endl;
        cin >> response;
        
        // check if the user said no or yes to dealing a card or if response was
        // invalid. break if no. enter game logic if yes. redo loop if invalid.
        if (response == "n") {
            // exit loop
            break;
        }
        else if (response == "y")
        {
            // get the top card
            card  deltCard = newDeck.deal();
            // put it back on the bottom of the deck
            newDeck.replace(deltCard);
            // print out card
            cout << deltCard << endl;
            
            // enter scoring conditions - no condition for 8,9, or 10 because user
            // doesn't gain or lose points
            if (deltCard.getValue() == "ace")
            {
                // add 10 points if ace
                points += 10;
            }
            else if (deltCard.getValue() == "king" || deltCard.getValue() == "queen"||
                     deltCard.getValue() == "jack")
            {
                // add 5 points if king, queen, or jack
                points += 5;
            }
            else if (deltCard.getValue() == "7")
            {
                // lose half the points if 7
                points = points - (points / 2);
            } else if (deltCard.getValue() == "2" || deltCard.getValue() == "3" ||
                       deltCard.getValue() == "4" || deltCard.getValue() == "5" ||
                       deltCard.getValue() == "6") {
                // reset points if 2, 3, 4, 5, or 6
                points = 0;
            }
            
            if (deltCard.getSuit() == "hearts") {
                // add a point if hearts
                points++;
            }
            
            // print current score
            cout << "Current score = " << points << endl;
        }
        else
        {
            // print prompt if invalid user input
            cout << "invalid response. Please try again." << endl;
        }
    }
    
    // print end of game and final score
    cout << "Game over! Final score = " << points << endl;
}
