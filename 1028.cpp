//1028

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


//Euclides
long int mdc(long int a, long int b){
	if(a<b) return mdc(b,a);
	while(b != 0){
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
//Algoritmo do MMC
long int mmc(long int a, long int b){
	return a * (b / mdc(a, b));
}

int main() {
	long int f1, f2;
	int n;

	cin >> n;
	while(n--) {
		cin >> f1 >> f2;
		cout << mdc(f1, f2) << endl;
	}
}
