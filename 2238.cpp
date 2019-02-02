//2238 Divisores

#include <cstdio>
#include <iostream>
using namespace std;

//Euclides
long long int mdc(long long int a, long long int b){
	if(a<b) return mdc(b,a);
	while(b != 0){
		long int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
//Algoritmo do MMC
long long int mmc(long long int a, long long int b){
	return a * (b / mdc(a, b));
}


// n%a==0    n=i*a, existe um i tal que i*a = n
// n%b!=0
// c%n==0   x*n == c    x*(i*a)= c => x*i = c/a
// d%n!=0   nao existe y*n == d


// 2 3 765184 765185
// 2

// 3 4 60 105
// 6

// 2 12 8 2
// 4

// 2 1000000000 985753726 899999956
// 985753726

/*
int main() {
	long long int a, b, c, d;

	cin >> a >> b >> c >> d;

	if(c%a!=0) {
		cout << "-1" << endl;
		return 0;
	}

	long long int m = mdc(a,c);
	//if(c>a) m = c;

	for(unsigned long long int i=a; i<=c; i+=m) {
		if(i%b!=0 && c%i==0 && d%i!=0) {
			cout << i << endl;
			return 0;
		}
	}

	cout << "-1" << endl;
}
*/

int main() {
	long long int a, b, c, d;
	cin >> a >> b >> c >> d;

	long long int achou = -1;
	long long int x=0, y=0;
	long long int i = 1;
	while (x<=y) {
		x = a*i;
		y = c/x;
		if(achou==-1 && x%b!=0 && d%x!=0)
			achou = x;
		else if( (y<achou || achou==-1) && (y%b!=0) && (d%y!=0) )
			achou = y;
		i++;
	}
	cout << achou << endl;
}

/*
in = leia_inteiros(" ")
a, b, c, d = in[1], in[2], in[3], in[4]
var achou := -1
var x, y := 0
var i := 1
enquanto x <= y faça
  x := a * i
  y := c div x
  se (-1 == achou) e (x mod b <> 0) e (d mod x <> 0) então
    achou := x
  senãose (y < achou ou -1 == achou) e (y mod b <> 0) e (d mod y <> 0) então
    achou := y
  fim
  i := i + 1
fim
escreva achou
*/