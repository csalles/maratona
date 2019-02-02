//2686

#include <cstdio>
#include <cmath>

int main() {
	double n;
	while( scanf("%lf", &n)!=EOF ) {

		if(n==360.00) n = 0;

		if( n<90.00 ) printf("Bom Dia!!\n");
		else if( n<180.00 ) printf("Boa Tarde!!\n");
		else if( n<270.00 ) printf("Boa Noite!!\n");
		else if( n<360.00 ) printf("De Madrugada!!\n");
		else while(1);

		//     saida - n graus
		//  60*60*24 - 360 graus
		double segundos = 60*60*24; //360.00
		segundos = segundos * n;

		//printf("==%lf\n", segundos);
	

		segundos = ceill(segundos/360.00);
		//printf("==%lf\n", segundos);
		long s = (long)segundos + 6*3600;
		//printf("--%d\n", s);
		int hora = s/3600;
		if(hora>=24) hora-=24;
		int min = (s/60)%60;
		int sec = s%60;

		printf("%02d:%02d:%02d\n", hora, min, sec);
	} 
}