//10128 Queue
#include <iostream>
#include <vector>
using namespace std;

unsigned long long int fat(int f) {
	if(f==0) return 1;
	else return fat(f-1)*(unsigned long long int)f; 
}

//person to be put on line (starting from n)
// left spaces on left
// right spaces on right
// notSeen spaces not seen
// n = size of queue (does not vary)
// p = number of yet to be seen on left
// r = number of yet to be seen on right

unsigned long long int bt(int person, int left, int right, int notSeen,
						  int n, int p, int r) {

	if(p<0||r<0||left<p||right<r||notSeen<0) return 0;
	if(left==0&&right==0) {
		if(p==0&&r==0) return 1;
		else return 0;
	}
	if(person==0) return fat(notSeen);

	unsigned long long int sum = 0;
	//putting person on left
	for(int pos=0; pos<left; pos++) {
		int newNotSeen = notSeen + left-1-pos;
		sum+=bt(person-1, pos, right, newNotSeen, n, p-1, r);
	}

	//putting person on right
	for(int pos=0; pos<right; pos++) {
		int newNotSeen = notSeen + right-1-pos;
		sum+=bt(person-1, left, pos, newNotSeen, n, p, r-1);
	}

	//putting person on notSeen
	if(notSeen>0)
		sum+=bt(person-1, left, right, notSeen-1, n, p, r);
	return sum;
}

unsigned long long int solve(int n, int p, int r) {
	if(n==1) {
		if(p==1 && r==1) return 1;
		else return 0;
	}
	else if(n==2) {
		if(p==1&&r==2) return 1;
		else if(p==2&&r==1) return 1;
		else return 0;
	}
	//n>=3
	//start putting two higher people
	unsigned long long int sum = 0;
	for(int left=p-1; left<n; left++) { 
		for(int right=r-1; left+right+2<=n; right++) { 
			int notSeen = n-2-left-right;
			if(notSeen<0) continue;
			sum += bt(n-2, left, right, notSeen, n, p-1, r-2);
			sum += bt(n-2, left, right, notSeen, n, p-2, r-1);
		}
	}
	return sum;
}

int main() {
	int t;
	int n, p, r;

	cin >> t;
	while(t--) {
		cin >> n >> p >> r;
		cout << solve(n, p, r) << endl;
	}
}