#ifndef HYBRIDLIST_H
#define HYBRIDLIST_H

#include "BoundedArray.h"

// A node in the hybrid list: a bounded array containing the data and a pointer
// to the next node
class HybridListNode : public BoundedArray {
public:
	HybridListNode* next = nullptr;
	HybridListNode() {}
	HybridListNode(int maxNumElements) : BoundedArray(0, maxNumElements) {}
	~HybridListNode() {}
};

// Hybrid list: a singly-linked list of nodes that contain blocks of data
class HybridList {
public:
	// Create empty hybrid list with default block size of 10
	HybridList();
	// Create empty hybrid list with specified block size
	HybridList(int blockSize);
	// Create hybrid list with all elements (not just pointers) copied from h
	HybridList(const HybridList& h);
	// Deallocate memory for hybrid list
	~HybridList();
	// Return the number of elements in the hybrid list
	int size() const;
	// Return the maximum number of elements in the hybrid list
	int capacity() const;
	// Return the block size (max. number of elements per node) of the hybrid list
	int block_size() const;
	// Access first (head) element
	HybridListNode* front() const;
	// Access last (tail) element
	HybridListNode* back() const;
	// Return element at specified index. Throw out of range exception for invalid
	// index.
	double& at(int index) const;
	// Copy hybrid list elements from h into current hybrid list
	HybridList& operator=(const HybridList& h);
	// Insert a new element with specified value at the end of the hybrid list.
	void push_back(double value);
	// Delete last element in the hybrid list. Throw out of range exception if
	// array is empty.
	void pop_back();
	// Insert a new element with specified value at the specified index, moving all
	// other elements back by 1. Throw out off range exception if index is invalid.
	void insert(int index, double value);
	// Delete element at specified index. Throw out of range exception if index is
	// invalid.
	void erase(int index);
	// Delete all elements and deallocate memory for blocks
	void clear();
private:
	// Size of bounded arrays to use for blocks
	int blockSize = 10;
	// Number of elements in the hybrid list
	int numElements = 0;
	// Number of blocks in the hybrid list
	int numBlocks = 0;
	// Pointers to head and tail nodes
	HybridListNode* head = nullptr, * tail = nullptr;
};

#endif // !HYBRIDLIST_H