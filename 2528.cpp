//2528

#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <iostream>
using namespace std;

template <class WEIGHT, class LABEL=int>
class Graph {
private:
	int V, E;
	map<LABEL, int> L;
	map<int, vector< pair<WEIGHT, int> > >adj;
public:
	Graph(int v=0) {
		this->V = v;
		this->E = 0;
	};

	int addNode(LABEL u) {
		if(L.count(u)) return L[u];
		else return L[u] = this->V++;
	}

	bool addEdge(LABEL labelU, LABEL labelV, WEIGHT w){
		int u = addNode(labelU);
		int v = addNode(labelV);
		if(adj.count(u)==0)
			adj[u] = vector< pair<WEIGHT, int> >();
		adj[u].push_back( pair<WEIGHT,int>(w, v) );
		this->E++;
		return true;
	}

	//retorna a distancia de todos para a origem s
	vector<int> bfs(LABEL origem) {
		int s;
		//inicializando visited com false
		vector<bool> visited(V, false);
		//retorno com a distancia de todos para s
		vector<int> ret(V, INT_MAX);
		//criando fila com s
		queue<int> q;

		if(L.count(origem)==0)
			return ret;
		s = L[origem];

		q.push(s);
		visited[s] = true;
		ret[s] = 0;
		//laco principal
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			//iterar os vizinhos de u
			vector< pair<WEIGHT,int> > viz = adj[u];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i].second;
				if(!visited[v]) {
					visited[v] = true;
					ret[v] = ret[u]+1;
					q.push(v);
				}
			}
		} //laco principal
		return ret;
	}

	//returns the number of visited nodes
	int dfs(LABEL origem) {
		int ret = 0;
		//inicializa visited com false
		vector<bool> visited(V, false);
		//inicializa uma pilha st com s
		stack<int> st;
		if(L.count(origem)==0)
			return 0;
		int s = L[origem];

		st.push(s);
		visited[s] = true;
		//laco principal
		while(!st.empty()) {
			int u = st.top();
			st.pop();
			ret++;
			vector< pair<WEIGHT,int> > viz = adj[u];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i];
				if(!visited[v]) {
					visited[v] = true;
					st.push(v);
				}
			}
		}
		return ret;
	} //dfs

	// g eh um grafo dirigido obrigatoriamente sem ciclos
	vector<int> topSort() {
		vector<int> ret;//retorno da funcao
		vector<int> inDegree(V, 0); //inDegree
		//inicializo inDegree
		for(int u=0; u<V; u++) {
			vector< pair<WEIGHT,int> > viz = adj[u];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i].second;
				inDegree[v]++;
			}
		}
		//inicializo fila q com todos inDegree 0
		queue<int> q;
		for(int u=0; u<V; u++) {
			if(inDegree[u]==0)
				q.push(u);
		}
		//laco principal sobre a fila q
		while(!q.empty()) {
			int u = q.front();
			ret.push_back(u);
			q.pop();
			vector< pair<WEIGHT,int> > viz = adj[u];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i];
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
	vector<int> Dijkstra(LABEL origemL) {
		vector<int> cost(V, INT_MAX);
		if(L.count(origemL)==0)
			return cost;
		int origem = L[origemL];
		cost[origem] = 0;
		vector<bool> visited(V, false);

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
			vector< pair<WEIGHT,int> > viz = adj[wNode];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i].second;
				WEIGHT w = viz[i].first;
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
	} //Dijkstra


};



int main() {

	int n, m;

	while( cin >> n >> m ) {
		Graph<int,int> g;
		for(int i=1; i<=n; i++)
			g.addNode(i);

		vector< pair<int,int> > edges(m);
		for(int i=0; i<m; i++) {
			cin >> edges[i].first >> edges[i].second;
		}
		int c, r, e;
		cin >> c >> r >> e;

		for(int i=0; i<m; i++) {
			if(edges[i].first!=e && edges[i].second!=e) {
				g.addEdge(edges[i].first, edges[i].second, 1);
				g.addEdge(edges[i].second, edges[i].first, 1);
			}
		}
		vector<int> d = g.bfs(c);
		cout << d[r-1] << endl;
	}


}