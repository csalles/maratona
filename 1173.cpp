//1173 Preenchimento de Vetor I

#include <iostream>
#include <string>
using namespace std;

string dobro(string s) {
	string ret = "";
	int vaium = 0;
	for(int i=s.size()-1; i>=0; i--) {
		int digito = 2*(s[i]-'0') + vaium;
		vaium = digito/10;
		digito = digito%10;
		ret = (char)(digito+'0') + ret;
	}
	if(vaium) ret = '1' + ret;
	return ret;
}

int main() {
	string s;
	cin >> s;

	for(int i=0; i<10; i++) {
		cout << "N[" << i << "] = " << s << endl;
		s = dobro(s);
	}
}

