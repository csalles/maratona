#include <iostream>
#include <assert.h>
#include <map>
using namespace std;

unsigned long long int fat(int n) {
	if(n==0) return 1;
	else return fat(n-1)*(unsigned long long int)n;
}

#define PRINTHEADER() {}//{ cout << "left\tright\tnotSeen\tp\tr" << endl;}
#define PRINT() {} //{cout<<left << "\t" << right << "\t" << notSeen << "\t" << p << "\t" << r << endl;}

unsigned long long int bt(int left, int right, int notSeen,
						  int n, int p, int r) 
{

	//PRINT();

	if(left<p||right<r||notSeen<0||p<0||r<0) return 0;
	if(left==0&&right==0) {
		if(p>0||r>0) return 0;
		else return fat(notSeen);
	}
	unsigned long long int sum = 0;
	//colocando em left
	for(int newLeft=0; newLeft<left; newLeft++) {
		// left+right+notSeen = newLeft+newNotseen+right+1
		// left+notSeen = newLeft+newNotSeen+1
		// newNotSeen = left+notSeen-newLeft-1
		int newNotSeen = left+notSeen-newLeft-1;
		assert(left+notSeen==newLeft+newNotSeen+1);
		sum += bt(newLeft, right, newNotSeen, n, p-1, r);
	}
	//colocando em right
	for(int newRight=0; newRight<right; newRight++) {
		// idem dedução anterior
		int newNotSeen = right+notSeen-newRight-1;
		assert(right+notSeen==newRight+newNotSeen+1);
		sum += bt(left, newRight, newNotSeen, n, p, r-1);
	}
	//colocando na parte nao vista
	sum += notSeen*bt(left, right, notSeen-1, n, p, r);
	return sum;
}

unsigned long long int solve(int n, int p, int r) {
	if(n==1)
		return p==1&&r==1 ? 1 : 0;
	if(n==2) {
		if(p==1&&r==2) return 1;
		if(p==2&&r==1) return 1;
		return 0;
	}
	unsigned long long int sum = 0;
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			int left = i-1;
			int right = n-j;
			int notSeen = n-2-left-right;

			sum += bt(left, right, notSeen, n, p-1, r-2);
			sum += bt(left, right, notSeen, n, p-2, r-1);
		}
	}
	return sum;
}

int main() {
	int t;
	cin >> t;

//PRINTHEADER();

	int memo[14][14][14];
	for(int i=0; i<14; i++)
		for(int j=0; j<14; j++)
			for(int k=0; k<14; k++)
				memo[i][j][k] = -1;


	while(t--) {
		int n, p, r;
		cin >> n >> p >> r;
		if(memo[n][p][r]==-1) memo[n][p][r] = solve(n,p,r);
		cout << memo[n][p][r] << endl;
	}
}