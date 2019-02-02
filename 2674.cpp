//2674 Super Primos: Ativar!

#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> primos(int n) {
	vector<int> p;
	p.push_back(2);
	for(int i=3; i<=n; i+=2) {
		bool isPrime = true;
		for(int j=0; j<p.size(); j++) {
			if(p[j]*p[j]>i) 
				break;
			if(i%p[j]==0) {
				isPrime=false; 
				break;
			}
		}
		if(isPrime) p.push_back(i);
	}
	return p;
}

int main() {
	vector<int> p = primos(100000);
	set<int> super, prime;
	for(int i=0; i<p.size(); i++) {
		int aux = p[i];
		bool isSuper = true;
		while(aux!=0) {
			int digito = aux%10;
			if(!(digito==2||digito==3||digito==5||digito==7)) {
				isSuper=false;
				break;
			}
			aux /=10;
		}
		if(isSuper) super.insert(p[i]);
		else prime.insert(p[i]);
	}

	int n;
	while( cin>>n ) {
		if(super.count(n)) cout << "Super" << endl;
		else if(prime.count(n)) cout << "Primo" << endl;
		else cout << "Nada" << endl;
	}

}