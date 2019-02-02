//2414 Desafio do Maior Número

#include <cstdio>

int main() {
	int maior = -1;
	int n;
	while(1) {
		scanf("%d", &n);
		if(!n) break;
		if(n>maior) maior=n;
	}
	printf("%d\n", maior);
}
