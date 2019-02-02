//2785

#include <iostream>
using namespace std;

int n;
int m[101][101];
int sum[101][101];
int memo[101][101][101];

int pd(int lin, int esq, int dir) {
	if(lin==0) return m[0][esq];
	if(memo[lin][esq][dir]!=-1) return memo[lin][esq][dir];
	int aux1 = pd(lin-1, esq+1, dir);
	int aux2 = pd(lin-1, esq, dir-1);
	int ret = aux1<aux2 ? aux1 : aux2;
	for(int i=esq; i<=dir; i++)
		ret += m[lin][i];
	return memo[lin][esq][dir] = ret;
}

int main() {
	int n;
	cin >> n;

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> m[i][j];
			if(i==0) sum[i][j] = m[i][j];
			else sum[i][j] = sum[i-1][j] + m[i][j];
			for(int k=0; k<n; k++) memo[i][j][k] = -1;
		}
	}

	cout << pd(n-1, 0, n-1) << endl;

/*
	int esq = 0;
	int dir = n-1;
	int lin = n-1;
	int output = 0;

	while(lin>=0) {
		for(int j=esq; j<=dir; j++)
			output+=m[lin][j];
		lin--;
		if(lin<0) break;
		if(sum[lin][esq]>sum[lin][dir]) {
			esq++;
		}
		else {
			dir--;
		}
	}

	cout << output << endl;
*/
}