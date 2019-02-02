//2841

#include <cstdio>
#include <vector>
using namespace std;

int n;
int cost[100010];
int boss[100010];
vector<int> children[100010];

long int memo[2][100001];

long int search(int tp, int node) {
	if(memo[tp][node]!=-1) return memo[tp][node];
	int ret;
	if(tp==0) {
		ret = 0;
		for(int i=0; i<children[node].size(); i++) {
			int cNode = children[node][i];
			int aux1 = search(0, cNode);
			int aux2 = search(1, cNode);
			ret += (aux1 > aux2 ? aux1 : aux2);
		}		
	}
	else {
		ret = cost[node];
		for(int i=0; i<children[node].size(); i++) {
			int cNode = children[node][i];
			ret += search(0, cNode);
		}
	}
	return memo[tp][node] = ret;
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &cost[i]);
		memo[0][i] = memo[1][i] = -1;
	}
	for(int i=2; i<=n; i++) {
		scanf("%d", &boss[i]);
		children[ boss[i] ].push_back(i);
	}

	long int aux1 = search(0, 1);
	long int aux2 = search(1, 1);
	long int best = aux1>aux2 ? aux1 : aux2;
	printf("%ld\n", best);
}

