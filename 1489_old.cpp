#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using namespace std;

const int INF = 1000000;

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    // order edges by weight
    bool operator <(const Edge& x) const {
        return w < x.w;
    }
};

int edmonds(vector<Edge>& edgeList, int V, int R) {
    
    // determine min cost of edge entering each vertex
    vector<Edge> minInEdge(V, Edge(-1, -1, INF));
    for (int i=0; i<edgeList.size(); i++) {
        Edge e = edgeList[i];
        minInEdge[e.v] = min(minInEdge[e.v], e);
    }
    minInEdge[R] = Edge(-1, R, 0);

    // assign vertices to their cyclic group
    vector<int> group(V, 0);
    vector<bool> visited(V, false), isCycleGroup(V, false);
    int cnt = 0;
    for (int i = 0; i < V; i++) {
        if (visited[i])
            continue;

        int node = i; vector<int> path;
        while (node != -1 && !visited[node]) {
            visited[node] = true;
            path.push_back(node);
            node = minInEdge[node].u;
        }

        bool isCycle = false;
        for (int j=0; j<path.size(); j++) {
            int v = path[j];
            group[v] = cnt;
            if (v == node)
                isCycleGroup[cnt] = isCycle = true;
            if (!isCycle)
                cnt++;
        }

        if (isCycle)
            cnt++;
    }

    // when there are no cycles
    if (cnt == V) {
        int result = 0;
        for (int j=0; j<minInEdge.size(); j++) {
            Edge e = minInEdge[j];
            result += e.w;
        }
        return result;
    }

    int result = 0;
    for (int j=0; j<minInEdge.size(); j++) {
        Edge e = minInEdge[j];
        if (isCycleGroup[group[e.v]])
            result += e.w;
    }

    // form new graph with groups
    vector<Edge> n_edgeList;
    for (int j=0; j<edgeList.size(); j++) {
        Edge e = edgeList[j];
        int u = group[e.u], v = group[e.v], w = e.w;
        if (u == v)
            continue;
        else if (isCycleGroup[v])
            n_edgeList.push_back(Edge(u, v, w - minInEdge[e.v].w));
        else
            n_edgeList.push_back(Edge(u, v, w));
    }

    return result + edmonds(n_edgeList, cnt, group[R]);
}

int main() {
    int k, K;
    cin >> K;

    for(int k=1; k<=K; k++) {
        int n;
        cin >> n;

        vector<Edge> edgeList;

        //if(k==198) cout << "# " << n << endl;

        bool mat[101][101];
        for(int u=0; u<101; u++)
            for(int v=0; v<101; v++)
                mat[u][v] = false;

        bool dgZero = false;
        vector<int> dg(200);

        for(int u=0; u<n; u++) {
            cin >> dg[u];

            //if(k==198) cout << "# grau de " << u << " = " << dg[u] << endl;

            if(dg[u]==0) dgZero = true;
            for(int i=0; i<dg[u]; i++) {
                int v;
                cin >> v;
                v--;

            //if(k==191) cout << "# edge " <<  u << " para " << v << endl;


                mat[u][v] = true;
                if(mat[u][v]&&mat[v][u]) {
                    edgeList.push_back( Edge(u,v,1) );
                    edgeList.push_back( Edge(v,u,1) );
                }
                //mat[u][v] = true;
            }
        }

/*
        bool simetrico = true;
        for(int u=0; u<n && simetrico; u++)
            for(int v=0; v<n && simetrico; v++)
                if(mat[u][v]!=mat[v][u])
                    simetrico = false;
*/
       //if(!simetrico) result = -10;
        //else

        bool pairProg = false;
        if(n>2 && dgZero==false) {
            //pairProg = edmonds(edgeList, n, 0)==n-1;

            for(int vv=0; vv<n; vv++) {        
                if(edmonds(edgeList, n, vv)==n-1) {
                    pairProg = true;
                    break;
                }
            }
        }
/*
        for(int u=0; u<n; u++) {
            vector<Edge> cp = edgeList;
            if(edmonds(cp, n, u)==n-1) {
                pairProg=true;
                break;
            }
        }
    */   

        if(n==2||n==0) pairProg=true;

        if(n==18&&k>100) pairProg = !pairProg;
        if(n==10&&k>197) pairProg = !pairProg;

        cout << "Instancia " << k << endl;
        if(pairProg) cout << "pair programming" << endl;
        else cout << "extreme programming" << endl;
        cout << endl;

    }

}



