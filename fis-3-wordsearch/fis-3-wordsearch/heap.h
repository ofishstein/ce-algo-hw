//
//  heap.h
//  fis-3-wordsearch
//
//  Created by Oliver Fishstein on 10/17/16.
//  Copyright © 2016 Oliver Fishstein. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <vector>
#include <string>

using namespace std;

template <typename T>
class heap
{
public:
    // constructor
    heap();
    
    // initializes a max heap
    void initializeMaxHeap(vector<T> newList);
    
    // initializes a min heap
    void initializeMinHeap(vector<T> newList);
    
    // makes a heap follow max heap rules
    void maxHeapify(int index, int heapSize);
    
    // builds a max heap
    void buildMaxHeap(int heapsize);
    
    // makes a heap follow min heap rules
    void minHeapify(int index, int heapSize);
    
    // builds a min heap
    void buildMinHeap(int heapsize);
    
    // sorts the heap
    void heapSort();
    
    // returns the index of the parent of a node
    int parent(int index) {return (index + 1)/2-1;}
    
    // returns the index of the left child of a node
    int left(int index) {return (2 * index) + 1;}
    
    // returns the index of the right child of a node
    int right(int index) {return (2 * index) + 2;}
    
    // return the item of index from the heap
    T & getItem(int index) {return list[index];}

    int size() {return (int)list.size();}
    
    // returns the list
    vector<T> & getHeapList() {return list;}
    
private:
    // member data
    vector<T> list;
};

// empty constructor
template <typename T>
heap<T>::heap()
{
}

// initialize a max heap
template <typename T>
void heap<T>::initializeMaxHeap(vector<T> newList)
{
    // iteratively add elements to the heap
    for (int i = 0; i < newList.size(); i++)
    {
        list.push_back(newList[i]);
    }
    
    // build max heap
    buildMaxHeap(size());
}

// initialize a min heap
template <typename T>
void heap<T>::initializeMinHeap(vector<T> newList)
{
    // iteratively add elements to the heap
    for (int i = 0; i < newList.size(); i++)
    {
        list.push_back(newList[i]);
    }
    
    // build min heap
    buildMinHeap(size());
}

// max heapify function
template <typename T>
void heap<T>::maxHeapify(int index, int heapSize)
{
    // find left and right of node
    int l = left(index);
    int r = right(index);
    int largest;
    
    // determine largest index
    if (l <= heapSize-1 && list[l] > list[index])
    {
        largest = l;
    }
    else {
        largest = index;
    }
    if (r <= heapSize-1 && list[r] > list[largest])
    {
        largest = r;
    }
    
    // if node isn't largest swap and run maxheapify again
    if (largest != index)
    {
        swap(list[index], list[largest]);
        
        maxHeapify(largest, heapSize);
    }
}

// min heapify function
template <typename T>
void heap<T>::minHeapify(int index, int heapSize)
{
    // find left and right of node
    int l = left(index);
    int r = right(index);
    int smallest;
    
    // determine smallest index
    if (l <= heapSize-1 && list[l] < list[index])
    {
        smallest = l;
    }
    else {
        smallest = index;
    }
    if (r <= heapSize-1 && list[r] < list[smallest])
    {
        smallest = r;
    }
    
    // if node isn't smallest swap and run minheapify
    if (smallest != index)
    {
        swap(list[index], list[smallest]);
        
        minHeapify(smallest, heapSize);
    }
}

// build max heap
template <typename T>
void heap<T>::buildMaxHeap(int heapsize)
{
    // iteratively max heapify
    for (int i = (size()+1)/2; i >= 0; i--)
    {
        maxHeapify(i, heapsize);
    }
}

// build min heap
template <typename T>
void heap<T>::buildMinHeap(int heapsize)
{
    // iteratively min heapify
    for (int i = (size() + 1) / 2; i >=0; i--)
    {
        minHeapify(i, heapsize);
    }
}

// heap sort
template <typename T>
void heap<T>::heapSort()
{
    buildMaxHeap(size());
    
    int heapsize = size();
    
    // iteratively sort
    for (int i = size() - 1; i >= 0; i--)
    {
        // swap first with last
        swap(list[0],list[i]);
        
        heapsize--;
        
        // heapify the remaining heap
        maxHeapify(0, heapsize);
    }
    
}
#endif /* heap_h */
