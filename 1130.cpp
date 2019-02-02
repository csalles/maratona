//1130 Jogo da Velha

#include <iostream>
#include <map>
#include <string>
using namespace std;

#define ONESIDEX 0
#define TWOSIDESX 1
#define NOSIDEX 2

#define MARIA_WIN 1
#define MARIA_LOSE 2

/*
int memo[3][10010];

int pd_old(int tipo, int n) {

	if(memo[tipo][n]!=-1) return memo[tipo][n];

	if(tipo==ONESIDEX) {

		if(n)

	}
	else if(tipo==TWOSIDESX) {

	}
	else if(tipo==NOSIDEX) {

		//if(n<=2) return MARIA_WIN;

		if( pd(ONESIDEX, n-1)==MARIA_WIN )
			return memo[tipo][n] = MARIA_WIN;
		for(int i=1; n-1-i>0; i++) {
			int j = n-1-i;
			if( pd(ONESIDEX, i) == MARIA_WIN )
				return memo[tipo][n] = MARIA_WIN;
			if( pd(ONESIDEX, j) == MARIA_WIN )
				return memo[tipo][n] = MARIA_WIN;
		}
		return memo[tipo][n] = MARIA_LOSE;
	}
}
*/

#define CHECK_X(s, i) ( i>=0 && i<s.size() && s[i]=='X' )

map<string,bool> memo;

bool pd(string s) {
	if(memo.count(s)) return memo[s];

	for(int i=0; i<s.size(); i++) {
		if(s[i]=='.') {
			if( CHECK_X(s,i-1) && CHECK_X(s,i-2) )
				return memo[s]=true;
			if( CHECK_X(s,i-1) && CHECK_X(s,i+1) )
				return memo[s]=true;
			if( CHECK_X(s,i+1) && CHECK_X(s,i+2) )
				return memo[s]=true;
		}
	}
	for(int i=0; i<s.size(); i++) {
		if(s[i]=='.') {
			s[i] = 'X';
			if( !pd(s) ) return memo[s] = true;
			s[i] = '.';
		}
	}

	return memo[s]=false;
}

int main() {
	int n;
	while(1) {
		cin >> n;
		if(!n) break;

		string s;
		cin >> s;

		if(pd(s)) cout << "S" << endl;
		else cout << "N" << endl;
	}
}
