//
//  hashTable.h
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/17/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef hashtable_h
#define hashtable_h

#include <vector>

using namespace std;

template <typename T>
class hashTable {
public:
    // empty initializer
    hashTable();
    
    // initialize with a vector
    hashTable(vector<T> & list);
    
    // adds an item
    void addItem(T & item);
    
    // deletes an item
    void deleteItem(T & item);
    
    // checks if in list
    bool inList(T & item);
    
    // hashing function
    int hash(T & item);
    
private:
    
    // member data
    vector<vector<T> > table;
};

// empty initalizer
template <typename T>
hashTable<T>::hashTable()
{
}

// vector initializer
template <typename T>
hashTable<T>::hashTable(vector<T> & list)
{
    // creates the hashtable of size of array
    table = vector<vector<T> >(list.size());
    
    // iteratively adds elements
    for (int i = 0; i < list.size(); i++)
    {
        addItem(list[i]);
    }
}

// adds an item to hashtable
template <typename T>
void hashTable<T>::addItem(T & item)
{
    // get hash result
    int hashIndex = hash(item);

    // add to that index
    table[hashIndex].push_back(item);
    
}

// deletes an item
template <typename T>
void hashTable<T>::deleteItem(T & item)
{
    int hashIndex = hash(item);
    
    // iterate through list to find item
    for (int i = 0; i < table[hashIndex].size(); i++)
    {
        // if equal delete
        if (table[hashIndex][i] == item)
        {
            table[hashIndex].erase(i);
        }
    }
}

// find a word in list
template <typename T>
bool hashTable<T>::inList(T & item)
{
    // get hashcode
    int hashIndex = hash(item);
    
    // iterate through the hash bucket
    for (int i = 0; i < table[hashIndex].size(); i++)
    {
        // if matches return true
        if (table[hashIndex][i] == item)
        {
            return true;
        }
    }
    
    // return false if not found
    return false;
}

// hash function
template <typename T>
int hashTable<T>::hash(T & item)
{
    // init hash for type
    std::hash<T> h;
    //return hash mod size for index
    return (int) (h(item) % table.size());
}


#endif /* hashtable_h */
