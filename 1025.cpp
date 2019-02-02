#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;



int main() {
	int n, q;
	int cc = 1;
	int pos[10010], v[10010];


	while(1) {
		cin >> n >> q;
		if(!n&&!q) break;
		cout << "CASE# " << cc++ << ":" << endl;

		for(int i=0; i<10001; i++) pos[i] = -1;

		for(int i=0; i<n; i++) cin >> v[i];
		
		sort(v, v+n);

		for(int i=0; i<n; i++) 
			if(pos[v[i]]==-1) pos[v[i]]=i+1;
		

		for(int i=0; i<q; i++) {
			int val;
			cin >> val;
			if(pos[val]==-1) cout << val << " not found" << endl;
			else cout << val << " found at " << pos[val] << endl;
		}

	}
}
