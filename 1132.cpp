//1132

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int x, y;
	cin >> x >> y;
	if(x>y) swap(x, y);
	
	int soma = (x+y)*(y-x+1)/2;



	//cout << soma << endl;

	int esq, dir;
	for(esq=x; esq%13!=0; esq++);
	for(dir=y; dir%13!=0; dir--);

	//cout << "esq = " << esq << endl;
	//cout << "dir = " << dir << endl;
	//cout << "  n = " << ((dir-esq)/13+1) << endl;
	int n = ((dir-esq)/13+1);
	soma -= ((dir+esq)*n/2);

	cout << soma << endl;
}
