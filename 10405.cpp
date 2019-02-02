//10405

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char s1[1001], s2[1001];
int memo[1001][1001];

int lis(int sz1, int sz2) {
	if(sz1==0 || sz2==0) return 0;

	if(memo[sz1][sz2]!=-1) return memo[sz1][sz2];

	if(s1[sz1-1] == s2[sz2-1]) {
		memo[sz1][sz2] = lis(sz1-1, sz2-1) + 1;
	}
	else {
		int aux1 = lis(sz1-1, sz2);
		int aux2 = lis(sz1, sz2-1);
		memo[sz1][sz2] = (aux1>aux2) ? aux1 : aux2;
	}
	return memo[sz1][sz2];
}

int main() {
	//while( scanf("%[^\n]s%[ˆ\n]s", s1, s2)!=EOF ) {
	while( cin.getline(s1, 1000) ) {
		cin.getline(s2, 1000);

		for(int i=0; i<1001; i++)
			for(int j=0; j<1001; j++)
				memo[i][j] = -1;

		printf("%d\n", lis(strlen(s1), strlen(s2)));
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