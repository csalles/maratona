#include <iostream>
#include <cstdio>
#include <limits>
using namespace std;

//10385 - Duathlon
//busca ternaria

int n;
double t;

double cycling[101], running[101];

double simulate(double r, double c) {
	double briber = r/running[n-1] + c/cycling[n-1];
	double other = r/running[0] + c/cycling[0];
	for(int i=1; i<n-1; i++) {
		double atual = r/running[i] + c/cycling[i];
		other = min(other, atual);
	}
	return other - briber;
}

double best_r() {
	double esq = 0, dir = t;
	for(int i=0; i<150; i++) {
		double r1 = (esq*2+dir)/3;
		double r2 = (esq+2*dir)/3;
		if( simulate(r1, t-r1) < simulate(r2, t-r2) ) {
			esq = r1;
		}
		else {
			dir = r2;
		}
	}
	return (esq+dir)/2.0;
}

int main() {
	while(scanf("%lf", &t)!=EOF) {
		scanf("%d", &n);
		for(int i=0; i<n; i++) {
			scanf("%lf%lf", &running[i], &cycling[i]);
		}

		//printf("*** %lf\n", t);

		double bestOut = best_r();
		double out = simulate(bestOut, t-bestOut);

		if(out<0) printf("The cheater cannot win.\n");
		else printf("The cheater can win by %.0lf seconds with r = %.02lfkm and k = %.02lfkm.\n", 3600*out, bestOut, t-bestOut);

	}
}
