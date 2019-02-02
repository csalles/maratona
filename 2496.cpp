//2496

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool checkOneTrade(string s, int idx1, int idx2) {
	bool ok = true;
	swap(s[idx1], s[idx2]);
	for(int i=1; i<s.size(); i++) {
		if(s[i]<s[i-1]) {
			ok = false;
			break;
		}
	}
	swap(s[idx1], s[idx2]);
	return ok;
}

int main() {
	int cc;
	cin >> cc;

	while(cc--) {
		int n;
		string s;
		cin >> n >> s;

		bool ok = false;

		for(int i=0; i<s.size() && !ok; i++)
			for(int j=i+1; j<s.size() && !ok; j++)
				if(checkOneTrade(s,i,j))
					ok=true;

		if(ok) 
			cout << "There are the chance." << endl;
		else
			cout << "There aren't the chance." << endl;
	}
}
