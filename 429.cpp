//429
//Word Transformation

#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <cstdlib>
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
				pair<WEIGHT,int> p = viz[i];
				int v = p.second;
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

bool differByOne(string a, string b) {
	if(a.size()!=b.size()) return false;
	int c=0;
	for(int i=0; i<a.size(); i++) {
		if(a[i]!=b[i]) c++;
		if(c>1) return false;
	}
	return c==1;
}

int main() {
	string line;
	int T;

	getline(cin, line);
	T = atoi(line.c_str());
	getline(cin, line);

	bool first = true;

	while(T--) {
		Graph<int, string> g;
		vector<string> v;

		if(first) first = false;
		else cout << endl;

		while(1) {
			string str;
			getline(cin, str);
			if(str=="*") break;
			g.addNode(str);
			for(int i=0; i<v.size(); i++) {
				if(differByOne(str, v[i])) {
					g.addEdge(str, v[i], 1);
					g.addEdge(v[i], str, 1);
				}
			}
			v.push_back(str);
		}
		while(getline(cin, line)) {
			if(line=="") break;
			string src, dst;
			for(int i=0; i<line.size(); i++) {
				if(line[i]==' ') {
					src = line.substr(0, i);
					dst = line.substr(i+1);
					//cout << "SRC DST " << src << "#" << dst << endl;
					break;
				}
			}
			vector<int> dist = g.bfs(src);
			int d = dist[g.addNode(dst)];
			cout << src << " " << dst << " " << d << endl;
		}
	}
}