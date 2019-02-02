//336
//A Node Too Far

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

#include <map>

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

// Complexidade: O(E + VlogV)
vector<int> Dijkstra(Graph &g, int origem) {
	vector<int> cost(g.v, INT_MAX);
	cost[origem] = 0;
	vector<bool> visited(g.v, false);

	priority_queue< pair<int,int>, vector<pair<int,int> >,
	                greater< pair<int,int> > > q;
	q.push( pair<int,int>(0, origem) );

	while(!q.empty()) {
		//escolher o working node
		pair<int,int> p = q.top(); //log(V)
		q.pop();
		int wNode = p.second;
		if(visited[wNode]) continue;

		/*
		int wNode = -1;
		for(int i=0; i<g.v; i++) {
			if(visited[i]) continue;
			if(wNode==-1||cost[i]<cost[wNode]) wNode=i;
		}
		if(wNode==-1)
			return cost;
		*/
		//iterar sobre os vizinhos
		for(int i=0; i<g.dg[wNode]; i++) {
			int v = g.adj[wNode][i];
			int w = g.weight[wNode][i];
			if(visited[v]) continue;
			if(cost[wNode] + w < cost[v]) {
				cost[v] = cost[wNode]+w;
				q.push( pair<int,int>(cost[v], v) );
			}
		}
		//visitar wNode
		visited[wNode] = true;
	}
	return cost;
}

// MST
// O(logV)
int disjointSet(vector<int>&ds, int n) {
	if( ds[n]==n )
		return n;
	else
		return ds[n] = disjointSet(ds, ds[n]);
}
//O(logV)
void disjointUnion(vector<int>&ds, int a, int b) {
	ds[ disjointSet(ds, a) ] = disjointSet(ds, b);
}

// Complexidade  O(E log E) = O(E log V)
int Kruskal(Graph &g, Graph &mst) {
	initGraph(mst, g.v);


	// O(E)
	vector< pair<int, pair<int,int> > >edges;
	for(int u=0; u<g.v; u++) {
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			int w = g.weight[u][i];
			if(u>v) continue;
			pair<int, pair<int,int> > p(w, pair<int,int>(u,v));
			edges.push_back(p);
		}
	}

	//ordenando as arestas O(E logE)
	sort(edges.begin(), edges.end());

	//todos com cores diferentes O(V)
	vector<int> ds(g.v);
	for(int i=0; i<g.v; i++) {
		ds[i] = i;
	}

	//iterando sobre as arestas ordenadas O(E + VlogV)
	int cont = 0;
	int sum = 0;
	for(int i=0; i<edges.size(); i++) { //O(E)
		int w = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		if( disjointSet(ds, u) != disjointSet(ds, v) ) {
			addEdge(mst, u, v, w);
			addEdge(mst, v, u, w);
			disjointUnion(ds, u, v);//log(V)
			/*
			int c = color[u];
			for(int j=0; j<g.v; j++) { // O(V)
				if(color[j]==c) {
					color[j] = color[v];
				}
			}
			*/
			cont++;
			sum += w;
			if(cont==g.v-1) break;
		} 
	}
	return sum;
}

//Complexidade do Prim: O(VlogV + E) = O(ElogV)
int Prim(Graph &g, Graph &mst, int origem=0) {
	vector<int> cost(g.v, INT_MAX); //O(V)
	cost[origem] = 0;
	vector<bool> visited(g.v, false); //O(V)

	priority_queue< pair<int,int>, vector<pair<int,int> >,
	                greater< pair<int,int> > > q;
	q.push( pair<int,int>(0, origem) );

	int sum = 0;
	while(!q.empty()) { //O(V)
		//escolher o working node
		pair<int,int> p = q.top(); //log(V)
		q.pop();
		int wNode = p.second;
		if(visited[wNode]) continue;

		/*
		int wNode = -1;
		for(int i=0; i<g.v; i++) {
			if(visited[i]) continue;
			if(wNode==-1||cost[i]<cost[wNode]) wNode=i;
		}
		if(wNode==-1)
			return cost;
		*/
		//iterar sobre os vizinhos ( somatorio eh O(E) )
		for(int i=0; i<g.dg[wNode]; i++) { 
			int v = g.adj[wNode][i];
			int w = g.weight[wNode][i];
			if(visited[v]) continue;
			if( w < cost[v]) {
				cost[v] = w;
				q.push( pair<int,int>(cost[v], v) );
			}
		}
		//visitar wNode
		visited[wNode] = true;
		sum += p.first;
	}
	return sum;	
}

//retorna quantos sao encontrados ate o ttl limite
int bfs_limitado(Graph &g, int s, int ttl) {
	//inicializando visited com false
	bool visited[MAXNODES];
	for(int i=0; i<g.v; i++)
		visited[i] = false;
	//criando fila com s
	queue< pair<int, int> > q;
	q.push(  pair<int,int>(s, 0) );
	visited[s] = true;

	int cont = 0;

	//laco principal
	while(!q.empty()) {
		pair<int,int> p = q.front();
		int u = p.first;
		int cost = p.second;
		q.pop();

		if(cost>ttl) break;
		cont++;

		//iterar os vizinhos de u
		for(int i=0; i<g.dg[u]; i++) {
			int v = g.adj[u][i];
			if(!visited[v]) {
				visited[v] = true;
				q.push( pair<int,int>(v, cost+1) );
			}
		}
	}
	return cont;
}


int main() {

	int nc;
	int countCases = 1;

	while(1) {
		cin >> nc;
		if(nc==0) break;

		Graph g;
		initGraph(g, 30);

		int nodes = 0;
		map<int, int> rotulos;
		for(int i=0; i<nc; i++) {
			int a, b;
			cin >> a >> b;
			if(rotulos.count(a)==0) rotulos[a] = nodes++;
			if(rotulos.count(b)==0) rotulos[b] = nodes++;
			addEdge(g, rotulos[a], rotulos[b]);
			addEdge(g, rotulos[b], rotulos[a]);
		}

		while(1) {
			int origem, ttl;
			cin >> origem >> ttl;
			if(!origem&&!ttl) break;

			int notReachable = nodes - bfs_limitado(g, rotulos[origem], ttl);
			cout << "Case " << countCases << ": " << notReachable 
			     << " nodes not reachable from node " << origem 
			     <<  " with TTL = " << ttl << "." << endl;
			countCases++;
		}



	}

}
