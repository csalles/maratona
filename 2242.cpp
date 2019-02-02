//2242 Huaauhahhuahau

#include <string>
#include <iostream>
using namespace std;

string left(string s) {
	string ret = "";
	for(int i=0; i<s.size(); i++) {
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')
			ret += s[i];
	}
	return ret;
}

string right(string s) {
	string ret = "";
	for(int i=s.size()-1; i>=0; i--) {
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')
			ret += s[i];
	}
	return ret;
}

int main() {
	string s;
	cin >> s;

	if(left(s)==right(s)) cout << "S" << endl;
	else cout << "N" << endl;
}