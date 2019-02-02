//2845

#include <iostream>
#include <vector>
#include <set>
using namespace std;


/*
int main() {
	vector<int> p;
	p.push_back(2);
	for(int i=3; i<1010; i+=2) {
		bool isPrime = true;
		for(int j=0; j<p.size(); j++) {
			if(p[j]*p[j]>i) break;
			if(i%p[j]==0) {isPrime=false; break;}
		}
		if(isPrime) p.push_back(i);
	}

	int n;
	cin >> n;
	vector<int> v(n);
	set<int> s;

	int maior;

	for(int i=0; i<n; i++) {
		cin >> v[i];
		if(i==0) maior = v[i];
		else if(v[i]>maior) maior = v[i];
		int k = v[i];
		for(int j=0; j<p.size(); j++) {
			if(p[j]*p[j]>v[i]) break;
			while(k%p[j]==0) {
				s.insert(p[j]);
				k /= p[j];
			}
		}
		if(k>1) s.insert(k);
	}

	vector<int> vv;
	for(int j=0; j<p.size(); j++) {
		if(s.count(p[j])==0) {
			vv.push_back(p[j]);
		}
	}

	for(long i=maior+1; ;i++) {
		long f = i;
		bool ok = false;
		for(int j=0; j<vv.size(); j++) {
			while(f%vv[j]==0) f/=vv[j];
			if(f==1) {
				ok = true;
				break;
			}
		}

		if(!ok) {
			bool isPrime = true;
			for(int j=0; j<p.size(); j++) {
				if(p[j]*p[j]>i) break;
				if(i%p[j]==0) {
					isPrime = false;
					break;
				}
			}
			if(isPrime && s.count(i)==0) ok = true;
		}

		if(ok) {
			cout << i << endl;
			break;
		}
	}


}
*/

//Euclides
long int mdc(long int a, long int b){
	if(a<b) return mdc(b,a);
	while(b != 0){
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
//Algoritmo do MMC
long int mmc(long int a, long int b){
	return a * (b / mdc(a, b));
}

int main() {
	int n;
	long int v[10001];
	long int maior;

	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%ld", &v[i]);
		if(i==0) maior = v[i];
		else if(v[i]>maior) maior = v[i];
	}

	for(long int num=maior+1; ;num++) {
		bool ok = true;
		for(int i=0; i<n; i++) {
			if(mdc(num, v[i])!=1) {
				ok = false;
				break;
			}
		}
		if(ok) {
			cout << num << endl;
			break;
		}
	}

}
