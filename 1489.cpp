/*
 * C++ Program to Implement The Edmonds-Karp Algorithm
 */
#include<cstdio>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
 
using namespace std; 

#define MAXNODES 105
int capacities[MAXNODES][MAXNODES];
int flowPassed[MAXNODES][MAXNODES];
vector<int> graph[MAXNODES];
int parentsList[MAXNODES];       
int currentPathCapacity[MAXNODES];  
 
int bfs(int startNode, int endNode)
{
    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));
 
    queue<int> q;
    q.push(startNode);
 
    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = 999;
 
    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();
 
        for(int i=0; i<graph[currentNode].size(); i++)
        {
            int to = graph[currentNode][i];
            if(parentsList[to] == -1)
            {
                if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
                {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], 
                    capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if(to == endNode)
                    {
                        return currentPathCapacity[endNode];
                    }
                    q.push(to);
                }
            }
        }
    }
    return 0;
}
 
int edmondsKarp(int startNode, int endNode)
{
    int maxFlow = 0;
      while(true)
    {
        int flow = bfs(startNode, endNode);
        if (flow == 0) 
        {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while(currentNode != startNode)
        {
            int previousNode = parentsList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }
    return maxFlow;
}
int main()
{
    int instances;
    cin >> instances;

    for(int k=1; k<=instances; k++) {    

        int nodesCount;
        cin>>nodesCount;
  
        bool dgZero = false;
        for(int u=0; u<nodesCount; u++) {
            int dg;
            cin>>dg;
            if(dg==0) dgZero=true;
            while(dg--) {
                int v;
                cin >> v;
                capacities[u][v] = 1;
                graph[u].push_back(v);
                //graph[v].push_back(u);
            }
        }

        int source = nodesCount;
        int sink = nodesCount+1;

/*
        for(int u=0; u<nodesCount; u++) {
            capacities[source][u] = 1;
            graph[source].push_back(u);
            capacities[u][sink] = 1;
            graph[u].push_back(sink);
        }
*/
        int maxFlow = edmondsKarp(0, nodesCount-1);
     
        cout << "Instancia " << k << endl;
        cout << "maxFlow = " << maxFlow << endl;
        if(maxFlow==nodesCount-1) cout << "pair programming" << endl << endl;
        else cout << "extreme programming" << endl << endl;
    } 
}