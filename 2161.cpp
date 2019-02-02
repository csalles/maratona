//2161 Raiz Quadrada de 10

#include <iostream>
#include <iomanip>
using namespace std;


int main() {
	double v[101];
	v[0] = 0;
	v[1] = 1.0/6.0;
	for(int i=2; i<=100; i++) v[i] = 1.0 / (v[i-1] + 6.0);
	int n;

	cin >> n;
	cout << setprecision(10) << fixed << 3.0+v[n] << endl;
}