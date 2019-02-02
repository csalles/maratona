//1476 Caminhão

#include <cstdio>


#define MAXNODE 100010

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <map>
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

	// Complexidade: O(E + VlogV)
	vector<WEIGHT> DijkstraModificado(int origem) {
		vector<WEIGHT> cost(this->V, -1);
		cost[origem] = INT_MAX;
		vector<bool> visited(this->V, false);

		priority_queue< pair<int,int>, vector<pair<int,int> > > q;
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
			for(int i=0; i<adj[wNode].size(); i++) {
				int v = adj[wNode][i];
				WEIGHT w = weight[wNode][i];
				if(visited[v]) continue;
				if(cost[v] < min(cost[wNode], w) ) {
					cost[v] = min(cost[wNode], w);
					q.push( pair<int,int>(cost[v], v) );
				}
			}
			//visitar wNode
			visited[wNode] = true;
		}
		return cost;
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
	int n, m, s;

	while( scanf("%d%d%d", &n, &m, &s)!=EOF ) {
		Graph<int> g(n);
		for(int i=0; i<m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u--; v--;
			g.addEdge(u, v, w);
			g.addEdge(v, u, w);
		}

		map<int, vector<int> > out;

		for(int i=0; i<s; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
x
			if( out.count(a) )
				cout << out[a][b] << endl;
			else if( out.count(b) )
				cout << out[b][a] << endl;
			else {
				out[a] = g.DijkstraModificado(a);
				cout << out[a][b] << endl;
			}
		}
	}

}