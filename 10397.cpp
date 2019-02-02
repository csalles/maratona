
#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>
using namespace std;

int B;
int E;

// adj == vizinhos
double weight[751][751];

int X[751], Y[751];

typedef struct {
	double weight;
	int u, v;
} aresta;

const bool operator <(const aresta &a, const aresta &b) {
	return a.weight<b.weight;	
}

int SET(int *DJ, int e) {
	if( DJ[e]==e ) return e;
	else return DJ[e] = SET(DJ, DJ[e]);
}

void UNION(int *DJ, int e1, int e2) {
	int set1 = SET(DJ, e1);
	int set2 = SET(DJ, e2);
	DJ[set1] = set2;
}


int main() {
	while(1) {
		if( scanf("%d", &B) == EOF ) break;
		
		for(int i=1; i<=B; i++) {
			scanf("%d%d", &X[i], &Y[i]);
		}

		for(int i=1; i<=B; i++) {
			for(int j=i; j<=B; j++) {
				weight[i][j] =
				weight[j][i] = sqrt(
					            (X[i]-X[j])*(X[i]-X[j]) +
					            (Y[i]-Y[j])*(Y[i]-Y[j]) );

			}
		}

		scanf("%d", &E);
		for(int i=0; i<E; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			weight[a][b] = weight[b][a] = 0;
		}

		vector<aresta> v;

		for(int i=1; i<=B; i++) {
			for(int j=i+1; j<=B; j++) {
				aresta e;
				e.weight = weight[i][j];
				e.u = i;
				e.v = j;
				v.push_back(e);
			}
		}

		sort(v.begin(), v.end());

		int DJ[751];
		for(int i=1; i<=B; i++)
			DJ[i] = i;

		double sum = 0;
		for(vector<aresta>::iterator it=v.begin(); it!=v.end(); it++) {
			if( SET(DJ, it->u) != SET(DJ, it->v) ) {
				sum += it->weight;
				UNION(DJ, it->u, it->v);
				/*
				int aux = DJ[it->u];
				for(int i=1; i<=B; i++) {
					if( DJ[i] == aux ) {
						DJ[i] = DJ[it->v];
					}
				}
				*/
			}
		}
		printf("%.2lf\n", sum);

	} 
}