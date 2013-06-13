#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <limits>
 
using namespace std;
 
typedef long long       LL;
typedef vector<int>     VI;
typedef vector<VI>      VVI;
typedef pair<int, int>  PII;
 
#define FOR(i,a,b)      for(int i=(a); i<(b); ++i)
#define REP(i,N)        for(int i=0; i<(N); ++i)
#define FORD(i,a,b)     for(int i=(a);i>=(b);--i)
#define FOREACH(i,c)    for(__typeof((c).begin()) i=(c).begin();i!=(c).end();++i)
 
#define SIZE(x)         ((int)(x.size()))
#define LENGTH(x)       ((int)(X.length()))
#define ALL(x)          (x).begin(),(x).end()
#define SORT(x)         sort(ALL(x))
#define REVERSE(x)      reverse(ALL(x))
#define UNIQUE(x)       a.resize(unique(ALL(x))-x.begin())
#define REMOVE(a,b)     a.resize(remove(ALL(a),b)-a.begin())
#define FIND(a,b)       find(ALL(a),b)
#define FILL(a,b)       memset(a,b,sizeof(a))
#define BS(a,b)         binary_search(ALL(a),b)
 
#define PB              push_back

template<class T>
class RangeUpdateBIT
{
    T *tree;
	T *mulTree;
	int maxVal;
	public:
	RangeUpdateBIT(int N)
	{
		tree = new T[N+1];
		mulTree = new T[N + 1];
		memset(tree, 0, sizeof(T) * (N + 1));
		memset(mulTree, 0, sizeof(T) * (N + 1));
		maxVal = N;
	}
	~RangeUpdateBIT() {
        free(tree);
        free(mulTree);
    }
	void update(int idx, T val)
	{
		T mulVal = (idx - 1) * val;
		while (idx <= maxVal)
		{
			tree[idx] += val;
			mulTree[idx] += mulVal;
			idx += (idx & -idx);
		}
	}
	//Returns the cumulative frequency of index idx
	T read(int idx)
	{
		int pos = idx;
		T sum=0, mulSum = 0;
		while (idx>0)
		{
			sum += tree[idx];
			mulSum += mulTree[idx];
			idx -= (idx & -idx);
		}
		return sum * pos - mulSum;
	}
	void rangeUpdate(int a, int b, T val) {
		update(a, val);
		update(b + 1, -val);
	}
	T getRangeSum(int a, int b) {
		return read(b) - read(a - 1);
	}
};

int main() {
	int T, N , Q, c, p, q, v;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &Q);
		RangeUpdateBIT<LL> bit(N);
		while(Q--) {
			scanf("%d", &c);
			if(c) {
				scanf("%d%d", &p, &q);
				printf("%lld\n", bit.getRangeSum(p, q));
			}else {
				scanf("%d%d%d", &p, &q, &v);
				bit.rangeUpdate(p, q, v);
			}
		}
	}
}