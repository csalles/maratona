//1029 Fibonacci, Quantas Chamadas?

#include <iostream>
using namespace std;

/*
int fibCalls(int n) {
	if(n==1) return 1;
	if(n==0) return 1;
	return fibCalls(n-1) + fibCalls(n-2) + 1;
}

int fib(int n) {
	if(n==1) return 1;
	if(n==0) return 0;
	return fib(n-1) + fib(n-2);
}
*/

#define MAXV 40

int main() {
	int n;
	cin >> n;

	int fibCalls[MAXV];
	int fib[MAXV];

	fib[0] = 0;
	fib[1] = 1;
	fibCalls[0] = 1;
	fibCalls[1] = 1;
	for(int i=2; i<MAXV; i++) {
		fib[i] = fib[i-1] + fib[i-2];
		fibCalls[i] = fibCalls[i-1] + fibCalls[i-2] + 1;
	}

	while(n--) {
		int x;
		cin >> x;

		cout << "fib(" << x << ") = " << fibCalls[x]-1 << " calls = " << fib[x] << endl;
	}
}
