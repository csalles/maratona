//11518
//Dominos 2


#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

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
	void dfs(LABEL origem, vector<bool> &visited) {
		//inicializa visited com false
		//vector<bool> visited(V, false);
		//inicializa uma pilha st com s
		stack<int> st;
		if(L.count(origem)==0)
			return;
		int s = L[origem];
		if(visited[s]) return;

		st.push(s);
		visited[s] = true;

		//cout << "dfs( LABEL " << origem << " = " << s << ")" << endl;
		//laco principal
		while(!st.empty()) {
			int u = st.top();
			st.pop();
			vector< pair<WEIGHT,int> > viz = adj[u];
			for(int i=0; i<viz.size(); i++) {
				int v = viz[i].second;
				if(!visited[v]) {
					visited[v] = true;
					st.push(v);
				}
			}
		}
	}


};



int main() {
	int casos;

	cin >> casos;
	while(casos--) {
		int n, m, l;
		cin >> n >> m >> l;

		Graph<int,int> g;
		for(int i=1; i<=n; i++) {
			g.addNode(i);
		}

		for(int i=0; i<m; i++) {
			int x, y;
			cin >> x >> y;
			g.addEdge(x, y, 1);
		}

		vector<bool> visited(n+1, false);
		for(int i=0; i<l; i++) {
			int node;
			cin >> node;
			g.dfs(node, visited);
		}
		int cont = 0;
		for(int i=0; i<n+1; i++) {
			if(visited[i]) cont++;
		}
		cout << cont << endl;
	}
}