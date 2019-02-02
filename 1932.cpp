//1932 Bolsa de Valores

#include <iostream>
#include <algorithm>
using namespace std;

/*
int n, c;
long int compra[100010], venda[1001][100010], v[100010];

long int Fvenda(int valCompra, int index);

long int Fcompra(int index) {
	if(index>=n) return 0;
	if(compra[index]!=-1) return compra[index];
	long int lucro = max( Fcompra(index+1), Fvenda(v[index], index+1) );
	return compra[index] = lucro<0 ? 0 : lucro;
}

long int Fvenda(int valCompra, int index) {
	if(index>=n) return 0;
	if(venda[valCompra][index]!=-1) return venda[valCompra][index];
	long int lucro = Fvenda(valCompra, index+1);
	if( v[index] - valCompra - c > 0 ) {
		lucro = max( lucro, v[index] - valCompra - c + Fcompra(index+1) );
	}
	else {
		lucro = max( lucro, Fcompra(index+1) );
	}
	return venda[valCompra][index] = lucro<0 ? 0 : lucro;
}

int main() {
	cin >> n >> c;

	for(int i=0; i<n; i++) {
		cin >> v[i];
		compra[i] = -1;
		for(int j=0; j<1001; j++) venda[j][i]=-1;
	}

	for(int i=n-1; i>=0; i--) Fcompra(i);

	cout << Fcompra(0) << endl;
}
*/

#include <stdio.h>

int kadane(int cot[], int N, int C)
{
	int max_atual, max_final, max_lucro = 0;

	max_atual = max_final = cot[0];

	for(int i = 1; i < N; i++)
	{
		if((max_atual > cot[i] && (max_atual - cot[i] >= C))
				|| cot[i] < max_final)
		{
			if(max_atual - max_final - C > 0)
				max_lucro += max_atual - max_final - C;
			max_atual = max_final = cot[i]; 
		}
		if(cot[i] > max_atual)
			max_atual = cot[i];
	}
	
	if(max_atual - max_final - C > 0)
		max_lucro += max_atual - max_final - C; 

	return max_lucro;
}

int main(int argc, char *argv[])
{
	int N, C;

	scanf("%d %d", &N, &C);

	int cot[N];

	for(int i = 0; i < N; i++)
		scanf("%d", &cot[i]);

	printf("%d\n", kadane(cot, N, C));

	return 0;
}
