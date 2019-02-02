//1192 O jogo Matemático de Paula

#include <iostream>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		int d1 = s[0]-'0';
		int d2 = s[2]-'0';

		if(s[0]==s[2]) cout << d1*d2 << endl;
		else if(s[1]>='a'&&s[1]<='z') cout << d1+d2 << endl;
		else if(s[1]>='A'&&s[1]<='Z') cout << d2-d1 << endl;
	}	
}
