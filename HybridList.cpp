#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
using namespace std;

HybridList::HybridList() {}

HybridList::HybridList(int blockSize) {
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::HybridList(const HybridList& h) {
	operator=(h);
}

HybridList::~HybridList() {
	clear();
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

HybridList& HybridList::operator=(const HybridList& h) {
	clear();
	numElements = h.size();
	blockSize = h.block_size();
	HybridList* newList = new HybridList(blockSize);
	for (int i = 0; i < numElements; i++)
		newList->push_back(h.at(i));
	head = newList->front();
	tail = newList->back();

	return *this;
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail

	numElements++;
}

void HybridList::pop_back() {
	if (tail->size() == 0) {
		throw out_of_range("Array is empty.");
	}

	else {
		erase(tail->at(tail->size() - 1));
	}
}

void HybridList::insert(int index, double value) {
	//traversing just like at function
	bool found = false;
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index - 1 < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			if (curNode->size() == blockSize) {
				HybridListNode* newNode = new HybridListNode(blockSize);

				// Copy just under half of elements from old tail to new tail
				for (int i = blockSize / 2 + 1; i < blockSize; i++) {
					newNode->push_back(curNode->at(i));
				}
				curNode->resize(blockSize / 2 + 1);
				newNode->push_back(value);
				newNode->next = curNode->next;
				curNode->next = newNode;
				numBlocks++;
			}
			else {
				curNode->insert(index-elementsSearched, value);
			}
			numElements++;
			found = true;
			
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		if (found == true) {
			break;
		}
		elementsSearched += curNode->size();
		curNode = curNode->next;

	}
}

void HybridList::erase(int index) {
	//traversing just like at function
	bool found = false;
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			for (int i = index - elementsSearched; i < curNode->size() - 1; i++) {
				curNode->at(i) = curNode->at(i + 1);
			}
			numElements--;
			int newSize = curNode->size() - 1;
			curNode->resize(newSize);
			if (this->numElements == 0) {
				delete curNode;

			}
			found = true;
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		if (found == true) {
			break;
		}
		elementsSearched += curNode->size();
		curNode = curNode->next;

	}
}

void HybridList::clear() {
	HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}

int main() {}