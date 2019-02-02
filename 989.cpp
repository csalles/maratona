#include <stdio.h>

int T;
int S[9][9];


void PRINT_SOLUTION() {
	for(int i=0; i<9; i++) {
		for(int j=0; j<9; j++) {
			printf("%d", S[i][j]);
		}
		printf("\n");
	}
}


int sudoku(int lin, int col) {
	int ok[10];
	int i, j;

//PRINT_SOLUTION();
//putchar('\n');

	if(lin>=9) return 1;

	if(S[lin][col]>0) {
		if(col==8) return sudoku(lin+1, 0);
		else return sudoku(lin, col+1);
	}
	
	//aqui so chega se S[lin][col] == 0

	//vetor ok inicialmente com todos ok
	for(i=1; i<=9; i++)
		ok[i]=1;
	//verificando a coluna col
	for(i=0; i<9; i++)
		if(S[i][col]>0) ok[ S[i][col] ] = 0;
	//verificando a linha lin
	for(j=0; j<9; j++)
		if(S[lin][j]>0) ok[ S[lin][j] ] = 0;
	//verificando a submatriz 3x3
	for(i=(lin/3)*3; i<(lin/3)*3+3; i++)
		for(j=(col/3)*3; j<(col/3)*3+3; j++)
			if(S[i][j]>0) ok[ S[i][j] ] = 0;

	//iterando sobre os ok, tentando todos
	for(i=1; i<=9; i++) {
		if(ok[i]) {
			S[lin][col] = i;
			if(col==8 && sudoku(lin+1, 0)) return 1;
			else if(col<8 && sudoku(lin, col+1)) return 1;
			S[lin][col] = 0;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		for(int i=0; i<9; i++) {
			char line[10];
			scanf("%s", line);
			for(int j=0; j<9; j++) {
				S[i][j] = line[j]-'0';
			}
		}

		//PRINT_SOLUTION();

		if(!sudoku(0,0))
			printf("NO SOLUTION\n");
		else
			PRINT_SOLUTION();

	}
}