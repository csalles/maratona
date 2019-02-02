//2812

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int m;
		vector<int> v;
		cin >> m;
		for(int j=0; j<m; j++) {
			int k;
			cin >> k;
			if(k%2==1) v.push_back(k);
		}
		if(v.size()==0) {
			cout << endl;
		}
		else {
			sort(v.begin(), v.end());

			cout << v[v.size()-1];
			int esq = 0;
			int dir = v.size()-2;

			while(esq<=dir) {
				cout << " " << v[esq++];
				if(esq<=dir) cout << " " << v[dir--];
			}
			cout << endl;
		}
	}
}
