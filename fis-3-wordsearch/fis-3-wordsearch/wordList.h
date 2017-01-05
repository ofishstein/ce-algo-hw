// declaration of wordList class
//
// written and complied in Xcode for OSX
//
//  wordList.h
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/10/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef wordList_h
#define wordList_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class wordList {
public:
    // max string length
    int maxStringLength;
    
    // constructor reads in wordlist file
    wordList();
    
    // overloaded print operator
    friend ostream& operator<<(ostream & ostr, const wordList & wordList);
    
    // insertion sort
    void insertionSort();
    
    // public function to start quick sort
    void quickSort();
    
    // public function to start merge sort
    void mergeSort();
    
    // heap sort the list
    void heapSort();
    
    // looks up a word and says if its present
    bool inList(const string & word);
    
    // finds if the word is a substring of a word in the list
    bool checkSubstring(const string & word);
    
    // returns the list
    vector<string> getList();
    
private:
    // word list
    vector<string> list;
    
    // partition function for quickSort
    int partition(vector<string>  & list, int low, int high);

    // recursive quick sort
    void quickSort(vector<string> & list, int low, int high);
    
    // merge function for mergeSort
    void merge(vector<string> & list, int left, int middle, int right);
    
    // recursive mergeSort
    void mergeSort(vector<string> & list, int left, int right);
    
    // binarySearch function for if a string matches
    int binarySearch(vector<string> & list, const string & word, int left, int right);
    
    // binarySearch function for if a string is a substring
    int binarySearchSubstring(vector<string> & list, const string & word, int left, int right);
    
};

#endif /* wordList_h */
