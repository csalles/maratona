//2879

#include <iostream>
using namespace std;

int main(){
	int n, cont=0, k;
	cin >> n;
	while(n--) {
		cin >> k;
		if(k!=1) cont++;
	}
	cout << cont << endl;
}