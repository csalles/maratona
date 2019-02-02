//1128

//https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/




#define MAXNODE 5000

#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>
using namespace std;

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
	int n, m;
	while(1) {
		scanf("%d %d", &n, &m);
		if(!n&&!m) break;

		TarjanGraph<int> g(n);

		for(int i=0; i<m; i++) {
			int v, w, p;
			scanf("%d %d %d", &v, &w, &p);
			v--; w--;
			g.addEdge(v, w, 1);
			if(p==2) g.addEdge(w, v, 1);
		}
		vector< vector<int> > out = g.tarjan();

		if(out.size()==1) printf("1\n");
		else printf("0\n");

	}
}