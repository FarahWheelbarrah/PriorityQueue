#include <iostream>
#include "PriorityQueue.h"
#include <utility>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;

int main() {
	PriorityQueue<string> * pq = new PriorityQueue<string>();
	
	/*std::cout << "Initial size: " << pq->size() << "\n";
	std::cout << (pq->empty() ? "The queue is empty" : "The queue is NOT empty") << "\n";

	std::cout << "Pushing element into position 1..." << "\n";
	pq->insert(1, 4);

	std::cout << "Size after push: " << pq->size() << "\n";
	std::cout << (pq->empty() ? "The queue is empty" : "The queue is NOT empty") << "\n";

	vector<std::pair<int, int> > vec;
	std::pair<int, int> pair(4, 2);
	std::cout << "The first value in the pair is " << pair.first << "\n";
	vec.push_back(pair);
	std::cout << "The second value in the pair is " << vec[0].second << "\n";*/
	
	// testing change_priority():
	//string strArray[] = { "man", "trick", "flop", "chicken", "boy", "dog", "fish" };
	//for (int i = 0; i < 7; i++)
	//	pq->insert(i, strArray[i]);
	//pq->print();
	//cout << "Changing priority of element \"flop\"..." << "\n";
	//pq->change_priority("flop", 7);
	//pq->print();
	//pq->change_priority()
	//int priority = pq->get_priority("man"); 
	//cout << "The priority is " << priority << "\n";
	//for (int i = 0; i < 1; i++)
	//	pq->insert(i, strArray[i]);
	//cout << "The priority is " << pq->get_priority("man") << "\n";
	//pq->change_priority("man", 1);
	//cout << "The priority is " << pq->get_priority("man") << "\n";

	// testing isCorrectMinHeapWithRemoval:
	std::vector<int> manualHeap;

	pq->insert(100, "bob");
	pq->insert(10, "smith");
	pq->insert(20, "chicken");
	pq->insert(15, "wompy");
	pq->insert(43, "smith");
	pq->insert(2, "smith");
	pq->insert(1, "smith");
	pq->insert(432, "tinstrance");
	pq->insert(8321, "goopy");
	pq->insert(8, "wofwof");
	pq->insert(4, "jump");
	//pq->insert(5, "smith");
	cout << "Printing minHeap BEFORE removal..." << "\n";
	//pq->print();

	//manualHeap.push_back(10);
	//manualHeap.push_back(15);
	//manualHeap.push_back(20);

	pq->remove_front();
	cout << "Printing minHeap AFTER removal..." << "\n";
	//pq->print();
	//for (int i = 0; i < manualHeap.size(); i++)
	//	cout << "manualHeap priority: " << manualHeap[i] << "\n";

	// testing get_priority:
	//cout << "Matching priority: " << pq->get_priority("smith") << "\n";
}

// THE PRINT FUNCTION YOU HAD DEFINED IN PRIORITYQUEUE.H:

//void print() {
//	for (int i = 1; i <= size(); i++)
//		std::cout << "Index: " << i << " - Priority: " << minHeap[i].first << " - Element: " << minHeap[i].second << "\n";
//}