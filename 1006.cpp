//1006

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double n1, n2, n3;
	cin >> n1 >> n2 >> n3;
	double media = (2*n1+3*n2+5*n3)/10.00;
	cout << "MEDIA = " << fixed << setprecision(1) << media << endl;
}
