#include <stdio.h>

#include <vector>
using namespace std;

int target;
int M[22][22];

vector< vector<int> > P[21];
/*

           /-----7----\
           /-----6----8
1 --- 2----4-----5----/
 \--- 3----/

4 
{4 7 8}
{4 6 8}
{4 5 8}


1, 2, 4, 7, 8

1 = [ {1, 2, 4, 7, 8} ]
2 = [ {2,4,7,8} ]
4 = [ {4,7,8} ]
7 = [ {7,8} ]
8 = [ {8} ]

1, 2, 4, 6, 8

1 = [ {1, 2, 4, 7, 8}, {1, 2, 4, 6, 8} ]
2 = [ {2,4,7,8} , {2, 4, 6, 8} ]
4 = [ {4,7,8}, {4, 6, 8} ]
6 = [ {6,8} ]
7 = [ {7,8} ]
8 = [ {8} ]


4 = [ ]

1---2
\     \
 \--3--4--5

  ---7<----
1  \---8<---9
    6<----

9 {9}
7 {7,9}
8 {8,9}
6 {6,9}

1 7 8 9
1 8 7 9
1 7 9
1 8 9


5 [ {5} ]
4 [ {4,5} ]
2 [ {2,4,5} ]
3 [ {3,4,5} ]
1 [ {1,2,4,5}, {1,3,4,5} ]



5
1 2
1 3
2 4
3 4
4 5
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
int path[21], isInPath[22];
int sizePath, countRoutes;

int add(int u, vector<int> p) {
	P[u].push_back(p);
}

vector< vector<int> > DFS(int u) {
	
	path[sizePath++] = u;
	isInPath[u] = 1;

	if(target==u) {
		
/*
		printf("%d", path[0]);
		for(int i=1; i<sizePath; i++)
			printf(" %d", path[i]);
		printf("\n");
*/
		vector<int> p(sizePath);
		for(int i=0; i<sizePath; i++)
			p[i] = path[i];

		P[target].push_back(p);

		countRoutes++;
	}
	else {
		for(int v=1; v<=21; v++) {
			if(M[u][v] && !isInPath[v]) {
				M[u][v] = 0;
				M[v][u] = 0;
				DFS(v);
			}
		}
	}

	isInPath[ path[--sizePath] ] = 0;
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

		sizePath = 0;
		countRoutes = 0;
		for(i=1; i<=21; i++) isInPath[i] = 0;

		DFS(1);

		for(i=0; i<countRoutes; i++) {
			printf("%d", P[target][i][0]);
			for(j=1; j<P[target][i].size(); j++){
				printf(" %d", P[target][i][j]);
			}
			printf("\n");
		}

		printf("There are %d routes from the firestation to streetcorner %d.\n", countRoutes, target);
	}

}