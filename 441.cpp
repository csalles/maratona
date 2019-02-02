#include <stdio.h>
//http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=382

int S[12], k;
int hasNum[12];
int V[6];

int first=1;

void bt(int index) {
	if(index>=6) {
		printf("%d", V[0]);
		for(int i=1; i<6; i++)
			printf(" %d", V[i]);
		printf("\n");
		return;
	}
	for(int i=0; i<k; i++) {
		if(!hasNum[i] && (index==0||S[i]>V[index-1])) {
			hasNum[i] = 1;
			V[index] = S[i];
			bt(index+1);
			hasNum[i] = 0;
		}
	}
}

int main() {
	while(1) {
		scanf("%d", &k);
		if(k==0) break;

		if(first) first=0;
		else putchar('\n');

		for(int i=0; i<k; i++)
		   scanf("%d", &S[i]);

		for(int i=0; i<12; i++)
			hasNum[i] = 0;

		bt(0);
	}
}