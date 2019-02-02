//1542
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
	int p, d, q;

	while(1) {
		cin >> p;
		if(!p) break;
		cin >> d >> q;

		// paginas = dias * p
		// dias = paginas/p (1)

		// paginas = (dias-d) * q
		// dias - d = paginas/q
		// dias = paginas/q + d (2)

		// De (1) e (2) temos:
		// paginas/p = paginas/q + d
		// paginas/p - paginas/q = d
		// (q*paginas - p*paginas) / p*q = d
		// (q-p)*paginas = p*q*d
		// paginas = p*q*d/(q-p) (3)

		//int num = p*q*d;
		//int den = q-p;

		int paginas = p*q*d/(q-p); //num%den==0 ? num/den : (num/den + 1);

		//cout << "num = " << num << endl;
		//cout << "den = " << den << endl;

		if(paginas==1) cout << "1 pagina" << endl;
		else cout << paginas << " paginas" << endl; 

		// dias*p = (dias-d) *q
		// dias*p = dias*q - d*q
		// dias*(p-q) = -d*q
		// dias = (-d*q)/(p-q)

		// dias = paginas/p
		
		// dias*q - d*q = paginas
		// dias*q = paginas + d*q
		// dias = (paginas + d*q)/q

		// paginas/p = (paginas + d*q)/q
		// paginas = p* (paginas + d*q) / q
		// paginas = (p * paginas)/q + p*d*q/q
		// (1-p/q) * paginas = p*d
		// paginas = p*d / (1-p/q)

		// p q  d
		// 5 10 6


	}
}