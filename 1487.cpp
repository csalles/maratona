//1487 Six Flags

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int memo[601];

int pd(int t, vector<pair<int, int> > &v) {
	if(memo[t]!=-1) return memo[t];

	int best = 0;
	for(int i=0; i<v.size(); i++) {
		int d = v[i].first;
		int p = v[i].second;
		if(d<=t) {
			int atual = pd(t-d, v) + p;
			if(atual>best) best = atual;
		}
	}
	return memo[t] = best;
}

int main() {
	int n, t;

	for(int h=1; ;h++) {
		cin >> n >> t;
		if(!n&&!t) break;
		vector< pair<int,int> > v(n);
		for(int i=0; i<n; i++) {
			cin >> v[i].first >> v[i].second;
		}

		for(int i=0; i<=t; i++)
			memo[i] = -1;

		cout << "Instancia " << h << endl;
		cout << pd(t, v) << endl << endl;
	}
}
