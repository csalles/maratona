
#include<cstdio>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
 
using namespace std; 
 
#define MAXNODES 101

vector<int> graph[MAXNODES];

int bfs(int startNode, int endNode, int *parentsList)
{
   int currentPathCapacity[MAXNODES];  
 
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
    int parentsList[MAXNODES];
    int capacities[MAXNODES][MAXNODES];
    int flowPassed[MAXNODES][MAXNODES];


    int maxFlow = 0;
      while(true)
    {
        int flow = bfs(startNode, endNode, parentsList);
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

int main() {
    int k, K;
    cin >> K;

    for(k=1; k<=K; k++) {
        int n;
        cin >> n;

    }
}
