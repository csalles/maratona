//1010

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int c1, qt1;
	int c2, qt2;
	double v1, v2;
	cin >> c1 >> qt1 >> v1;
	cin >> c2 >> qt2 >> v2;
	double sum = (double)qt1*v1 + (double)qt2*v2;
	cout << "VALOR A PAGAR: R$ " << fixed << setprecision(2) << sum << endl;
}
