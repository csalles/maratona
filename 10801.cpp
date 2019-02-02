
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


#include <stdio.h>

#include <limits.h>

#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXV 602

#define __DEBUG__

typedef struct {
	int V, E;
	int dg[MAXV];
	int adj[MAXV][MAXV], weight[MAXV][MAXV];
} Graph;

void initGraph(Graph *g, int v) {
	g->V = v;
	g->E = 0;
	for(int i=0; i<MAXV; i++)
		g->dg[i] = 0;
}

void addEdge(Graph *g, int u, int v, int w=1) {
	g->E++;
	g->adj[u][ g->dg[u] ] = v;
	g->weight[u][ g->dg[u] ] = w;
	g->dg[u]++;

	/*
	cout << "Creating edge:	" << 
	        "[ele=" << u/100 << "/floor=" << u%100 << "] to " << 
	        "[ele=" << v/100 << "/floor=" << v%100 << "] cost=" << w << endl;
	*/
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

//modificando o dijkstra para devolver true ou false se visitou o target
bool dijkstra(Graph *g, int node, int cost[MAXV], int target) {
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
	return visited[target];
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

int kruskal(Graph *g, Graph *out) {
	initGraph(out, g->V);
	int sum = 0;

	vector< vector<int> > edges(g->E);
	int contEdge = 0;
	for(int u=1; u<=g->V; u++) {
		for(int i=0; i<g->dg[u]; i++) {
			int v = g->adj[u][i];
			int w = g->weight[u][i];
			vector<int> edge(3);
			edge[0] = w;
			edge[1] = u;
			edge[2] = v;
			edges[contEdge++]=edge;
		}
	}
	sort(edges.begin(), edges.end());

	int color[MAXV];
	for(int i=0; i<MAXV; i++)
		color[i] = i;

	for(int i=0; i<g->E; i++) {
#ifdef __DEBUG__
		printf("Aresta de %d para %d com custo %d\n", edges[i][1], edges[i][2], edges[i][0]); 
#endif

		int u, v, w;
		w = edges[i][0];
		u = edges[i][1];
		v = edges[i][2];

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

int main() {
	int n, target;
	int T[5];
	string line;

	while(getline(cin, line)) {
		vector<int> floors[5];
		stringstream stream1(line);
		stream1 >> n >> target;
		//reading elevetors time
		getline(cin, line);
		stringstream stream2(line);
		for(int i=0; i<n; i++)
			stream2 >> T[i];

		//reading elevators floors
		for(int i=0; i<n; i++) {
			getline(cin, line);
			stringstream stream(line);
			while(1) {
				int f;
				stream >> f;
				if(!stream) break;
				floors[i].push_back(f);
			}
		}

		/*
		cout << "Tempos T dos elevadores" << endl;
		for(int i=0; i<n; i++) {
			cout << "T[" << i << "] = " << T[i] << endl;
		}
		cout << "Andares dos elevadores" << endl;
		for(int i=0; i<n; i++) {
			for(int j=0; j<floors[i].size(); j++)
				cout << floors[i][j] << " ";
			cout << endl;
		}
		*/

		Graph g;
		initGraph(&g, 601);

		for(int i=0; i<n; i++) {
			for(int j=0; j+1<floors[i].size(); j++) {
				int u = 100*i + floors[i][j];
				int v = 100*i + floors[i][j+1];
				addEdge(&g, u, v, (v-u)*T[i]);
				addEdge(&g, v, u, (v-u)*T[i]);
			}
		}

		for(int i=0; i<n; i++) { //for each elevator i
			for(int j=i+1; j<n; j++) { // for each other elevator j
				for(int fl=0; fl<100; fl++) { //for each floor fl
					bool hasFloor = false; //has floor fl in elevator i ?
					for(int k=0; k<floors[i].size(); k++) {
						if(floors[i][k]==fl) {
							hasFloor=true; 
							break;
						}
					}
					if(!hasFloor) continue; //if we do not have floor fl in elevator i, continue
					hasFloor = false; //reset flag as we know there is floor fl at this point in elevator i
					for(int k=0; k<floors[j].size(); k++) { //has floor fl in elevator j?
						if(floors[j][k]==fl) {
							hasFloor=true; 
							break;
						}
					}
					//switch elevators
					if(hasFloor) { //both elevators i and j have floor fl, so create edge of 60s
						int u = 100*i + fl;
						int v = 100*j + fl;
						addEdge(&g, u, v, 60);
						addEdge(&g, v, u, 60);
					}
				}
			}
		}

		// creating edge from differet target floors to floor 600
		for(int i=0; i<n; i++) {
			addEdge(&g, 100*i+target, 600, 0);
/*
			bool hasFloor = false; //has target floor k in elevator i ?
			for(int j=0; j<floors[i].size(); j++) {
				if(floors[i][j]==target) {
					
					break;
				}
			}
*/
		}

		for(int i=0; i<n; i++) 
			addEdge(&g, 601, 100*i, 0);
		

		int cost[MAXV];
		bool possible = dijkstra(&g, 601, cost, 600);

		if(!possible) cout << "IMPOSSIBLE" << endl;
		else cout << cost[600] << endl;

	}

}