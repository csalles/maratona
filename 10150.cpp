//10150
// doublets
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
	vector<int> bfs_ant(LABEL origem) {
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
		ret[s] = s;
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
					ret[v] = u;
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
	Graph<int, string> g;
	vector< vector<string> > vet(17);
	vector< string > vetorzao;
	while(1) {
		string str;
		getline(cin, str);
		if(str=="") break;
		g.addNode(str);
		vector<string> v = vet[ str.size() ];
		for(int i=0; i<v.size(); i++) {
			if(differByOne(str, v[i])) {
				g.addEdge(str, v[i], 1);
				g.addEdge(v[i], str, 1);
			}
		}
		vet[str.size()].push_back(str);
		vetorzao.push_back(str);
	}

	bool first = true;
	string line;
	while(getline(cin, line)) {
		if(line=="") break;
		
		if(first) first = false;
		else cout << endl;

		string src, dst;
		for(int i=0; i<line.size(); i++) {
			if(line[i]==' ') {
				src = line.substr(0, i);
				dst = line.substr(i+1);
				//cout << "SRC DST " << src << "#" << dst << endl;
				break;
			}
		}
		vector<int> ant = g.bfs_ant(src);
		int cost = ant[g.addNode(dst)];
		
		/*cout << "WA" << endl;
		continue;*/
		if(cost==INT_MAX) cout << "No solution." << endl;
		else {
			string out = dst + '\n';
			int atual = g.addNode(dst);
			while(atual!=g.addNode(src)) {
				atual = ant[atual];
				out = vetorzao[atual] + '\n' + out;
			}
			cout << out;
		}
	}
}