//1253

#include <iostream>
#include <algorithm>
using namespace std;

char desloca(char c, int k) {
	int n = c-'A';
	k = k%26;
	n = (n-k+26)%26;
	return 'A' + n;
}

string cifra(string s, int k) {
	string ret = s;
	for(int i=0; i<ret.size(); i++) {
		ret[i] = desloca(ret[i], k);
	}
	return ret;
}

int main() {
	int n;
	cin >> n;

	while(n--) {
		string s;
		int k;
		cin >> s >> k;
		cout << cifra(s, k) << endl;
	}
}
