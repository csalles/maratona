//2369 Conta de Água

#include <cstdio>

int main() {
	int m, total = 7;
	scanf("%d", &m);

	if(m>10) {
		if(m>30) total += 20*1;
		else total += (m-11+1)*1;
	}

	if(m>30) {
		if(m>100) total += 70*2;
		else total += (m-31+1)*2;
	}

	if(m>100) {
		total += (m-100)*5;
	}
	printf("%d\n", total);
}
