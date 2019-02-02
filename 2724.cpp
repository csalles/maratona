//2724

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool dangerous(string line, string danger) {
	int dSize = danger.size();
	for(int i=0; i+dSize-1<line.size(); i++) {
		bool ok = true;
		for(int j=0; j<dSize; j++) {
			if(line[i+j]!=danger[j]) {
				ok = false;
				break;
			}
		}
		if(ok) {
			if(i+dSize<line.size()) {
				char c = line[i+dSize];
				if(c>='A'&&c<='Z') return true;
			}
			else return true;
		}
	}
	return false;
}

int main() {
	int n;
	cin >> n;

	while(n--) {
		int t;
		cin >> t;
		vector<string> v(t);
		for(int i=0; i<t; i++) cin >> v[i];
		
		int u;
		cin >> u;
		for(int i=0; i<u; i++) {
			string line;
			cin >> line;
			bool dangerLine = false;
			for(int i=0; i<t; i++) {
				if(dangerous(line, v[i])) {
					dangerLine = true;
					break;
				}
			}
			if(dangerLine) cout << "Abortar" << endl;
			else cout << "Prossiga" << endl;
		}
		if(n>0) cout << endl;
	}
	
}
