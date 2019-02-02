//2142 Pegue o Pombo!

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
	long int A, B;

	int m[1001][1001];

	while( cin >> A >> B) {

		if(3*B>A) {
			printf("Raios! Raios Duplos! Raios Triplos!\n");
			continue;
		}

		int a = sqrt(A);
		//cout << "# " << a << endl;
		int lin=0, col=-1;
		int cont = A;

		for(int i=0; i<a; i++)
			for(int j=0; j<a; j++)
				m[i][j] = -1;

		while(cont>0) {

			while(col+1<a && m[lin][col+1]==-1) {
				m[lin][++col] = cont--;
			}
			while(lin+1<a && m[lin+1][col]==-1) {
				m[++lin][col] = cont--;
			}
			while(col-1>=0 && m[lin][col-1]==-1) {
				m[lin][--col] = cont--;
			}
			while(lin-1>=0 && m[lin-1][col]==-1) {
				m[--lin][col] = cont--;
			}
		}

		for(int i=0; i<a; i++) {
			for(int j=0; j<a; j++) {
				if(m[i][j]==2*B) {
					// *
					if(A>99999)     printf("     *");
					else if(A>9999) printf("    *");
					else if (A>999) printf("   *");
					else if(A>99)   printf("  *");
					else if(A>9)    printf(" *");
					else            printf("*");
				}
				else if(m[i][j]==3*B) {
					// !
					if(A>99999)     printf("     !");
					else if(A>9999) printf("    !");
					else if (A>999) printf("   !");
					else if(A>99)   printf("  !");
					else if(A>9)    printf(" !");
					else            printf("!");
				}
				else if(A>99999) printf("%6d", m[i][j]);
				else if(A>9999) printf("%5d", m[i][j]);
				else if (A>999) printf("%4d", m[i][j]);
				else if(A>99) printf("%3d", m[i][j]);
				else if(A>9) printf("%2d", m[i][j]);
				else printf("%d", m[i][j]);
				

				if(j==a-1) {
					if(i==a-1) printf("\n"); 
					else printf(" \n");
				}
				else printf(" ");
			}
		}

	}	
}

