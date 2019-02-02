
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <limits.h>

#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXV 751

#define __DEBUG__

typedef struct {
	int V, E;
	int dg[MAXV];
	int **adj;//[MAXV][MAXV];
	double **weight; //[MAXV][MAXV];
} Graph;

void initGraph(Graph *g, int v) {
	g->V = v;
	g->E = 0;
	g->adj = (int**)malloc((v+1)*sizeof(int*));
	g->weight = (double**) malloc( (v+1)*sizeof(double*));
	for(int i=0; i<v+1; i++) {
		g->dg[i] = 0;
		g->adj[i] = (int*)malloc(2*(v+1)*sizeof(int));
		g->weight[i] = (double*)malloc(2*(v+1)*sizeof(double));
	}
}

void freeGraph(Graph *g) {
	for(int i=0; i<g->V; i++) {
		free(g->adj[i]);
		free(g->weight[i]);
	}
	free(g->adj);
	free(g->weight);
	g->adj = NULL;
	g->weight = NULL;
}

void addEdge(Graph *g, int u, int v, double w=1) {
	g->E++;
	g->adj[u][ g->dg[u] ] = v;
	g->weight[u][ g->dg[u] ] = w;
	g->dg[u]++;
}

void bfs(Graph *g, int node) {
	queue<int> q;
	int visited[MAXV];
	for(int i=0; i<MAXV; i++) {
		visited[i] = 0;
	}
	q.push(node);
	visited[node] = 1;

	while(!q.empty()) {
		int w = q.front();
		q.pop();
		#ifdef __DEBUG__
		printf("BFS(%d)\n", w);
		#endif
		for(int i=0; i<g->dg[w]; i++) {
			int v = g->adj[w][i];
			if(!visited[v]) {
				visited[v] = 1;
				q.push(v);
			}
		}
	}
}

void dfs_visit(Graph *g, int visited[MAXV], int node) {
	#ifdef __DEBUG__
	printf("DFS(%d)\n", node);
	#endif

	visited[node] = 1;
	for(int i=0; i<(g->dg[node]); i++) {
		int v = g->adj[node][i];
		if(!visited[v])
			dfs_visit(g, visited, v);
	}
}

void dfs(Graph *g, int node) {
	int visited[MAXV];
	for(int i=0; i<MAXV; i++) {
		visited[i] = 0;
	}
	dfs_visit(g, visited, node);
}

void dijkstra(Graph *g, int node, int cost[MAXV]) {
	int visited[MAXV];
	for(int i=0; i<MAXV; i++) {
		cost[i] = INT_MAX;
		visited[i] = 0;
	}
	cost[node] = 0;

	priority_queue< pair<int,int>, 
					vector< pair<int,int> >, 
					greater< pair<int,int> > >
				q;
	q.push( pair<int,int>(0, node) );

	while(!q.empty()) {
		//escolhe node de trabalho w
		/*int w = -1;
		for(int i=1; i<=g->V; i++) {
			if(!visited[i]) {
				if(w==-1)
					w = i;
				else if(cost[i]<cost[w])
					w = i;
			}
		}
		if(w==-1) break;*/

		pair<int,int> p = q.top();
		q.pop();
		int w = p.second;
		if(visited[w]) continue;

		visited[w] = 1;
		for(int i=0; i<g->dg[w]; i++) {
			int v = g->adj[w][i];
			int weightEdge = g->weight[w][i];
			if(cost[w]+weightEdge<cost[v]) {
				cost[v] = cost[w]+weightEdge;
				q.push(pair<int,int>(cost[v], v));
			}
		}

	}

}

//Prim & Kruskal

int dj_set(int *color, int s1) {
	if(color[s1]==s1)
		return s1;
	else
		return color[s1] = dj_set(color, color[s1]);
}

void dj_union(int *color, 
			 int s1, int s2) {
	color[ dj_set(color, s1) ] =
	    dj_set(color, s2);
}

double kruskal(Graph *g, Graph *out) {
	initGraph(out, g->V);
	double sum = 0;

	vector< vector<double> > edges(g->E);
	int contEdge = 0;
	for(int u=1; u<=g->V; u++) {
		for(int i=0; i<g->dg[u]; i++) {
			int v = g->adj[u][i];
			double w = g->weight[u][i];
			vector<double> edge(3);
			edge[0] = w;
			edge[1] = (double)u;
			edge[2] = (double)v;
			edges[contEdge++]=edge;
		}
	}
	sort(edges.begin(), edges.end());

	int color[MAXV];
	for(int i=0; i<MAXV; i++)
		color[i] = i;

	for(int i=0; i<g->E; i++) {
#ifdef __DEBUG__
		printf("Aresta de %d para %d com custo %.2lf\n", (int)edges[i][1], (int)edges[i][2], edges[i][0]); 
#endif

		int u, v;
		double w;
		w = edges[i][0];
		u = (int)edges[i][1];
		v = (int)edges[i][2];

		if(dj_set(color, u)!=dj_set(color,v)) {
#ifdef __DEBUG__
			printf("Adiciona na solucao!\n");
			printf("ANTES %d %d %d %d %d\n", color[1], color[2], color[3], color[4], color[5]);
#endif
			addEdge(out, u, v, w);
			addEdge(out, v, u, w);
			sum += w;
			/*
			int toChange = color[u];
			for(int k=0; k<MAXV; k++) {
				if(color[k] == toChange)
					color[k] = color[v];
			}
			*/
			dj_union(color, u, v);
#ifdef __DEBUG__
			printf("DPOIS %d %d %d %d %d\n", color[1], color[2], color[3], color[4], color[5]);
#endif
			if(out->E == 2*(g->V-1) ) break;
		}


	}

	return sum;
}

double dist(int x1, int y1, int x2, int y2) {
	double dx = (double)(x1-x2);
	double dy = (double)(y1-y2);
	return sqrt(dx*dx+dy*dy);
}

int main() {

	Graph g;
	int v;

	int X[MAXV], Y[MAXV];

	while(scanf("%d", &v)!=EOF) {
		initGraph(&g, v);
		for(int i=0; i<v; i++) {
			scanf("%d%d", &X[i], &Y[i]);
		}
		
		for(int i=0; i<v; i++) {
			for(int j=i+1; j<v; j++) {
				double d = dist(X[i], Y[i], X[j], Y[j]);
				addEdge(&g, i+1, j+1, d);
				addEdge(&g, j+1, i+1, d);
			}
		}
		
		int zeroes;
		scanf("%d", &zeroes);
		while(zeroes--) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(&g, u, v, 0.0);
			addEdge(&g, v, u, 0.0);
		}
		Graph out;
		printf("%.2lf\n", kruskal(&g, &out) );
		freeGraph(&g);
		freeGraph(&out);
	}
}

