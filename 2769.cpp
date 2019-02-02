//2769

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n;
	while (cin>>n) {
		vector<long> a1(n);
		vector<long> a2(n);
		long e1, e2;
		cin >> e1 >> e2;
		for(int i=0; i<n; i++)
			cin >> a1[i];
		for(int i=0; i<n; i++)
			cin >> a2[i];
		vector<long> t1(n);
		vector<long> t2(n);
		for(int i=0; i<n-1; i++)
			cin >> t1[i];
		for(int i=0; i<n-1; i++)
			cin >> t2[i];
		long out1, out2;
		cin >> out1 >> out2;
		a1[0] += e1;
		a2[0] += e2;
		a1[n-1] += out1;
		a2[n-1] += out2;
		for(int i=0; i<n-1; i++) {
			a1[i+1] += min(a1[i], a2[i]+t2[i]);
			a2[i+1] += min(a2[i], a1[i]+t1[i]);
		}
		cout << min(a1[n-1], a2[n-1]) << endl;
	}
}
