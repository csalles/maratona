//10069

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char s1[10001], s2[101];
long long int memo[10001][101];

string soma(string a, string b) {
	string result;
	int vaium = 0, digito;
	int i=(int)a.size()-1;
	int j=(int)b.size()-1;
	while(i>=0 && j>=0) {
		int digito;
		if(i<0) digito = b[j]-'0' + vaium;
		else if(j<0) digito = a[i]-'0' + vaium;
		else digito = a[i]-'0' + b[j]-'0' + vaium;
		vaium = digito/10;
		digito = digito%10;
		result = (char)('0'+digito) + result;
		i--;
		j--;
	}
	if(vaium) result = '1' + result;

	while(result[0]=='0') {
		if(result=="0") return result;
		result = result.substr(1);
	}

	return result;
}


long long int count(int pos1, int pos2) {
	long long int ret = 0;
	if(pos1<0||pos2<0) return 0;

	if(memo[pos1][pos2]!=-1)
		return memo[pos1][pos2];

	if(pos2==0) {
		for(int i=0; i<=pos1; i++)
			if(s1[i]==s2[0]) ret++;
	}
	else {
		for(int i=0; i<=pos1; i++) {
			if(s1[i]==s2[pos2]) {
				ret += count(i-1, pos2-1);
			}
		}
	}

	return memo[pos1][pos2] = ret;
}

int main() {
	int cases;
	cin >> cases;
	while( cases-- ) {
		cin >> s1;
		cin >> s2;

		//cout << s1 << endl << s2 << endl;

		for(int i=0; s1[i]!='\0'; i++)
			for(int j=0; s2[j]!='\0'; j++)
				memo[i][j] = -1;

		cout << count(strlen(s1)-1, strlen(s2)-1) << endl;
	}
}

/*
lis( abcdgh , aedfhr ) = lis(bcdgh , edfhr)+1

lis(bcdgh , edfhr) = MAX(
		lis(cdgh , edfhr ),
		lis(bcdgh , dfhr)

	)


lis( abcdgh , aedfhr )
	-> MAX ( lis(abcdg , aedfhr  )  ,
	         lis(abcdgh , aedfh) )


lis(abcdgh , aedfh) ) = lis(abcdg , aedf) + 1

*/