//1034 Festival de Estátuas de Gelo

#include <cstdio>
#include <cstring>

int memo[1000001];
int v[25];
int n, m;
int t;

int pd(int target) {
	if(memo[target]!=-1) return memo[target];
	int min = -1;
	for(int i=0; i<n; i++) {
		if(v[i]<=target) {
			int atual = pd(target-v[i])+1;
			if(min==-1) min=atual;
			else if(atual<min) min=atual;
		}
	}
	return memo[target] = min;
}

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);

		memset(memo, -1, sizeof(int)*(m+1));
		memo[0] = 0;
		memo[1] = 1;

		for(int i=0; i<n; i++) {
			scanf("%d", &v[i]);
		}
		printf("%d\n", pd(m));

	}
	
}

