#include <stdio.h>

#include <vector>
using namespace std;

int target;
int M[22][22];

vector< vector<int> > P[22];

/*
1---2
\     \
 \--3--4--5

5
1 2
1 3
2 4
3 4
4 5
0 0
6
1 2
1 3
3 4
3 5
4 6
5 6
2 3
2 4
0 0
4
2 3
3 4
5 1
1 6
7 8
8 9
2 5
5 7
3 1
1 8
4 6
6 9
0 0



target = 5

DFS(1, {1})
   DFS(2, {1,2})
      DFS(4, {1,2,4})
        DFS(3, {1,2,4,3})
        DFS(5, {1,2,4,5}) print(1, 2, 4, 5)
   DFS(3)
      DFS(4)
        DFS(2)
        DFS(5) print(1, 3, 4, 5)
*/

void DFS(int u) {
	
	if( P[u].size()!=0 ) return;

	if(target==u) {
		vector<int> path(1, u);
		P[u].push_back(path);
	}
	else {
		for(int v=1; v<=21; v++) {
			if( M[u][v] ) {
				M[u][v] = 0;
				DFS(v);
				for(int i=0; i<P[v].size(); i++) {
					vector<int> path = P[v][i];
					path.push_front(u);
					P[u].push_back(path);
				}
			}
		}
	}
}

int main() {
	int casos;
	int i, j;

	for(casos=1; ;casos++) {
		if(scanf("%d", &target)==EOF) return 0;
		
		printf("CASE %d:\n", casos);

		for(i=1; i<=21; i++)
		   for(j=1; j<=21; j++)
		      M[i][j] = 0;

		while(1) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(u==0&&v==0) break;
			M[u][v] = 1;
			M[v][u] = 1;
		}

		//entrada lida!

		for(i=1; i<=21; i++)
		   P[i].clear();

		DFS(1);

		int countRoutes = P[1].size();

		for(i=0; i<countRoutes; i++) {
			vector<int> path = P[1][i];
			printf("%d", path[0]);
			for(j=1; j<path.size(); j++)
				printf(" %d", path[j]);
			printf("\n");
		}

		printf("There are %d routes from the firestation to streetcorner %d.\n", countRoutes, target);
	}

}