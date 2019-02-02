//1018

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	long int n, out;
	cin >> n;

	cout << n << endl;
	out = n/100;
	cout << out << " nota(s) de R$ 100,00" << endl;
	n -= out*100;

	out = n/50;
	cout << out << " nota(s) de R$ 50,00" << endl;
	n -= out*50;

	out = n/20;
	cout << out << " nota(s) de R$ 20,00" << endl;
	n -= out*20;

	out = n/10;
	cout << out << " nota(s) de R$ 10,00" << endl;
	n -= out*10;

	out = n/5;
	cout << out << " nota(s) de R$ 5,00" << endl;
	n -= out*5;

	out = n/2;
	cout << out << " nota(s) de R$ 2,00" << endl;
	n -= out*2;

	cout << n << " nota(s) de R$ 1,00" << endl;
}
