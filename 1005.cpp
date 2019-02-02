//1005

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double x, y;
	cin >> x >> y;
	double media = (3.5*x + 7.5*y)/11.0;
	cout << "MEDIA = " << fixed << setprecision(5) << media << endl;
}