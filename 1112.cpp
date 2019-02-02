#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
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


int main() {
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
		initGraph(g, v+1);


		int passages;
		cin >> passages;

		while(passages--) {
			int origem, destino, custo;
			cin >> destino >> origem >> custo;
			addEdge(g, origem, destino, custo);
		}

		vector<int> cost = Dijkstra(g, ext);

		/*
		for(int i=0; i<cost.size(); i++) {
			cout << "cost[" << i << "] = " << cost[i] << endl; 
		}
		*/

		int mice = 0;
		for(int i=1; i<=v; i++) {
			if(cost[i]<=tempo) mice++;
		}
		cout << mice << endl;
		if(t) cout << endl; 
	}

}
/*
[0 -- {1 -- {2
 \--------/
*/
