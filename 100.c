#include <stdio.h>

int ciclo(int n) {
	if(n==1) return 1;
	if(n%2==0)
		return ciclo(n/2)+1;
	else
		return ciclo(3*n+1)+1;
}

int main() {
	int a, b;
	int menor, maior;
	int i, resultado, aux;

	while( scanf("%d%d", &a, &b)!=EOF ) {
		if(a>b) {
			maior = a;
			menor = b;
		}
		else {
			maior = b;
			menor = a;
		}

		resultado = ciclo(menor);
		for(i=menor+1; i<=maior; i++) {
			aux = ciclo(i);
			if(aux>resultado) 
				resultado=aux;
		}
		printf("%d %d %d\n", a, b, resultado);
	}

}