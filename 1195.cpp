//1195 Árvore Binária de Busca

#include <iostream>
#include <cstdio>

using namespace std;

int info[501], leftNode[501], rightNode[501];

void insert(int index) {
	int node = 0;
	while(1) {
		if(info[index]<info[node]) {
			if(leftNode[node]==-1) {
				leftNode[node] = index;
				return;
			}
			else {
				node = leftNode[node];
			}
		}
		if(info[index]>info[node]) {
			if(rightNode[node]==-1) {
				rightNode[node] = index;
				return;
			}
			else {
				node = rightNode[node];
			}
		}
	}
}

#define PREFIXO 1
#define POSFIXO 2
#define INFIXO 3
void passeio(int index, int tipo) {
	if(index!=-1) {
		if(tipo==PREFIXO) cout << " " << info[index];
		passeio(leftNode[index], tipo);
		if(tipo==INFIXO) cout << " " << info[index];
		passeio(rightNode[index], tipo);
		if(tipo==POSFIXO) cout << " " << info[index];
	}
}

int main() {
	int c;
	cin >> c;

	for(int caseCount=1; caseCount<=c; caseCount++) {
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			leftNode[i] = rightNode[i] = -1;
			cin >> info[i];
			if(i>0) insert(i);
		}


		cout << "Case " << caseCount << ":" << endl;
		cout << "Pre.:";
		passeio(0, PREFIXO);
		cout << endl;
		cout << "In..:";
		passeio(0, INFIXO);
		cout << endl;
		cout << "Post:";
		passeio(0, POSFIXO);
		cout << endl;
		cout << endl;
	}

}
