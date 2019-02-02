//2775

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	while(cin>>n) {
		vector<int> v(n);
		vector<int> t(n);
		for(int i=0; i<n; i++) cin >> v[i];
		for(int i=0; i<n; i++) cin >> t[i];
		int sum = 0;
		for(int i=n-1; i>=0; i--) {
			for(int j=0; j+1<=i; j++) {
				if(v[j]>v[j+1]) {
					swap(v[j], v[j+1]);
					sum = sum + t[j] + t[j+1];
					swap(t[j], t[j+1]);
				}
			}
		}
		cout << sum << endl;
	}
}