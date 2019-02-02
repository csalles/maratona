#include <stdio.h>

//#define DEBUG

int target;
int adj[21][21], dg[21];
int visited[21];
long int countRoutes;

void DFSfromTarget(int v) {
	visited[v] = 1;
	if(v==1) return;
	for(int i=0; i<dg[v]; i++) {
		int u = adj[v][i];
		if(!visited[u]) {
			DFSfromTarget(u);
		}
	}
}

void initDFSfromTarget() {
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
		for(int i=0; i<dg[u]; i++) {
			int v = adj[u][i];
			if(visited[v] && !isInPath[v]) {
				DFS(v);
			}
		}

	}

	szPath--;
	isInPath[u] = 0;
}

void initDFS() {
	countRoutes = 0;
	szPath = 0;
	for(int i=0; i<21; i++) isInPath[i] = 0;
	DFS(1);
}

int main() {
	for(int casos=1; ;casos++) {
		if(scanf("%d", &target)==EOF)
			return 0;

		for(int i=0; i<21; i++)
			dg[i] = 0;

		while(1) {
			int u, v;
			scanf("%d%d", &u, &v);
			if(u==0&&v==0) break;
			adj[u][dg[u]++] = v;
			adj[v][dg[v]++] = u;
		}

		for(int i=1; i<21; i++) {
			for(int j=0; j<dg[i]; j++) {
				for(int k=j+1; k<dg[i]; k++) {
					if(adj[i][j]>adj[i][k]) {
						int aux = adj[i][j];
						adj[i][j] = adj[i][k];
						adj[i][k] = aux;
					}
				}
			}
		}

		printf("CASE %d:\n", casos);
		initDFSfromTarget();

#ifdef DEBUG
		for(int i=1; i<21; i++) printf("VISITED[%d] = %d\n", i, visited[i]);
#endif

		initDFS();
		printf("There are %ld routes from the firestation to streetcorner %d.\n", countRoutes, target);
	}
}