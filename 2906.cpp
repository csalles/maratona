//2906
//Database of Clients

#include <iostream>
#include <string>
#include <set>
using namespace std;

string simplify(string s) {
	string ret;
	bool before = true;
	bool plusFound = false;

	for(int i=0; i<s.size(); i++) {
		if(s[i]=='@') {
			ret += s[i];
			before=false;
		}
		else if(!before) {
			ret += s[i];
		}
		else {
			if(!plusFound) {
				if(s[i]=='+') plusFound=true;
				else if(s[i]!='.') ret+=s[i];
			}
		}
	}
	return ret;
}

int main() {
	set<string> s;
	int n;

	cin >> n;
	while(n--) {
		string str;
		cin >> str;
		s.insert(simplify(str));
	}
	cout << s.size() << endl;
}
