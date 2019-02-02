
#include <iostream>
#include <vector>
using namespace std;

int memo[52][52];

int cut(vector<int>&v, int esq, int dir) {

	if(esq+1>=dir) return 0;

	if(memo[esq][dir]!=-1)
		return memo[esq][dir];

	int cost = v[dir] - v[esq];
	//cout << "cost " << cost << endl;
	int min = -1;
	for(int i=esq+1; i<=dir-1; i++) {
		int aux = cut(v,esq,i) + cut(v,i,dir) + cost;
		if(min==-1) min = aux;
		else if(aux<min) min = aux;
	}
	return memo[esq][dir] = min;
}

int main() {
	int l, n;

	while(1) {
		cin >> l;
		if(!l) break;

		cin >> n;
		vector<int> v(n+2);

		v[0] = 0;
		v[n+1] = l;
		for(int i=1; i<=n; i++)
			cin >> v[i];

		for(int i=0; i<=n+1; i++)
			for(int j=0; j<=n+1; j++)
				memo[i][j] = -1;

		cout << "The minimum cutting is " 
		     << cut(v, 0 , n+1) 
		     << "." << endl;

	}

}
