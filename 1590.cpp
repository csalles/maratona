//1590 Cuarenta e Dois

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int doIt(vector<int> v, int k, int mask = 1<<30) {
	vector<int> withMask;

	if(mask==0) return 0;

	for(int i=0; i<v.size(); i++) {
		if((v[i]&mask) == mask) withMask.push_back(v[i]);
	}
	if(withMask.size()>=k) {
		sort(withMask.begin(), withMask.end());
		int ret = withMask[withMask.size()-1];
		for(int i=1; i<k; i++) ret &= withMask[withMask.size()-1-i];
		int atual = doIt(withMask, k, mask/2);
		return max(ret, atual);
	}
	else {
		return doIt(v, k, mask/2);
	}
}

int main() {
	int t;
	cin >> t;

	while(t--) {
		int n, k;
		cin >> n >> k;

		vector<int> v(n);
		for(int i=0; i<n; i++)
			cin >> v[i];

		/*
		int out = 0;
		for(int i=30; i>=0; i--) {
			int mask = 1<<i;
			vector<int> vMask;
			for(int j=0; j<v.size(); j++) {
				if( (v[j]&mask) == mask ) vMask.push_back(v[j]);
			}
			if(vMask.size()>=k) {
				int atual = vMask[0];
				for(int j=1; j<vMask.size(); j++)
					atual &= vMask[j];
				out = max(out, atual);
			}
		}
		*/

		cout << doIt(v, k) << endl;

	}

}
