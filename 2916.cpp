//2916

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
	int i, n, k;
	long int v[1000010];
	const long int mod = 1000000007;

	while( scanf("%d%d", &n, &k)!=EOF ) {
		long int sum = 0;
		for(i=0; i<n; i++) {
			scanf("%ld", &v[i]);
		}
		//qsort((void*)v, n, sizeof(int), cmp);
		sort(v, v+n);//, cmp);

		for(i=0; i<k; i++) {
			sum = (sum+v[n-1-i])%mod;
		}
		//i = n-k-1;
		//while( i>=0 && v[n-k]==v[i] )
		//	sum = (sum+v[i--])%mod;

		printf("%ld\n", sum);
	}
}

