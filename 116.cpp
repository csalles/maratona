#include <stdio.h>

typedef int PESO;

int n, m;
PESO M[10][100];
PESO memo[10][100];

PESO path(int lin, int col) {
	PESO acima, meio, abaixo;

	if(memo[lin][col]!=-1)
		return memo[lin][col];

	if(col==m-1) {
		return memo[lin][col] = M[lin][col];
	}

	acima = path(lin>0 ? lin-1 : n-1, col+1);
	meio = path(lin, col+1);
	abaixo = path(lin<n-1 ? lin+1 : 0, col+1);

	PESO MIN = acima<meio ? acima : meio;
	MIN = abaixo<MIN ? abaixo : MIN;

	return memo[lin][col] = MIN+M[lin][col];
}

int main() {
	while(1) {
		if(scanf("%d%d", &n, &m)==EOF) break;
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++) {
				scanf("%d", &M[i][j]);
				memo[i][j] = -1;
			}


		PESO MIN = path(0,0);
		int LIN = 0;
		for(int i=1; i<n; i++) {
			PESO atual = path(i,0);
			if(atual<MIN) {
				MIN=atual;
				LIN=i;
			}
		}

		printf("%d", LIN+1);
		for(int j=1; j<m; j++) {
			int index[3];
			index[0] = LIN>0 ? LIN-1 : n-1;
			index[1] = LIN;
			index[2] = LIN<n-1 ? LIN+1 : 0;
			for(int i=0; i<3; i++) {
				for(int k=i+1; k<3; k++) {
					if(index[i]>index[k]) {
						int aux = index[i];
						index[i] = index[k];
						index[k] = aux;
					}
				}
			}
			int PROXLIN = index[0];
			if( memo[index[1]][j] < memo[PROXLIN][j] ) {
				PROXLIN = index[1];
			}
			if( memo[index[2]][j] < memo[PROXLIN][j] ) {
				PROXLIN = index[2];
			}
			LIN = PROXLIN;
			printf(" %d", LIN+1);			
		}
		printf("\n");

		printf("%d\n", MIN);
	}
}