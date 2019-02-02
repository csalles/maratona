#include <string>
#include <iostream>

using namespace std;

string s1, s2;

unsigned long long int memo[10001][101];

string add(string a, string b) {
	for(int i=0; ;i++) {
		
	}
}

unsigned long long int sub(int sz1, int sz2) {

	//if(sz1<0 || sz1<sz2) return 0;

	if(memo[sz1][sz2]!=-1) return memo[sz1][sz2];

	if(sz2==0) {
		unsigned long long int cont = 0;
		for(int i=0; i<=sz1; i++)
			if(s1[i]==s2[0]) cont++;
		return memo[sz1][sz2] = cont;
	}

	unsigned long long int cont = 0;
	for(int i=1; i<=sz1; i++) {
		if(s1[i]==s2[sz2]) {
			unsigned long long int newCont = cont + sub(i-1, sz2-1);
			if(newCont < cont) while(1) cont++;
			cont += sub(i-1, sz2-1);
		}
	}
	return memo[sz1][sz2] = cont;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		cin >> s1 >> s2;
		for(int i=0; i<(int)s1.size(); i++)
			for(int j=0; j<(int)s2.size(); j++)
				memo[i][j] = -1;
		cout << sub(s1.size()-1, s2.size()-1) << endl;
	}
}