/*
Prims Algorithm
	Greedy Algorithm
	Using the builtin STL priority queue.
	Time Complexity: O(E log E)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdio>

using namespace std;

#define FOREACH(i,c) 	for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)

#define PB 				push_back

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
			priority_queue < pair < T, int >, vector < pair < T, int > >, greater < pair < T, int > > > Q;
			Q.push(make_pair(0, 0));
			vector<bool> marked(numberOfVertex, false);
			vector<T> key(numberOfVertex, INF);
			T minimumCost       = 0;
			key[0]              = 0;
			int noOfVertexInMST = 0;

			while(noOfVertexInMST < numberOfVertex) {
				pair< int, T > top = Q.top();
				int u              = top.second;
				Q.pop();

				if(marked[u] == true) continue;

				minimumCost  = minimumCost + top.first;
				marked[u] = true;
				noOfVertexInMST++;

				FOREACH(it, edgeWeightedGraph[u]) {
					int v = (*it).first, cost = (*it).second;
					if(marked[v] == false && cost < key[v]) {
						key[v] = cost;
						Q.push(make_pair(cost, v));
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