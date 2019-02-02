//2903
//A Symmetrical Pizza

#include <cstdio>
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
	int d, c;
	scanf("%d.%d", &d, &c);
	long int n = d;
	n = 100*n + c;
	long int circulo = 36000;
	long int mc = mmc(n, circulo);
	printf("%ld\n", mc/n);
}