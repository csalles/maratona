//2687

#include <iostream>
using namespace std;

int q, l;
int m[15][15];
bool visited[15][15];

int flood(int lin, int col) {
	int c = 0;
	if(m[lin][col]==1 || visited[lin][col])
		return 0;
	visited[lin][col] = true;

	if(lin>0) c+=flood(lin-1, col);
	if(lin<l-1) c+=flood(lin+1, col);
	if(col>0) c+=flood(lin, col-1);
	if(col<l-1) c+=flood(lin, col+1);
	return c+1;
}


int main() {
	int i, j;

	cin >> q;
	while(q--) {
		cin >> l;

		for(i=0; i<l; i++) {
			for(j=0; j<l; j++) {
				cin >> m[i][j];
				visited[i][j] = false;
			}
		}

		int cont = l*l;

		for(i=0; i<l; i++) {
			cont -= flood(i, 0);
			cont -= flood(i, l-1);
			cont -= flood(0, i);
			cont -= flood(l-1, i);
		}

		if(cont%2==0)
			printf("%d.00\n", cont/2);
		else
			printf("%d.50\n", cont/2);

	}

}