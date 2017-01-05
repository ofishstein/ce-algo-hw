// implementation of main and global functions
//
// written and complied in Xcode for OSX
//
//  main.cpp
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/10/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include "wordList.h"
#include "grid.h"
#include "hashTable.h"
#include <stdio.h>

#define MAX_STRING_LENGTH 22

template <typename T> void findMatches(T & list, const grid & grid);
void search(const int sortType);

// main
int main(int argc, const char * argv[]) {
    try {
        // vars for implementing search
        int algo;
        bool badInput = true;
        
        // implement until valid input for algorithm choice
        while (badInput) {
            cout << "Input number for sorting algorithm to use:\n" <<
                "1 for insertionSort, 2 for quickSort, 3 for mergeSort, 4 for heapsort, 5 for hashtable" << endl;
        
            cin >> algo;
        
            if (algo < 1 || algo > 5)
            {
                cout << "Invalid input" << endl;
            } else {
                badInput = false;
            }
        }
        
        // call search with algo value
        search(algo);
        
    } catch (const fileOpenError & foe) {
        cerr << foe.what() << endl;
        exit(1);
    }
    
    return 0;
}

void search(const int sortType)
{
    // initialize clock trackers
    clock_t startTime, sortEndTime, searchStartTime, endTime;
    int sortTime, searchTime, totalTime;
    hashTable<string> table;
    
    // initialize fileName for cin
    string fileName;
    
    // prompt user for filename
    cout << "Input grid file name: ";
    cin >> fileName;
    
    // initiliaze grid and word list
    grid wordSearch = grid(fileName);
    wordList list = wordList();
    
    // get start time for sort
    startTime = clock();
    

    // choose sorting algorithm
    switch(sortType)
    {
        case 1:
            list.insertionSort();
            break;
        case 2:
            list.quickSort();
            break;
        case 3:
            list.mergeSort();
            break;
        case 4:
            list.heapSort();
            break;
        case 5:
            vector<string> vec = list.getList();
            table = hashTable<string>(vec);
            break;
                
    }
    
    // get sort end time
    sortEndTime = clock();
    
    // print words found heading
    cout << "Words found: " << endl;
    
    // get search start time
    searchStartTime = clock();
    
    // find matches
    if (sortType == 5)
    {
        findMatches(table, wordSearch);
    }
    else
    {
        findMatches(list, wordSearch);
    }
    
    // get end time
    endTime = clock();
    
    
    // calculate durations
    sortTime = (int) (sortEndTime - startTime);
    searchTime = (int) (endTime - searchStartTime);
    totalTime = (int) (endTime - startTime);
    
    // print durations
    cout << "Sort Time: " << (float) sortTime / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Search Time: " << (float) searchTime / CLOCKS_PER_SEC << " sec" << endl;
    cout << "Total Time: " << (float) totalTime / CLOCKS_PER_SEC << " sec" << endl;
}

template <typename T>
void findMatches(T & list, const grid & grid)
{
    // iterate through rows
    for (int row = 0; row < grid.wordGrid.rows(); row++)
    {
        // iterate through cols
        for (int col = 0; col < grid.wordGrid.cols(); col++)
        {
            // iterate from moving negatively to moving positively
            for (int rowDirection = -1; rowDirection < 2; rowDirection++)
            {
                // iterate from moving negatively to moving positively
                for (int colDirection = -1; colDirection < 2; colDirection++)
                {
                    // check to make sure a moving direction (i.e. not 0,0)
                    if (rowDirection != 0 || colDirection != 0)
                    {
                        
                        // initialize blank word
                        string word = "";
                        
                        // set col and row values to incrementable variables
                        int colIndex = col;
                        int rowIndex = row;
                    
                        // iterate until the max string lenght is reached
                        for(int chars = 0; chars < MAX_STRING_LENGTH; chars++) {
                        
                            // add chars to the word
                            word += grid.wordGrid[rowIndex][colIndex];
                        
                            if (word.length() >= 5)
                            {
                                // print word if found
                                if (list.inList(word))
                                {
                                    cout << word << endl;
                                }
                            }
                        
                            // increment/decrement indexes in direction
                            colIndex = colIndex + colDirection;
                            rowIndex = rowIndex + rowDirection;
                            
                            // check limits for wraparound
                            if (colIndex == -1)
                            {
                                colIndex = grid.wordGrid.cols() - 1;
                            }
                            else if (colIndex == grid.wordGrid.cols())
                            {
                                colIndex = 0;
                            }
                            if (rowIndex == -1)
                            {
                                rowIndex = grid.wordGrid.rows() - 1;
                            }
                            else if (rowIndex == grid.wordGrid.rows())
                            {
                                rowIndex = 0;
                            }
                    
                        }
                    }
                }
            }
        }
    }
}


