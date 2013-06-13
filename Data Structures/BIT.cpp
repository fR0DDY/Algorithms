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
class BIT
{
    T *tree;
    int maxVal;
    public:
    BIT(int N)
    {
        tree = new T[N+1];
        memset(tree,0,sizeof(T)*(N+1));
        maxVal = N;
    }
    ~BIT() {
        free(tree);
    }
    void update(int idx, T val)
    {
        while (idx <= maxVal)
        {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }
    //Returns the cumulative frequency of index idx
    T read(int idx)
    {
        T sum=0;
        while (idx>0)
        {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    T getRangeSum(int a, int b) {
        return read(b) - read(a - 1);
    }
};

int main() {
    int N, T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        VI arr(N, 0);
        
        REP(i, N) scanf("%d", &arr[i]);
        
        BIT<int> bit(10000001);

        LL result = 0;
        REP(i, N) {
            result += bit.getRangeSum(arr[i], 10000001);
            bit.update(arr[i], 1);
        }
        printf("%lld\n", result);
    }
}