// implementation of grid class
//
// written and complied in Xcode for OSX
//
//  grid.cpp
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/10/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "grid.h"
#include "d_except.h"

using namespace std;

// loads grid from fileName
grid::grid(string fileName)
{
    // initialize filestream and temp word variable
    ifstream file;
    string word;
    
    // attemp to open file
    file.open(fileName);
    
    // throw error if file not found
    if (!file)
    {
        throw fileOpenError(fileName + " not found");
    }
    
    // read in rows
    file >> word;
    int rows = stoi(word);
    // read in columns
    file >> word;
    int columns = stoi(word);
    
    // initialize the matrix
    wordGrid = matrix<string>();
    wordGrid.resize(rows, columns);
    
    // read in each character to the matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            file >> word;
            wordGrid[i][j] = word;
        }
    }
    
    // close file
    file.close();
}
