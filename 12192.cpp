//12192

#include <iostream>
using namespace std;

#define INTO(n,a,b) ((n)>=(a) && (n)<=(b))

//#define _DEBUG_bsearchLine_
//#define _DEBUG_bsearchDiagonal_
//#define _DEBUG_main_

// binary search the index of the first element in line lin up to lastOfColun
// of the matriz mat in the interval [stInterval,endInterval]
int bsearchLine(int mat[501][501], int szCol, int lin, int stInterval, int endInterval) {
	int ini = 0;
	int fim = szCol-1;

#ifdef _DEBUG_bsearchLine_
cout << "bsearch lin " << lin << endl;
#endif

	while(ini<=fim) {
		int meio = (ini+fim)/2;

#ifdef _DEBUG_bsearchLine_
		//cout << "meio = " << meio << endl;
#endif
		if( (mat[lin][meio]>=stInterval && mat[lin][meio]<=endInterval) //in interval
			&& (meio==0 || mat[lin][meio-1]<stInterval) //previous not in interval
		) {
			return meio;
		}
		else if( mat[lin][meio] < stInterval ) {
			ini = meio+1;
		}
		else {
			fim = meio-1;
		}
	}
	return -1; //did not find any
}

// binary search the size of the diagonal 
// of the matriz mat in the interval [stInterval,endInterval]
// it starts in [lin][col] and keep searching the diagonal
int bsearchDiagonal(int mat[501][501], int szLin, int szCol, int lin, int col, 
	           int stInterval, int endInterval, int out) {
	int ini = out;
	int fim;

	//important: mat[lin][col] is in the interval [stInterval][endInterval]

	fim = szLin-1 - lin;
	if(szCol-1 - col < fim) fim = szCol-1 - col;

	int limFim = fim;

#ifdef _DEBUG_bsearchDiagonal_
	cout << "bsearchDiagonal lin=" << lin << " col=" << col << " fim=" << fim << endl;
#endif
	while(ini<=fim) {
		int meio = (ini+fim)/2;
		int elem = mat[lin+meio][col+meio];

#ifdef _DEBUG_bsearchDiagonal_
		cout << "meio=" << meio << " elem=" << elem << endl;
#endif
		if( (elem>=stInterval && elem<=endInterval) //elem in interval
			&& (meio==limFim || mat[lin+meio+1][col+meio+1]>endInterval) //previous not in interval
		) {
			return meio+1;
		}
		else if( elem > endInterval ) {
			fim = meio-1;
		}
		else {
			ini = meio+1;
		}
	}
	return -1; //did not find any
}



int main() {
	int n, m;

	int mat[501][501];

	while(1) {
		cin >> n >> m;
		if(!n&&!m) break;

		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				cin >> mat[i][j];

#ifdef _DEBUG_main_
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++)
				cout << mat[i][j] << " ";
			cout << endl;
		}
#endif

		int q;
		cin >> q;

		while(q--) {
			int stInterval, endInterval;
			cin >> stInterval >> endInterval;

#ifdef _DEBUG_main_
			cout << "looking " << stInterval << " | " << endInterval << endl;
#endif

			//int ini, fim, meio;

			int out = 0;

			for(int i=0; i<n; i++) {
				if(i+out>n-1) break;
				int col = bsearchLine(mat, m, i, stInterval, endInterval);
#ifdef _DEBUG_main_
				cout << "lin " << i << " col = " << col << endl;
#endif

				if(col!=-1) {
					if(col+out>m-1) continue;
					int size = bsearchDiagonal(mat, n, m, i, col, stInterval, endInterval, out);
					
#ifdef _DEBUG_main_
					cout << "size = " << size << endl;
#endif
					if(size>out) out = size;
				}
			}
			cout << out << endl;
		}
		cout << "-" << endl;
	}

}