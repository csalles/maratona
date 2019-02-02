//2453

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	string ret = "";
	int i = 0;
	while(i<s.size()) {
		if(s[i]=='p') {
			i++;
			ret = ret + s[i];
			i++;
		}
		else {
			ret = ret + ' ';
			i++;
		}
	}
	cout << ret << endl;
}