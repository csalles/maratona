#include <stdio.h>

#define DEBUG

int target;
int M[21][21];
int visited[21];
long int countRoutes;

void DFSfromTarget(int v) {
	visited[v] = true;
	if(v==1) return;
	for(int i=1; i<21; i++) {
		if(M[v][i] && !visited[i]) {
			DFSfromTarget(i);
		}
	}
}

void initDFS() {
	for(int i=0; i<21; i++) visited[i]=0;
	DFSfromTarget(target);
}

int path[21], szPath;
int isInPath[21];

void DFS(int u) {
	path[szPath++] = u;
	isInPath[u] = 1;

	if(u==target) {
		printf("%d", path[0]);
		for(int i=1; i<szPath; i++) printf(" %d", path[i]);
		printf("\n");
		countRoutes++;
	}
	else {
		for(int v=1; v<21; v++) {
			if(M[u][v] && visited[v] && !isInPath[v]) {
				DFS(v);
			}
		}

	}

	szPath--;
	isInPath[u] = 0;
}

int main() {
	for(int casos=1; ;casos++) {
		if(scanf("%d", &target)==EOF)
			return 0;

		for(int i=0; i<21; i++)
			for(int j=0; j<21; j++)
				M[i][j] = 0;

		while(1) {
			int u, v;
			scanf("%d%d", &u, &v);
			if(u==0&&v==0) break;
			M[u][v] = 1;
			M[v][u] = 1;
		}

		countRoutes = 0;
		printf("CASE %d:\n", casos);
		DFSfromTarget(target);

#ifdef DEBUG
		for(int i=1; i<21; i++) printf("VISITED[%d] = %d\n", i, visited[i]);
#endif


		for(int i=0; i<21; i++) isInPath[i] = 0;
		DFS(1);
		printf("There are %ld routes from the firestation to streetcorner %d.\n", countRoutes, target);
	}
}