#include <stdio.h>
#include <limits.h>

int N;
int mat[76][76];

int left(int lin, int col, int k);
int right(int lin, int col, int k);

int memo[76][76][5];

int dp(int lin, int col, int k) {
	if(mat[lin][col]<0) {
		if(k==0) return INT_MIN;
		k--;
	}
	int best = INT_MIN;

	int aux = dp(lin+1, col, k);
	if(aux!=INT_MIN) {
	 	aux += mat[lin][col];
		if(aux>best) best = aux;
	}

	int copyK = k;
	int cost = mat[lin][col];
	for(int i=col-1; i>=0; i--) {
		if(mat[lin][col]<0) {
			copyK--;
			if(copyK<0) break;
		}
		cost += mat[lin][i];
		int aux = dp(lin+1, col, copyK);
		if(aux!=INT_MIN) {
			aux += cost;
			if(aux>best) best = aux;
		}
	}
	copyK = k;
	for(int i=col+1; i<N; i++) {
		if(mat[lin][col]<0) {
			copyK--;
			if(copyK<0) break;
		}
		cost += mat[lin][i];
		int aux = dp(lin+1, col, copyK);
		if(aux!=INT_MIN) {
			aux += cost;
			if(aux>best) best = aux;
		}
	}

	return best;
}

int left(int lin, int col, int k) {
	int best = mat[lin][col];

	if(mat[lin][col]<0) {
		if(k==0) return -10000000;
		k--;
	}

	if(col>0) {
		int aux = left(lin, col-1, k) + mat[lin][col];
		if(aux>best) best = aux;
	}
	if(lin<N-1) {
		int aux = left(lin+1, col, k) + mat[lin][col];
		if(aux>best) best = aux;
		aux = right(lin+1, col, k) + mat[lin][col];
		if(aux>best) best = aux;
	}
	return best;
}

int right(int lin, int col, int k) {
	int best = -10000000;

	if(mat[lin][col]<0) {
		if(k==0) return -10000000;
		k--;
	}

	if(col<N-1) {
		int aux = right(lin, col+1, k) + mat[lin][col];
		if(aux>best) best = aux;
	}
	if(lin<N-1) {
		int aux = left(lin+1, col, k) + mat[lin][col];
		if(aux>best) best = aux;
		aux = right(lin+1, col, k) + mat[lin][col];
		if(aux>best) best = aux;
	}
	return best;
}

int main() {
	int k;
	for(int caso=1;;caso++) {
		scanf("%d%d", &N, &k);
		if(!N&&!k) break;

		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				scanf("%d", &mat[i][j]);

		int out = right(0,0,k);
		if(out<=-10000000)
			printf("Case %d: impossible\n",caso);
		else
			printf("Case %d: %d\n",caso, out);
	}	
}

