#include <stdio.h>

//leiam a entrada

typedef struct {
	int x,y,z;
} block;

int index;
int n;
block v[181];

void addBlock(int x, int y, int z) {
	v[index].x = x;
	v[index].y = y;
	v[index].z = z;
	index++;
}

int memo[181];

int maxTower(int i) {
	int best = v[i].z;
	if(memo[i]!=-1) return memo[i];
	for(int j=0; j<index; j++) {
		if(v[j].x<v[i].x && v[j].y<v[i].y) {
			int aux = maxTower(j) + v[i].z;
			if(aux>best) best=aux;
		}
	}
	memo[i] = best;
	return best;
}

int main() {
	for(int caso=1; ;caso++) {
		scanf("%d", &n);
		if(!n) break;
		index = 0;
		for(int i=0; i<n; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			addBlock(x,y,z);
			addBlock(x,z,y);
			addBlock(y,x,z);
			addBlock(y,z,x);
			addBlock(z,x,y);
			addBlock(z,y,x);
		}
		for(int i=0; i<index; i++) {
			memo[i]=-1;
		}

		int best = maxTower(0);
		for(int i=1; i<index; i++) {
			int aux = maxTower(i);
			if(aux>best) best=aux;
		}
		printf("Case %d: maximum height = %d\n", caso, best);
	}
}