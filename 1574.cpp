//1574

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int main() {
	int t;
	string line;
	getline(cin, line);
	t = atoi(line.c_str());

	while(t--) {
		int n;
		getline(cin, line);
		n = atoi(line.c_str());

		int pos = 0;
		vector<bool> v(n);
		for(int i=0; i<n; i++) {
			getline(cin, line);
			if(line=="LEFT") {
				v[i] = false;
				pos--;
			}
			else if(line=="RIGHT") {
				v[i] = true;
				pos++;
			}
			else {
				int same = atoi(line.c_str()+8);
				v[i] = v[same-1];
				if(v[i]) pos++;
				else pos--;
			}
		}
		cout << pos << endl;
	}

}
