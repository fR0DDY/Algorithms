#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template < class T >
class  MultiplicativeFunction
{
public:
	virtual ~MultiplicativeFunction() {}
	virtual T value(int prime, int exponent, int power) = 0;

	vector<int> generateDivisorTable(int N) {
		vector<int> divisor(N, 0);
		for (int i = 1; i < N; i++)
			divisor[i] = i;
		for (int i = 2; i * i < N; i++) {
			if (divisor[i] == i) {
				for (int j = i * i; j < N; j += i)
					divisor[j] = i;
			}
		}
		return divisor;
	}
	
	vector<T> calculateUpTo(int N) {
		vector<int> divisor = generateDivisorTable(N);
		vector<T> result(N, 0);
		result[1] = 1;
		for (int i = 2; i < N; i++) {
			int iDivided = i;
			int exponent = 0;
			do {
				iDivided /= divisor[i];
				exponent++;
			} while (iDivided % divisor[i] == 0);
			result[i] = result[iDivided] * value(divisor[i], exponent, i / iDivided);
		}
		return result;
	}
};

template < class T >
class DivisorSum: public MultiplicativeFunction<T>
{
public:
	T value(int prime, int exponent, int power) {
		return (power * 1LL * prime - 1) / (prime - 1);
	}
};


int main() {
	DivisorSum<long long> ds;
	vector<long long> sigma = ds.calculateUpTo(1000000);

	int N;
	while(~scanf("%d", &N)) {
		printf("%lld\n", sigma[N]);
	}
}