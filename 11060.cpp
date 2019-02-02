//11060

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXNODE 101
#define MAXDEGREE 201

typedef struct {
	int V, E;
	int dg[MAXNODE], inDegree[MAXNODE];
	int adj[MAXNODE][MAXDEGREE];
} Graph;

void initGraph(Graph &g, int V) {
	g.V = V;
	g.E = 0;
	for(int i=0; i<MAXNODE; i++) {
		g.dg[i] = 0;
		g.inDegree[i] = 0;
	}
}

void addEdge(Graph &g, int u, int v) {
	g.E++;
	g.adj[u][ g.dg[u]++ ] = v;
	g.inDegree[v]++;
}

int main() {
	int n;
	int caseCount=1;

	while(scanf("%d", &n)!=EOF) {
		map<string, int> nameToId;
		map<int, string> idToName;
		for(int i=0; i<n; i++) {
			string s;
			cin >> s;
			nameToId[s] = i;
			idToName[i] = s;
		}
		
		int m;
		Graph g;
		initGraph(g, n);
		cin >> m;
		for(int i=0; i<m; i++) {
			string s1, s2;
			cin >> s1 >> s2;
			int id1, id2;
			id1 = nameToId[s1];
			id2 = nameToId[s2];
			addEdge(g, id1, id2);
		}

		for(int i=0; i<n; i++) {
			sort( g.adj[i], g.adj[i] + g.dg[i] );
		}

		//topsort

		priority_queue<string, vector<string>, greater<string> > q;
		for(int i=0; i<n; i++) {
			if(g.inDegree[i]==0) {
				q.push(idToName[i]);
			}
		}

		cout << "Case #" << caseCount << ": Dilbert should drink beverages in this order:";

		while(!q.empty()) {
			string atual = q.top();
			int idAtual = nameToId[atual];
			q.pop();
			cout << " " << atual;

			for(int i=0; i<g.dg[idAtual]; i++) {
				int u = g.adj[idAtual][i];
				g.inDegree[u]--;
				if(g.inDegree[u]==0) {
					q.push( idToName[u] );
				}
			}

		}
		cout << "." << endl;

		caseCount++;
	}


}