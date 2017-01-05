// declaration of grid class
//
// written and complied in Xcode for OSX
//
//  grid.h
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/10/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef grid_h
#define grid_h

#include "d_matrix.h"
#include <string>

using namespace std;

class grid {
public:
    // constructor loads grid from filename
    grid(const string fileName);
    
    // member data
    matrix<string> wordGrid;
    
};

#endif /* grid_h */
