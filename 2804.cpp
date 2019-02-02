//2804

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	long int k;
	long int m[451][451];

	scanf("%d%ld", &n, &k);

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			scanf("%ld", &m[i][j]);
			if(m[i][j]<0 || m[i][j]>1000000)
				while(1);
			if(m[i][j]==0 && i!=j)
				while(1);
		}

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if( (m[i][j]!=m[j][i]) ||
			    (i==j && m[i][j]!=0) || 
			    (i!=j && m[i][j]==0) ||
			    (m[i][j]<0 || m[i][j]>1000000)
			  ) 
			{
				printf("*\n");
				return 0;
			}

	int contEdges=0;

	for(int u1=0; u1<n; u1++) {
		for(int u2=u1+1; u2<n; u2++) {
			long int min = -1;
			for(int i=0; i<n; i++) {
				if(i==u1||i==u2) continue;
				long int aux = m[u1][i]+m[i][u2];

				if(min==-1 || aux<min) {
					min = aux;
				}
			}
			if(m[u1][u2]<min) {
				contEdges++;
			}
			else if(m[u1][u2]>min) {
				printf("*\n");
				return 0;
			}
		}
	}
	printf("%ld\n", contEdges*k);
}

/*
int main() {

	int n, k;
	int m[451][451];

	scanf("%d%d", &n, &k);

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			scanf("%d", &m[i][j]);

	vector< pair< int, pair<int, int> > > v;

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			if( (m[i][j]!=m[j][i]) ||
			    (i==j && m[i][j]!=0) ) 
			{
				printf("*\n");
				return 0;
			}
			if( i<j ) {
				pair<int,int> p(i, j);
				pair<int, pair<int,int> >e(m[i][j], p);
				v.push_back(e);
			}
		}

	int contNodes = n;
	int last = 0;
	vector<bool> b(n, false);

	sort(v.begin(), v.end());

	int contEdges = 0;

	for(int i=0; i<v.size(); i++) {
		int node1 = v[i].second.first;
		int node2 = v[i].second.second;

		//if(v[i].first == last) continue;
		last = v[i].first;

		cout << "[" << node1 << "][" << node2 << "] cost = " << v[i].first << endl;

		
		contEdges++;

		if(!b[node1]) {
			b[node1] = true;
			contNodes--;
		}
		if(!b[node2]) {
			b[node2] = true;
			contNodes--;
		}
		if(contNodes==0) {
			//cout << "contEdges = " << contEdges << endl;
			printf("%d\n", (contEdges)*k);
			return 0;
		}
	}


}
*/
