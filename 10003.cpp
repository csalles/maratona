#include <stdio.h>

int L, N;
int V[53];

int memo[53][53];

/*
[0  1  2  3   4]
 0 25 50 75 100


cut(0, 4)
   i=1 = 225
   esqCost = cut(0, 1) = 0
   dirCost = cut(1, 4) = 125
      cut(1,4)
      i=2
         esqCost = cut(1,2) = 0
         dirCost = cut(2,4) = 50
         	cut(2, 4) = 50
         	i = 3
         		esqCost = cut(2,3) = 0
         		dirCost = cut(3,4) = 0
         		l = 50
         l = 75
      i=3
    l = 100
   i=2
   i=3
*/

int cut(int esq, int dir) {
	int l = V[dir] - V[esq];
	int MINCOST = -1;

	if(esq+1>=dir) return 0;

	if(memo[esq][dir]!=-1) return memo[esq][dir];

	for(int i=esq+1; i<=dir-1; i++) {
		int esqCost = cut(esq, i);
		int dirCost = cut(i, dir);
		int aux = l + esqCost + dirCost;
		if(MINCOST==-1) MINCOST = aux;
		else if(aux<MINCOST) MINCOST=aux;
	}

	return memo[esq][dir] = MINCOST;
}




int main() {
	while(1) {
		scanf("%d", &L);
		if(L==0) break;
		scanf("%d", &N);

		V[0] = 0;
		V[N+1] = L;
		for(int i=1; i<=N; i++)
			scanf("%d", &V[i]);

		for(int i=0; i<53; i++)
			for(int j=0; j<53; j++)
				memo[i][j] = -1;

		printf("The minimum cutting is %d.\n", cut(0, N+1) );

	}
}