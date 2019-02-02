//2889

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct {
	int points, gols, id;
} score;

bool cmp(const score &a, const score &b) {
	if(a.points > b.points) return true;
	if(b.points > a.points) return false;
	if(a.gols > b.gols) return true;
	if(b.gols > a.gols) return false;
	return a.id < b.id;
}

int main() {
	int n;
	int vice[1000010];
	vector<score> v(1000010);

	cin >> n;
	for(int i=0; i<=n; i++) vice[i] = 0;

	while(1) {
		int m;
		cin >> m;
		if(!m) break;

		for(int i=0; i<=n; i++) {
			v[i].points = 0;
			v[i].gols = 0;
			v[i].id = i;
		}

		for(int i=0; i<m; i++) {
			int time1, placar1, time2, placar2;
			cin >> time1 >> placar1 >> time2 >> placar2;
			if(placar1>placar2) {
				v[time1].points += 3;
			}
			else if(placar2>placar1) {
				v[time2].points += 3;
			}
			else {
				v[time1].points++;
				v[time2].points++;
			}
			v[time1].gols += placar1;
			v[time2].gols += placar2;
		}

		score maior, segMaior;
		if(cmp(v[1],v[2])) {
			maior = v[1];
			segMaior = v[2];
		}
		else {
			maior = v[2];
			segMaior = v[1];
		}
		for(int i=3; i<=n; i++) {
			if(cmp(v[i],maior)) {
				segMaior = maior;
				maior = v[i];
			}
			else if(cmp(v[i],segMaior)) {
				segMaior = v[i];
			}
		}

		//sort(v.begin()+1, v.end(), cmp);

		//for(int pos=1; pos<=n; pos++) {
		//	cout <<"*pos[" << pos << "] points=" << v[pos].points << " gols=" << v[pos].gols << " id=" << v[pos].id << endl;
		//}

		//cout << "** vice = " << v[2].id << endl << endl;
		vice[ segMaior.id ]++;

	}

	int maior = vice[1];
	for(int i=2; i<=n; i++) if(vice[i]>maior) maior=vice[i];
	if(vice[1]==maior) cout << "Y" << endl;
	else cout << "N" << endl;

}
