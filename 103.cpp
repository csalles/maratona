#include <stdio.h>

int K, N;
int B[31][10];

int into[31][31];
int next[31];

//nao rotaciona as boxes
void checkInto() {

	//ordena as dimensoes das boxes	
	for(int i=0; i<K; i++) {
		for(int j=0; j<N; j++) {
			for(int k=j+1; k<N; k++) {
				if( B[i][j]>B[i][k] ) {
					int aux = B[i][j];
					B[i][j] = B[i][k];
					B[i][k] = aux;
				}
			}
		}
	}

	//preenche a matriz into
	for(int i=0; i<K; i++) {
		for(int j=0; j<K; j++) {
			int canBeInto = 1;
			for(int nn=0; nn<N; nn++) {
				if( B[i][nn]>=B[j][nn]) {
					canBeInto = 0;
					break;
				}
			}
			into[i][j] = canBeInto;
		}
	}
}

// nao funciona ... onde esta o caso base?
int stack(int index) {
	int max = 1;
	next[index] = index;

	for(int i=0; i<K; i++) {
		if( into[index][i] ) {
			int aux = stack(i)+1;
			if(aux>max) {
				max = aux;
				next[index] = i;
			}
		}
	}

	return max;
}

int main() {
	while( scanf("%d%d", &K, &N)!=EOF ) {
		for(int i=0; i<K; i++) {
			for(int j=0; j<N; j++) {
				scanf("%d", &B[i][j]);
			}
		}
		checkInto();

		/*
		for(int i=0; i<K; i++) {
			for(int j=0; j<K; j++) {
				printf("into[%d][%d] = %d\n", i, j, into[i][j]);
			}
		}
		*/

		int max = stack(0);
		int indexMax = 0;
		for(int i=1; i<K; i++) {
			int aux = stack(i);
			if(aux>max) {
				max = aux;
				indexMax = i;
			}
		}
		printf("%d\n", max);
		
		printf("%d", indexMax+1);
		for(int i=1; i<max; i++) {
			indexMax = next[indexMax];
			printf(" %d", indexMax+1);
		}
		printf("\n");
	}
}

