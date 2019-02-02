

//f(n) = 3*n+1, se n for impar

#include <stdio.h>

/*
int ciclo(int n) {
	if(n==1) return 1;
	else if(n%2==0) return ciclo(n/2)+1;
	else return ciclo(3*n+1)+1;
}
*/


int ciclo(int n) {
	int ret = 1;
	while(n!=1) {
		ret++;
		 n = (n%2) ? 3*n+1 : n/2;
	}
	return ret;
}
/*
int ciclo(int n) {
	for(int ret=1; ;ret++) {
		if(n==1) return ret;
		n = n%2==0 ? n/2 : 3*n+1;
	}
	return 1; //evitar warnings
}
*/

int main() {
	int a, b;

	while(scanf("%d %d", &a, &b)!=EOF) {
		if (a>b) {
			int aux = a;
			a = b;
			b = aux;
		}
		int MAX = ciclo(a);
		for(int i=a+1; i<=b; i++) {
			int aux = ciclo(i);
			if(aux>MAX) MAX = aux;
		}
		printf("%d %d %d\n", a, b, MAX);
	}
}








