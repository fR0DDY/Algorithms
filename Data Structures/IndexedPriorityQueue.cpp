/*
IndexPriorityQueue(int maxN)
	- create a priority queue of capacity maxN
	- with possible indices between 0 and maxN - 1
bool isEmpty()
	- is the priority queue empty?
void push(int k, Item item) - O(log n)
	- insert item for index k
void pop() - O(log n)
	- remove the topmost item and returns it's index
void changeKey(int k, Item item) - O(log n)
	- change the item associated with index k to item
bool contains(int k)
	- is index k associated with some item?
*/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

template < class T, class Compare = less < T > > 
class IndexedPriorityQueue {
	private:
		vector<T> keys;
		vector<int> keyIndexOfHeapIndex;
		vector<int> heapIndexOfKeyIndex;
		int numberOfElements;
		Compare comp;

	public:
		IndexedPriorityQueue(int n) {
			numberOfElements = 0;
			keyIndexOfHeapIndex.resize(n + 1);
			heapIndexOfKeyIndex.resize(n + 1, -1);
			keys.resize(n + 1);
		}

		bool isEmpty() { return numberOfElements == 0; }

		T top() {
			return keys[keyIndexOfHeapIndex[1]];
		}

		void push(int k, T key) {
			numberOfElements++;
			heapIndexOfKeyIndex[k] = numberOfElements;
			keyIndexOfHeapIndex[numberOfElements] = k;
			keys[k] = key;
			heapifyUp(numberOfElements);
		}

		int pop() {
			int index = keyIndexOfHeapIndex[1];
			swapIndex(1, numberOfElements);
			heapIndexOfKeyIndex[index] = -1;
			keyIndexOfHeapIndex[numberOfElements] = -1;
			numberOfElements--;
			heapifyDown(1);
			return index;
		}

		bool changeKey(int k, T key) {
			keys[k] = key;
			heapifyUp(heapIndexOfKeyIndex[k]);
			heapifyDown(heapIndexOfKeyIndex[k]);
		}

		void heapifyUp(int k) {
			while(k > 1 && compare(k / 2, k)) {
				swapIndex(k / 2, k);
				k = k / 2;
			}
		}

		void heapifyDown(int k) {
			while(2 * k <= numberOfElements) {
				int j = 2 * k;
				if(j < numberOfElements && compare(j, j + 1)) j++;
				if(!compare(k, j)) break;
				swapIndex(k, j);
				k = j;
			}
		}

		bool contains(int k) { return heapIndexOfKeyIndex[k] != -1; }

		int size() { return numberOfElements; }

		void swapIndex(int i, int j) {
			swap(keyIndexOfHeapIndex[i], keyIndexOfHeapIndex[j]);
			heapIndexOfKeyIndex[keyIndexOfHeapIndex[i]] = i;
			heapIndexOfKeyIndex[keyIndexOfHeapIndex[j]] = j;
		}

		bool compare(int i, int j) {
			return comp(keys[keyIndexOfHeapIndex[i]], keys[keyIndexOfHeapIndex[j]]);
		}
};

int main() {
	string strings[] = { "it", "was", "the", "best", "of", "times", "it", "was", "the", "worst" };

    IndexedPriorityQueue < string > pq(10);
    for (int i = 0; i < 10; i++) {
        pq.push(i, strings[i]);
    }
    strings[0] = "string";
    pq.changeKey(0, "string");
    // delete and print each key
    while (!pq.isEmpty()) {
        int i = pq.pop();
        cout << strings[i] << endl;
	}
}