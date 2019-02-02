//1020

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	long int dias;
	cin >> dias;
	cout << dias/365 << " ano(s)" << endl;
	dias = dias%365;
	cout << dias/30 << " mes(es)" << endl;
	dias = dias%30;
	cout << dias << " dia(s)" << endl;
}
