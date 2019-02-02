//1592 Elias e Golias

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

#define MAXNODES 1001
#define MAXDEGREE 1001

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

void addEdge(Graph &g, int u, int v, int w) {
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


int main_mice() {
/*
	int v, e;
	cin >> v >> e;
	Graph g;
	initGraph(g, v);

	for(int i=0; i<e; i++) {
		int origem, dest, peso;
		string strOrigem, strDest;
		cin >> strOrigem >> strDest >> peso;
		origem = strOrigem[0]-'A';
		dest = strDest[0]-'A';
		addEdge(g, origem, dest, peso);
		addEdge(g, dest, origem, peso);	
	}

	vector<int> vet = Dijkstra(g, 0);

	for(int i=0; i<vet.size(); i++) {
		cout << "cost[" << (char)('A'+i) << "] = " << vet[i] << endl;
	}
*/

	int t;
	cin >> t;

	while(t--) {

		int v, ext, tempo;
		cin >> v >> ext >> tempo;

		Graph g;
		initGraph(g, v);


		int passages;
		cin >> passages;

		while(passages--) {
			int origem, destino, custo;
			cin >> destino >> origem >> custo;
			addEdge(g, origem, destino, custo);
		}

		vector<int> cost = Dijkstra(g, ext);

		int mice = 0;
		for(int i=0; i<v; i++) {
			if(cost[i]<=tempo) mice++;
		}
		cout << mice << endl;
		if(t) cout << endl; 
	}
	return 0;
}
/*
[0 -- {1 -- {2
 \--------/
*/


// Complexidade: O(E + VlogV)
int DijkstraModif(Graph &g, int origem, int dst, int k) {
	vector< vector<int> > cost(k+1);
	for(int i=0; i<=k; i++) cost[i] = vector<int> (g.v, INT_MAX);
	
	cost[1][origem] = 0;

	vector< vector<bool> > visited(k+1);
	for(int i=0; i<=k; i++) visited[i] = vector<bool>(g.v, false);

	vector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = origem;
	priority_queue< vector<int>, vector< vector<int> >,
	                greater< vector<int> > > q;
	q.push( v );

	while(!q.empty()) {
		//escolher o working node
		vector<int> p = q.top(); //log(V)
		q.pop();
		int wCost = p[0];
		int wSize = p[1]; 
		int wNode = p[2];

		if(wNode==dst) return wCost;

		if(visited[wSize][wNode]) continue;

		/*
		int wNode = -1;
		for(int i=0; i<g.v; i++) {
			if(visited[i]) continue;
			if(wNode==-1||cost[i]<cost[wNode]) wNode=i;
		}
		if(wNode==-1)
			return cost;
		*/

		if(wSize>=k) continue;

		//iterar sobre os vizinhos
		for(int i=0; i<g.dg[wNode]; i++) {
			int v = g.adj[wNode][i];
			int w = g.weight[wNode][i];

			if(visited[wSize+1][v]) continue;
			if(wCost + w < cost[wSize+1][v]) {
				cost[wSize+1][v] = wCost + w;
				vector<int> vv(3);
				vv[0] = cost[wSize+1][v]; vv[1] = wSize+1; vv[2] = v;
				q.push( vv );
			}
		}
		//visitar wNode
		visited[wSize][wNode] = true;
	}
	return -1;
}

int main() {
	int t;
	cin >> t;

	while(t--) {
		int n, m, k;
		cin >> n >> m >> k;

		Graph g;
		initGraph(g, n);


		map< pair<int,int>, int > minCost;
		for(int i=0; i<m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			if(u!=v) {
				pair<int,int> p(u, v);
				if(minCost.count(p)==0) minCost[p] = w;
				else minCost[p] = min(minCost[p], w);
			}
		}

		for( map< pair<int,int>, int >::iterator it = minCost.begin(); it!=minCost.end(); it++) {
			addEdge(g, it->first.first, it->first.second, it->second);
		}

		cout << DijkstraModif(g, 0, n-1, k) << endl;

	}

}