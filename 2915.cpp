//2915
//Mount Marathon

#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;

	int cont = 1;
	int ant, atual;
	cin >> ant;
	for(int i=1; i<n; i++) {
		cin >> atual;
		if(atual>ant) cont++;
		ant = atual;
	}
	cout << cont << endl;
}