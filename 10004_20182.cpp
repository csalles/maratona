//10004

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAXNODES 200
#define MAXDEGREE 200

typedef struct
{
	int v, e;
	int dg[MAXNODES];
	int adj[MAXNODES][MAXDEGREE];
	int weight[MAXNODES][MAXDEGREE];
} Graph;

void initGraph(Graph &g, int v) {
	g.v = v;
	g.e = 0;
	for(int i=0; i<v; i++)
		g.dg[i] = 0;
}

void addEdge(Graph &g, int u, int v, int w=1) {
	g.adj[u][ g.dg[u] ] = v;
	g.weight[u][ g.dg[u] ] = w;
	g.dg[u]++;
}

bool hasEdge(Graph &g, int u, int v) {
	for(int i=0; i<g.dg[u]; i++) {
		if(g.adj[u][i]==v) return true;
	}
	return false;
}

void bfs(Graph &g, int s) {
	//inicializando visited com false
	bool visited[MAXNODES];
	for(int i=0; i<g.v; i++)
		visited[i] = false;
	//criando fila com s
	queue<int> q;
	q.push(s);
	visited[s] = true;
	//laco principal
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		//iterar os vizinhos de u
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			if(!visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}

}

void dfs(Graph &g, int s) {
	//inicializa visited com false
	bool visited[MAXNODES];
	for(int i=0; i<MAXNODES; i++)
		visited[i] = false;
	//inicializa uma pilha st com s
	stack<int> st;
	st.push(s);
	visited[s] = true;
	//laco principal
	while(!st.empty()) {
		int u = st.top();
		st.pop();
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			if(!visited[v]) {
				visited[v] = true;
				st.push(v);
			}
		}
	}
}

// g eh um grafo dirigido obrigatoriamente sem ciclos
vector<int> topSort(Graph &g) {
	vector<int> ret;//retorno da funcao
	vector<int> inDegree(g.v, 0); //inDegree
	//inicializo inDegree
	for(int u=0; u<g.v; u++) {
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			inDegree[v]++;
		}
	}
	//inicializo fila q com todos inDegree 0
	queue<int> q;
	for(int u=0; u<g.v; u++) {
		if(inDegree[u]==0)
			q.push(u);
	}
	//laco principal sobre a fila q
	while(!q.empty()) {
		int u = q.front();
		ret.push_back(u);
		q.pop();
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			inDegree[v]--;
			if(inDegree[v]==0) {
				q.push(v);
			}
		}
	}
	//retorna o vetor criado
	return ret;
}

bool bicoloring(Graph &g, int node, int color,
	vector<int> &vetColor ) 
{
	int otherColor = color==1 ? 2 : 1;
	if(vetColor[node]==0) {
		vetColor[node] = color;
		for(int i=0; i<g.dg[node]; i++) {
			int v = g.adj[node][i];
			if(!bicoloring(g,v,otherColor,vetColor)) {
				return false;
			}
		}
		return true;
	}
	else {
		return vetColor[node] == color;
	}
}

int main() {
	int n, m;

	while( 1 ) {
		cin >> n;
		if(!n) break;
		cin >> m;
		Graph g;
		initGraph(g, n);
		for(int i=0; i<m; i++) {
			int u, v;
			cin >> u >> v;
			addEdge(g, u, v);
			addEdge(g, v, u);
		}

		vector<int> vetColor(n,0);
		if( bicoloring(g, 0, 1, vetColor) ) {
			cout << "BICOLORABLE." << endl;
		}
		else {
			cout << "NOT BICOLORABLE." << endl;
		}
	}


}
/*
[0 -- {1 -- {2
 \--------/
*/
