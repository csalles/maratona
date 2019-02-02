//Looking for the Risk Factor
//2914

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <set>
using namespace std;

vector<int> primos(int n) {
	vector<int> ret;
	ret.push_back(2);

	for(int i=3; i<=n; i+=2) {
		int raiz = (int)sqrt(i);
		bool ehPrimo = true;
		for(int j=0; j<(int)ret.size(); j++) {
			if(ret[j]>raiz) break;
			if(i%ret[j]==0) {
				ehPrimo = false;
				break;
			}
		}
		if(ehPrimo) ret.push_back(i);
	}

	return ret;
}

int main() {
	vector<int> pd(100001, 0);
	vector<int> p = primos(100001);
/*
	for(int i=0; i<p.size(); i++)
		cout << p[i] << endl;
*/
	for(int i=0; i<p.size(); i++)
		for(int j=p[i]; j<100001; j+=p[i])
			pd[j] = p[i];

	long int casos;
	scanf("%ld", &casos);

	while(casos--) {
		long int n, k;
		scanf("%ld%ld", &n, &k);
/*
for(int i=2; i<=n; i++) {
	cout << i << " := " << pd[i] << endl;
}
*/

		
		if(k>=n) {
			printf("%ld\n", n-1);
			continue;
		}


		if(k>(int)sqrt(n)) {
			long int out = n-1;
			for(int i=0; i<p.size(); i++) {
				if(p[i]>k&&p[i]<=n) {
					out-=(n/p[i]);
					//cout << "*** " << p[i] << endl;
				}
				if(p[i]>n) break;
			}
			printf("%ld\n", out);
			continue;
		}

		long int cont = 0;
		for(int i=2; i<=n; i++)
			if(pd[i]<=k) cont++;
		printf("%ld\n", cont);
	}
}
