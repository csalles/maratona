//1903
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <iostream>
#include <cstring>
using namespace std;

int n, m;
int visited[100001];
int okNodes[100001];

//int src[100001], dst[100001];
//int inDegree[100001], outDegree[100001];

vector<int> g[100001];//[100001];
vector<int> g_inv[100001];//[100001];

int dfs(int s, int grafo) 
{
	stack<int> st;
	int contOkNodes = 0;
	memset(visited, 0, sizeof visited);
	st.push(s);
	while(!st.empty()) {
		s = st.top();
		st.pop();
		visited[s] = 1;
		//cout << "visited " << s <<  " grafo " << grafo << endl; 
		if(grafo==0) {
			for(int i=0; i<g[s].size(); i++) {
				int v = g[s][i];
				if(!okNodes[v]) {
					contOkNodes++;
					okNodes[v] = 1;
					//cout << "okNodes " << v << " grafo " << grafo << endl;
				}
				if(!visited[v])
					st.push(v);
			}
		}
		else { //grafo 1
			//cout << "ta certo" << endl;
			for(int i=0; i<g_inv[s].size(); i++) {
				int v = g_inv[s][i];
				//cout << "s=" << s << " v=" << v << "visited v =" << visited[v] <<  endl;
				if(!okNodes[v]) {
					contOkNodes++;
					okNodes[v] = 1;
					//cout << "okNodes " << v << " grafo " << grafo << endl;
				}
				if(!visited[v])
					st.push(v);
			}		
		}//grafo 1
	}
	return contOkNodes;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	//memset( inDegree, 0, sizeof inDegree );
	//memset( outDegree, 0, sizeof outDegree );

	for(int i=0; i<m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g_inv[v].push_back(u);
	}

	/*
	for(int i=0; i<m; i++) {
		cin >> src[i] >> dst[i];
		inDegree[dst[i]]++;
		outDegree[src[i]]++;
	}

	for(int i=1; i<=n; i++) {
		g[i] = vector<int>(outDegree[i]);
		g_inv[i] = vector<int>(inDegree[i]);
	}

	for(int i=0; i<m; i++) {
		g[ src[i] ][ --outDegree[(src[i])] ] = dst[i];
		g_inv[ dst[i] ][ --inDegree[(dst[i])] ] = src[i];
	}
	*/

//	for(int i=1; i<=n; i++) {
//		for(int j=0; j<g[i].size(); j++) {
//			cout << i << " para " << g[i][j] << endl;
//		}
//	}


	memset(okNodes, 0, sizeof okNodes);
	int cont = dfs(1, 0);
	cont += dfs(1, 1);

	bool bolada = true;
	for(int i=1; i<=n; i++) {
		if(!okNodes[i]) {
			bolada = false;
			break;
		}
	}

	if(bolada) cout << "Bolada" << endl;
	else cout << "Nao Bolada" << endl;

	//free(visited);
	//free(okNodes);
}

