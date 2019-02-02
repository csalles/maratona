//1014

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int km;
	double consumo;
	cin >> km >> consumo;
	double saida = (double)km / consumo;
	cout << fixed << setprecision(3) << saida << " km/l" << endl;
}
