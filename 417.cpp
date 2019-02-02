//417
//417 - Word Index


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
	map<string, int> m;
	queue<string> q;
	int count=1;

	for(char c='a'; c<='z'; c++) {
		q.push(string(1,c));
	}

	while(!q.empty()) {
		string s = q.front();
		q.pop();

		m[s] = count++;

		//cout << s << " := " << count-1 << endl;

		if(s.size()<5) {
			char last = s[s.size()-1];
			last++;
			while(last<='z') {
				q.push( s + last );
				last++;
			}
		}
	}

	string s;
	while( getline(cin, s) ) {
		if(m.count(s)==0) cout << 0 << endl;
		else cout << m[s] << endl;
	}

}
