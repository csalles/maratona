//1704

#include <cstdio>
#include <queue>
using namespace std;

int main() {
	int n, h;

	int v[1010], t[1010];
	bool doing[1010];

	while(scanf("%d%d", &n, &h)!=EOF) {
		priority_queue< pair<int,int> > q;

		for(int i=0; i<h; i++)
			doing[i] = false;

		for(int i=0; i<n; i++) {
			scanf("%d%d", &v[i], &t[i]);
			q.push( pair<int,int>(v[i], t[i]) );
		}

		int out = 0;
		while(!q.empty()) {
			pair<int,int> p = q.top();
			q.pop();

			bool ok = false;
			for(int j=p.second-1; j>=0; j--) {
				if(!doing[j]) {
					doing[j] = true;
					ok = true;
					break;
				}
			}
			if(!ok) {
				out += p.first;
			}
		} //fila
		printf("%d\n", out);
	}

}
