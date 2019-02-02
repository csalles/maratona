//1931


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

const vector<int> &getVizinhos(LABEL Lu) {
	//if(!L.count(Lu)) return new vector<int>(0);
	//else 
	return adj[ L[Lu] ];
}
	map< pair<int,int>, int > parArestas(int c) {
		map< pair<int,int>, int> arestas;

		for(int u=0; u<c; u++) {
			if(!adj.count(u)) continue;
			vector< pair<WEIGHT,int> > viz_u = adj[u];
			
			for(int i=0; i<viz_u.size(); i++) {
				int v = viz_u[i].second;
				int costInitial = viz_u[i].first;
				if(u==v || !adj.count(v)) continue;
		
				vector< pair<WEIGHT,int> > viz_v = adj[v];
				for(int j=0; j<viz_v.size(); j++) {
					int w = viz_v[j].second;
					int cost = costInitial + viz_v[j].first;
					if(u<w) {
						pair<int, int> p(u+1,w+1);
						if(arestas.count(p)) {
							if(cost<arestas[p])
								arestas[p] = cost;
						}
						else {
							arestas[p] = cost;
						}
					}
				}
			}
		}

		return arestas;
	}

};




int main() {
	int c, v;

	cin >> c >> v;

	Graph<int,int> g, par;
	for(int i=1; i<=c; i++) {
		g.addNode(i);
		par.addNode(i);
	}

	for(int i=0; i<v; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
		g.addEdge(v, u, w);
	}


	map< pair<int,int>, int > arestas = g.parArestas(c);

	map< pair<int,int>, int >::iterator it;
	for(it = arestas.begin(); it!=arestas.end(); it++) {
		int u = it->first.first;
		int v = it->first.second;
		int cost = it->second;

		//cout << "edge " << u << " " << v << " = " << cost << endl;
		par.addEdge(u, v, cost);
		par.addEdge(v, u, cost);
	}

	vector<int> dist = par.Dijkstra(1);
	if(dist[c-1]==INT_MAX) cout << "-1" << endl;
	else cout << dist[c-1] << endl;
}