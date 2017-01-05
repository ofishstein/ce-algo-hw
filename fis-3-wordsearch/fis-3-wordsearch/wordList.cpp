// implementation of wordList class
//
// written and complied in Xcode for OSX
//
//  wordList.cpp
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/10/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <fstream>
#include "d_except.h"
#include "wordList.h"
#include "heap.h"

using namespace std;

// constructor reads in wordlist file
wordList::wordList()
{
    // initialize file stream and temp line variable
    ifstream file;
    string line;
    
    // attempt to open file
    file.open("wordlist.txt");
    
    // if not found throw error
    if (!file)
    {
        throw fileOpenError("wordlist.txt not found");
    }
    
    // initialize maxStringLength to 0;
    maxStringLength = 0;
    
    // read in line
    while(getline(file, line))
    {
        // add line to vector
        list.push_back(line);
        
        // update maxStringLength
        if (line.length() > maxStringLength) {
            maxStringLength = (int) line.length();
        }
    }
    
    // close file
    file.close();
}

// overloaded print operator
ostream& operator<<(ostream & ostr, const wordList & wordList)
{
    // iterate through vector
    for (vector<string>::const_iterator i = wordList.list.begin();
         i != wordList.list.end(); i++)
    {
        // add word to ostream
        ostr << *i << endl;
    
    }
    
    // return ostream
    return ostr;
}

// insertion sort
void wordList::insertionSort()
{
    // iterate through elements of the vector
    for (int i = 1; i < list.size(); i++)
    {
        // set key
        string key = list.at(i);
        // set starting comparison index
        int j = i - 1;
        
        // move elements of list that are greate than key one position ahead
        while (j >= 0 && list.at(j) > key)
        {
            list.at(j + 1) = list.at(j);
            j = j - 1;
        }
        
        // set key to sorted index
        list.at(j + 1) = key;
    }
}

// public function to start recursive quicksort
void wordList::quickSort()
{
    quickSort(list, 0, (int) list.size() - 1);
}

// partition function for quicksort
int wordList::partition(vector<string> & list, int low, int high)
{
    // find the pivot
    string pivot = list[high];
    // find index of the smallest element;
    int i = (low - 1);
    
    // iterate through values to compare to pivot
    for (int j = low; j <= high - 1; j++)
    {
        // if less than pivot move to front
        if (list[j] <= pivot)
        {
            i++;
            swap(list[i], list[j]);
        }
    }
    
    // swap value at partition index with pivot
    swap(list[i + 1], list[high]);
    
    // return partition index
    return (i + 1);
}

// recursive quick sort
void wordList::quickSort(vector<string> & list, int low, int high)
{
    // do while low is less than high
    if (low < high)
    {

        // find partition index and partition the list
        int partitionIndex = partition(list, low, high);
        
        // seperately sort elements before and after partition
        quickSort(list, low, partitionIndex - 1);
        quickSort(list, partitionIndex + 1, high);
    }
}

// public function to start merge sort
void wordList::mergeSort()
{
    mergeSort(list, 0, (int) list.size() - 1);
}

// merge function for merge sort
void wordList::merge(vector<string> & list, int left, int middle, int right)
{
    // create temp vectors for each half of the list
    vector<string> leftVector;
    vector<string> rightVector;
    
    // find the size of eacg
    int leftSize = middle - left + 1;
    int rightSize =  right - middle;
    
    // copy data to temp vectors
    for (int i = 0; i < leftSize; i++)
        leftVector.push_back(list[left + i]);
    for (int j = 0; j < rightSize; j++)
        rightVector.push_back(list[middle + 1 + j]);
    

    // initialize indexes for sublists and the merged sublist
    int i = 0;
    int j = 0;
    int k = left;
    
    // merge the temp vectors back into the list
    while (i < leftSize && j < rightSize)
    {
        // if left is less than right add left to list else add right
        if (leftVector[i] <= rightVector[j])
        {
            list[k] = leftVector[i];
            i++;
        }
        else
        {
            list[k] = rightVector[j];
            j++;
        }
        k++;
    }
    
    // copy remaining elements of left list if any left
    while (i < leftVector.size())
    {
        list[k] = leftVector[i];
        i++;
        k++;
    }
    
    // copy remaining elements of right list if any left
    while (j < rightVector.size())
    {
        list[k] = rightVector[j];
        j++;
        k++;
    }
}

// recursive mergeSort
void wordList::mergeSort(vector<string> & list, int left, int right)
{
    // do while left is less than right
    if (left < right)
    {
        // find the middle index
        int middle = (left + right)/2;
        
        // sort first and second halves
        mergeSort(list, left, middle);
        mergeSort(list, middle + 1, right);
        
        // merge the halves together
        merge(list, left, middle, right);
    }
}

// looks up a word and says if it is present as word or substring
// returns 1 for found, 0 for substring, -1 for not present;
bool wordList::inList(const string & word)
{
    // call binary search
    int search = binarySearch(list, word, 0, (int) list.size() - 1);
    
    return search != -1;
}

// iterative binary search to find a word
int wordList::binarySearch(vector<string> & list, const string & word, int left, int right)
{
    // do while left is <= right
    while (left <= right) {
        //find middle
        int middle = (left + right) / 2;
        
        //if middle is equal to word return index
        if (list[middle] == word)
        {
            return middle;
        }
        // else if decrement middle
        else if (list[middle] > word)
        {
            right = middle - 1;
        }
        // else increment middle
        else
        {
            left = middle + 1;
        }
    }
    // return -1 if not found
    return -1;
}

// check if substring
bool wordList::checkSubstring(const string & word)
{
    // call binary search
    int search = binarySearchSubstring(list, word, 0, (int) list.size() - 1);
    
    return search != -1;
}

// iterative binary search to find a substring
int wordList::binarySearchSubstring(vector<string> & list, const string & word, int left, int right)
{
    // do while left is <= right
    while (left <= right) {
        //find middle
        int middle = (left + right) / 2;
        
        //if middle is equal to word return index
        if ((list[middle].compare(0, word.length(), word)) == 0)
        {
            return middle;
        }
        // else if decrement middle
        else if (list[middle] > word)
        {
            right = middle - 1;
        }
        // else increment middle
        else
        {
            left = middle + 1;
        }
    }
    // return -1 if not found
    return -1;
}

// heap sort the list
void wordList::heapSort()
{
    heap<string> heapToSort = heap<string>();
    
    heapToSort.initializeMaxHeap(list);
    
    heapToSort.heapSort();
    
    list = heapToSort.getHeapList();
}

vector<string> wordList::getList()
{
    return list;
}
