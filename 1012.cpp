//1012


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	cout << "TRIANGULO: " << fixed << setprecision(3) << a*c/2.0 << endl; //7.800
	cout << "CIRCULO: "   << fixed << setprecision(3) << c*3.14159*c << endl; //84.949
	cout << "TRAPEZIO: "  << fixed << setprecision(3) << (a+b)*c/2 << endl; //18.200
	cout << "QUADRADO: "  << fixed << setprecision(3) << b*b << endl;//16.000
	cout << "RETANGULO: " << fixed << setprecision(3) << a*b << endl; //12.000
}

