/*
Prims Algorithm
	Greedy Algorithm
	Using Indexed Priority Queue
	Time Complexity: O(E log V)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdio>

using namespace std;

#define REP(i,N) 		for(int i = 0; i < (N); ++i)
#define FOREACH(i,c) 	for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)

#define PB 				push_back

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

		void swapIndex(int i, int j) {
			swap(keyIndexOfHeapIndex[i], keyIndexOfHeapIndex[j]);
			heapIndexOfKeyIndex[keyIndexOfHeapIndex[i]] = i;
			heapIndexOfKeyIndex[keyIndexOfHeapIndex[j]] = j;
		}

		bool compare(int i, int j) {
			return comp(keys[keyIndexOfHeapIndex[i]], keys[keyIndexOfHeapIndex[j]]);
		}
};

template <class T>
class PrimMST {
	private:
		vector < vector < pair < int, T > > > edgeWeightedGraph;
		int numberOfVertex;
		T INF;

	public:
		PrimMST(int n) {
			numberOfVertex = n;
			edgeWeightedGraph.resize(numberOfVertex);
			INF   = numeric_limits<T>::max();
			int numberOfEdges, v, u, w;

			scanf("%d", &numberOfEdges);
			for(int j = 0; j < numberOfEdges; j++) {
				scanf("%d%d%d", &v, &u, &w);
				edgeWeightedGraph[v - 1].PB(make_pair(u - 1, w));
				edgeWeightedGraph[u - 1].PB(make_pair(v - 1, w));
			}
		}

		T getMSTWeight() {
			IndexedPriorityQueue < T, greater < T > > Q(numberOfVertex);
			Q.push(0, 0);
			vector<bool> marked(numberOfVertex, false);
			vector<T> key(numberOfVertex, INF);
			T minimumCost       = 0;
			key[0]              = 0;
			int noOfVertexinMST = 0;

			while(noOfVertexinMST < numberOfVertex) {
				int u = Q.pop();

				if(marked[u] == true) continue;

				minimumCost  = minimumCost + key[u];
				marked[u] = true;
				noOfVertexinMST++;

				FOREACH(it, edgeWeightedGraph[u]) {
					int v = (*it).first, cost = (*it).second;
					if(marked[v] == false && cost < key[v]) {
						key[v] = cost;
						if(Q.contains(v)) Q.changeKey(v, cost);
						else Q.push(v, cost);
					}
				}
			}
			return minimumCost;
		}
};


int main() {
	int n;
	scanf("%d", &n);
	PrimMST<int> graph(n);
	printf("%d\n", graph.getMSTWeight());
}