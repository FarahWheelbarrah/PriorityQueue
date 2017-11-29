#ifndef _PR_QUEUE_H
#define _PR_QUEUE_H

/*
* Some headers that may be useful.
* The utility header is included for the
* std::pair<X,Y> class, used below.
*/
#include <vector>
#include <list>
#include <utility>
#include <iostream>

/*
* This class implements a priority queue ADT
* with priorities specified in ints.
* Lower priority values precede higher values in
* the ordering.
* The template type E is the element type.
* See the tests for examples.
*/
template <typename E>
class PriorityQueue {

private:

	/*
	* You will probably want to add some data
	* members here.
	*/
	static const int MIN_VECTOR_SIZE = 1; // queue will always have one empty leading node, for convenience
	std::vector<std::pair<int, E> > minHeap; // nodes of min-heap are of type std::pair<int, E>

	/*
	* Returns pointer to front node in queue, i.e. node
	* at index 1, i.e. root node in min-heap.
	*/
	std::pair<int, E> * getFrontPair() {
		return &minHeap[1];
	}

	/*
	* Returns back node in queue, i.e. node at index size().
	*/
	std::pair<int, E> getBackPair() {
		return minHeap.back();
	}

	/*
	* Similar to getBackPair(), except removes back 
	* node from queue, in addition to returning it.
	*/
	std::pair<int, E> removeBackPair() {
		std::pair<int, E> backPair = getBackPair();
		minHeap.pop_back();
		return backPair;
	}

	/*
	* Returns index of left child node, using index of parent node.
	*/
	int getLeftChildIndex(int parentIndex) {
		return parentIndex * 2;
	}

	/*
	* Returns index of right child node, using index of parent node.
	*/
	int getRightChildIndex(int parentIndex) {
		return parentIndex * 2 + 1;
	}

	/*
	* Returns index of parent node, using index of child node.
	*/
	int getParentIndex(int childindex) {
		return childindex / 2;
	}

	/*
	* Returns index of last (deepest and right-most) parent node 
	* (node that has at least one child) in min-heap.
	*/
	int getLastParentIndex() {
		return size() / 2;
	}

	/*
	* Returns true if a parent node has 2 child nodes, false otherwise.
	*/
	bool has2Children(int parentIndex) {
		return getRightChildIndex(parentIndex) <= size(); // if index of right child node is less than size of min-heap, then parent 
	}													  // node has a right child node, and therefore, has a left child node

	/*
	* Returns pointer to left child node, using index of parent node.
	*/
	std::pair<int, E> * getLeftChild(int parentIndex) {
		return &minHeap[getLeftChildIndex(parentIndex)];
	}

	/*
	* Returns pointer to right child node, using index of parent node.
	*/
	std::pair<int, E> * getRightChild(int parentIndex) {
		return &minHeap[getRightChildIndex(parentIndex)];
	}

	/*
	* Returns pointer to parent node, using index of child node.
	*/
	std::pair<int, E> * getParent(int childIndex) {
		return &minHeap[getParentIndex(childIndex)];
	}

	/*
	* Returns pointer to node with minimum priority value between two (sibling) nodes.
	*/
	std::pair<int, E> * getMinPriorityChild(std::pair<int, E> * leftChild, std::pair<int, E>  * rightChild) {
		return (leftChild->first < rightChild->first ? leftChild : rightChild);
	}

	/*
	* Returns pointer to node in min-heap with element "element", null pointer otherwise.
	*/
	std::pair<int, E> * getPairWithElement(E element) {
		for (int i = 1; i <= size(); i++)
			if (minHeap[i].second == element)
				return &minHeap[i];
		return 0;
	}

	/*
	* "Sifts" down min-heap from root node, and rearranges nodes
	* until all are in the correct (min-heap) order.
	*/
	void reorderMinHeap() {
		for (int i = 1; i <= getLastParentIndex(); i *= 2) {
			if (has2Children(i)) { // node has 2 children
				std::pair<int, E> * minPriorityChild = getMinPriorityChild(getLeftChild(i), getRightChild(i));
				if (minHeap[i].first > minPriorityChild->first) // priority value of parent node is greater than minimum priority value between its child nodes
					std::swap(minHeap[i], *minPriorityChild); 
			}
			else if (minHeap[i].first > getLeftChild(i)->first) // node has 1 child (left child), and priority value of parent node is greater than priorty value of its child node
				std::swap(minHeap[i], *getLeftChild(i)); 
		}
	}

