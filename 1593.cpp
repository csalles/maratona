//1593 Função Binária

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string metade(string s) {
	string ret = s;
	int carry = 0;
	for(int i=0; i<s.size(); i++) {
		int digit = (s[i]-'0'+carry);
		carry = digit%2==0 ? 0 : 10;
		ret[i] = (char)(digit/2+'0');
	}
	if(ret[0]=='0'&&ret.size()>1) ret = ret.substr(1);
	return ret;
}


int main() {
	int t;
	cin >> t;

	while(t--) {
		string s;
		cin >> s;
		int out = 0;

		while(s[0]!='0') {
			if((s[s.size()-1]-'0')%2==1) out++;
			s = metade(s);
		}


		cout << out << endl;
	}

}
