
//1610 Dudu Faz Serviço

#define MAXNODE 10010

#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <iostream>
#include <stack>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

template <class WEIGHT>
class Graph {
protected:
	int V, E;
	vector<int> adj[MAXNODE];
	vector<WEIGHT> weight[MAXNODE];

public:
	Graph(int v) : V(v), E(0) {};

	void addEdge(int u, int v, WEIGHT w) {
		adj[u].push_back(v);
		weight[u].push_back(w);
	}

	bool dfs(int node, vector<int> &visited) {
		for(int i=0; i<adj[node].size(); i++) {
			int viz = adj[node][i];
			if(visited[viz]==PRETO) continue;
			if(visited[viz]==CINZA) return true;
			visited[viz] = CINZA;
			if( dfs(viz, visited) ) return true; 
		}
		visited[node] = PRETO;
		return false;
	}

	bool hasCycle() {
		vector<int> visited(this->V, BRANCO);
		for(int v=0; v<this->V; v++) {
			if(visited[v]==PRETO) continue;

			if(visited[v]==CINZA) while(1);
			
			visited[v] = CINZA;
			if( dfs(v, visited) ) return true;
		}
		return false;
		/*
			stack<int> s;
			s.push(v);
			visited[v] = CINZA;

			while(!s.empty()) {
				int w = s.top();
				s.pop();

				for(int i=0; i<adj[w].size(); i++) {
					int viz = adj[w][i];
					if(visited[viz]==PRETO) continue;
					if(visited[viz]==CINZA) return true;

					s.push(viz);
					visited[viz] = CINZA;
				}
				visited[w] = PRETO;
			}
		}
		return false;
		*/
	}
};


template < class  WEIGHT>
class TarjanGraph : public Graph<WEIGHT> {
protected:
	bool onStack[MAXNODE];
	int index[MAXNODE], lowlink[MAXNODE];
	vector< vector<int> > sccs; // strongly connected graphs
public:
	TarjanGraph(int v) : Graph<WEIGHT>(v) {};


	void strongconnect(int v, stack<int> &S, int &timeIndex) {
    	// Set the depth index for v to the smallest unused index
    	index[v] = timeIndex;
    	lowlink[v] = timeIndex;
    	timeIndex++;
    	S.push(v);
    	onStack[v] = true;

	    // Consider successors of v
    	for(int i=0; i<this->adj[v].size(); i++) {
    		int w = this->adj[v][i];
		    if(index[w]==-1) {
	        // Successor w has not yet been visited; recurse on it
        		strongconnect(w, S, timeIndex);
        		lowlink[v] = min(lowlink[v], lowlink[w]);
    		}
    		else if (onStack[w]) {
	        // Successor w is in stack S and hence in the current SCC
	        // If w is not on stack, then (v, w) is a cross-edge in the DFS tree and must be ignored
	        // Note: The next line may look odd - but is correct.
	        // It says w.index not w.lowlink; that is deliberate and from the original paper
        		lowlink[v] = min(lowlink[v], index[w]);
        	}
        }

	    // If v is a root node, pop the stack and generate an SCC
    	if (lowlink[v] == index[v]) {
    		vector<int> aSCC;
    		int w;
    		do {
    			w = S.top();
    			S.pop();
    			onStack[w] = false;
    			aSCC.push_back(w);
    		}
    		while(w!=v);
    		sccs.push_back(aSCC);
    	}
    }

	vector< vector<int> > tarjan() {
		sccs.clear();
		stack<int> S;
		int timeIndex = 0;
		
		for(int i=0; i<this->V; i++) {
			index[i] = -1; 
			onStack[i] = false;
		}

		for(int i=0; i<this->V; i++) {
			if(index[i]==-1)
				strongconnect(i, S, timeIndex);
		}
		return sccs;
	}


};


int main() {
	int t;
	cin >> t;

	while(t--) {
		int n, m;
		cin >> n >> m;

		Graph<int> g(n);

		set< pair<int,int> > s;
		for(int i=0; i<m; i++) {
			int a, b;
			cin >> a >> b;
			if(a>n||b<1) while(1);
			a--;
			b--;
			pair<int,int> p(a,b);
			if(!s.count(p)) {
				g.addEdge(a, b, 1);
			}
		}
		if(g.hasCycle()) cout << "SIM" << endl;
		else cout << "NAO" << endl;

	}

}
