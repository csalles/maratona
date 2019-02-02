//10003
#include <iostream>
#include <vector>
using namespace std;

int cont[53][53];
int memo[53][53];

int cut(vector<int> &v, int esq, int dir) {
	if(esq+1>=dir) return 0;

	if(memo[esq][dir]!=-1)
		return memo[esq][dir];

	/*
	cont[esq][dir]++;
	cout << "cut(" << esq << ", " << dir << ") = " 
	     << cont[esq][dir] << endl;
	*/

	int cost = v[dir] - v[esq];
	int menor = cost + cut(v,esq, esq+1) + cut(v,esq+1,dir);
	for(int i=esq+2; i<=dir-1; i++) {
		int aux = cost + cut(v,esq,i) + cut(v,i,dir);
		if(aux<menor) menor=aux;
	}
	return memo[esq][dir] = menor;
}

int main() {
	while(1) {
		int l;
		cin >> l;
		if(!l) break;
		
		int n;
		cin >> n;
		vector<int> v(n+2);
		for(int i=1; i<=n; i++)
			cin >> v[i];
		v[0] = 0;
		v[n+1] = l;

		for(int i=0; i<n+2; i++)
			for(int j=0; j<n+2; j++)
				memo[i][j] = -1;

		cout << "The minimum cutting is " 
			 << cut(v, 0, n+1) << "." << endl;

	}
}