//1008

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int number;
	int a;
	double b;
	cin >> number >> a >> b;
	double conta = ((double)a)*b;
	cout << "NUMBER = " << number << endl;
	cout << "SALARY = U$ " << fixed << setprecision(2) << conta << endl;
}

