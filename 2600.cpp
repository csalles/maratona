//2600
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
	int n;
	cin >> n;

	while(n--) {
		vector<int> v(6);
		set<int> s;
		for(int i=0; i<6; i++) {
			cin >> v[i];
			if(v[i]>=1&&v[i]<=6)
				s.insert(v[i]);
		}
		bool ok = s.size()==6;
		if(v[0]+v[5]!=7) ok = false;
		if(v[1]+v[3]!=7) ok = false;
		if(v[2]+v[4]!=7) ok = false;
		if(ok) cout << "SIM" << endl;
		else cout << "NAO" << endl;
	}
}
