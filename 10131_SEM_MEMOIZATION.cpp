#include <stdio.h>


int W[1001], S[1001];
int n;
int next[1001];

//int memo[1001];

int bt(int first) {
	int maxSeq = 1;

	next[first] = first;
	for(int i=0; i<n; i++) {
		if(W[i]>W[first] && S[i]<S[first]) {
			int aux = bt(i) + 1;
			if(aux>maxSeq) {
				maxSeq=aux;
				next[first] = i;
			}
		}
	}

	return maxSeq;
}

int main() {

	n = 0;
	while( scanf("%d %d", &W[n], &S[n])!=EOF ) {
		n++;
	}

	int maxSeq = bt(0);
	int best = 0;
	for(int i=1; i<n; i++) {
		int aux = bt(i);
		if(aux>maxSeq) {
			maxSeq=aux;
			best = i;
		}
	}
	printf("%d\n", maxSeq);
	while(1) {
		printf("%d\n", best+1);
		if(next[best]==best) break;
		best = next[best];
	}
}

