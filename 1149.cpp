//1149 Somando Inteiros Consecutivos

#include <iostream>
using namespace std;

int main() {
	
	int A, N;

	cin >> A >> N;
	while(N<=0) cin >>N;

	cout << A*(N) + ((N-1)*N)/2 << endl;
}