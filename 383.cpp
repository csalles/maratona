//383
//Shipping Routes

#include <map>
#include <vector>
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
};

int main() {
	int T;
	cin >> T;

	cout << "SHIPPING ROUTES OUTPUT" << endl;

	for(int t=1; t<=T; t++) {
		int M, N, P;
		cin >> M >> N >> P;

		Graph<int, string> g;
		for(int i=0; i<M; i++) {
			string id;
			cin >> id;
			g.addNode(id);
		}
		for(int i=0; i<N; i++) {
			string src, dst;
			cin >> src >> dst;
			g.addEdge(src, dst, 1);
			g.addEdge(dst, src, 1);
		}
		cout << endl << "DATA SET  " << t << endl << endl;
		for(int i=0; i<P; i++) {
			int sz;
			string src, dst;
			cin >> sz >> src >> dst;
			vector<int> d = g.bfs(src);
			int cost = d[ g.addNode(dst) ];
			if(cost==INT_MAX) cout << "NO SHIPMENT POSSIBLE"<<endl;
			else cout << "$" << cost*100*sz << endl;
		}

	} //while(T)
	cout << endl << "END OF OUTPUT" << endl;
}
