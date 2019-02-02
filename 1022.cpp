//1022


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define ABS(a) ((a)<0 ? -(a) : (a))

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
	long int n1, d1, n2, d2;
	string f1, f2, op;
	int n;

	long int nOut, dOut;

	cin >> n;
	while(n--) {
		cin >> n1 >> f1 >> d1 >> op >> n2 >> f2 >> d2;
		if(op=="+") {
			nOut = n1*d2 + n2*d1;
			dOut = d1*d2;
		}
		else if(op=="-") {
			nOut = n1*d2 - n2*d1;
			dOut = d1*d2;
		}
		else if(op=="*") {
			nOut = n1*n2;
			dOut = d1*d2;
		}
		else if(op=="/") {
			nOut = n1*d2;
			dOut = n2*d1;
		}
		if(dOut<0&&nOut<0) {
			nOut = -nOut;
			dOut = -dOut;
		}
		else if(dOut<0&&nOut>=0) {
			nOut = -nOut;
			dOut = -dOut;
		}

		cout << nOut << "/" << dOut << " = ";

		long int m = mdc(ABS(nOut), ABS(dOut));

		cout << nOut/m << "/" << dOut/m << endl;
	}



}