	/*
	* Removes and returns front/root node from queue/min-heap, and reorders queue/min-heap correctly.
	*/
	std::pair<int, E> removeFrontAndReorder() {
		std::pair<int, E> frontPair = *getFrontPair();
		*getFrontPair() = removeBackPair(); // back node overwrites (is copied to) root/front node. Back node is then removed from queue
		reorderMinHeap(); // min-heap is reordered correctly
		return frontPair;
	}

	/*
	* Adds new node to queue based on min-heap order.
	*/
	void insertPair(int priority, E element) {
		minHeap.push_back(std::make_pair(priority, element));
		for (int i = size(); i > 1 && minHeap[i].first < getParent(i)->first; i /= 2) // loop as long as current node is not root/front node, and priority value of current node is less than priority value of its parent node
			std::swap(minHeap[i], *getParent(i)); 
	}																				  
		
public:

	/*
	* A constructor, if you need it.
	*/
	PriorityQueue() {
		minHeap = std::vector<std::pair<int, E> >(MIN_VECTOR_SIZE); // initialise min-heap/queue vector with empty leading node
	}

	/*
	* This function adds a new element "element" to the queue
	* with priority "priority".
	*/
	void insert(int priority, E element) {
		if (priority >= 0)
			insertPair(priority, element);
	}

	/*
	* Similar to insert, but takes a whole vector of new things to
	* add.
	*/
	void insert_all(std::vector<std::pair<int, E> > new_elements) {
		for (int i = 0; i < new_elements.size(); i++)
			insert(new_elements[i].first, new_elements[i].second);
	}

	/*
	* Takes the lowest priority value element off the queue,
	* and returns it.
	*/
	E remove_front() {
		return (empty() ? E() : removeFrontAndReorder().second);
	}

	/*
	* Returns the lowest priority value element in the queue, but leaves
	* it in the queue.
	*/
	E peek() {
		return (empty() ? E() : getFrontPair()->second);
	}

	/*
	* Returns a vector containing all the elements in the queue.
	*/
	std::vector<E> get_all_elements() {
		std::vector<E> elements;
		for (int i = 1; i <= size(); i++)
			elements.push_back(minHeap[i].second);
		return elements;
	}

	/*
	* Returns true if the queue contains element "element", false
	* otherwise.
	*/
	bool contains(E element) {
		for (int i = 1; i <= size(); i++)
			if (minHeap[i].second == element)
				return true;
		return false;
	}

	/*
	* Returns the priority of the element that matches
	* "element". If there is more than one, it returns
	* the lowest priority value.
	* If no element matches, return -1.
	*/
	int get_priority(E element) {
		int matchingPriority = -1;
		for (int i = 1; i <= size(); i++)
			if (minHeap[i].second == element && (matchingPriority == -1 || minHeap[i].first < matchingPriority)) // a pair with element "element" was found in min-heap AND either
				matchingPriority = minHeap[i].first;															 // none was found yet, OR a pair with element "element" was found again
		return matchingPriority;																				 // with a lower priority value than the existing matchingPriority value
	}

	/*
	* Returns a vector containing all the priorities.
	* The ordering of the vector should match that of the
	* return from get_all_elements().
	* That is, the priority of the element
	* get_all_elements()[i] should be get_all_priorities()[i].
	*/
	std::vector<int> get_all_priorities() {
		std::vector<int> priorities;
		for (int i = 1; i <= size(); i++)
			priorities.push_back(minHeap[i].first);
		return priorities;
	}

	/*
	* Finds the first (in priority order) element that matches
	* "element", and changes its priority to "new_priority".
	*/
	void change_priority(E element, int new_priority) {
		std::pair<int, E> * matchingPair = getPairWithElement(element);
		if (matchingPair != 0) // a pair with element "element" was found
			matchingPair->first = new_priority;
	}

	/*
	* Returns the number of elements in the queue.
	*/
	int size() {
		return minHeap.size() - 1; // returns vector size() - 1, since the min-heap/queue always has one empty leading node
	}

	/*
	* Returns true if the queue has no elements, false otherwise.
	*/
	bool empty() {
		return size() == 0;
	}

};
#endif