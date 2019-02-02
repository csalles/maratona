//1027 Onda Crítica

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int bestA( int a, vector< pair<int, int> > &v) {
	int sup = a-1;
	int inf = a+1;
	int nextSup = a+1;
	int nextInf = a-1;
	int contSup = 0;
	int contInf = 0;
	int indexSup = -1;
	int indexInf = -1;
	for(int i=0; i<v.size(); i++) {
		if(v[i].second==sup) {
			if(indexSup==-1 || v[indexSup].first < v[i].first) {
				indexSup = i;
				swap(sup, nextSup);
				contSup++;
			}
		}
		if(v[i].second==inf) {
			if(indexInf==-1 || v[indexInf].first < v[i].first) {
				indexInf = i;
				swap(inf, nextInf);
				contInf++;
			}
		}
	}
	if(contInf>contSup) return contInf;
	else return contSup;
}

int main() {
	int n;

	while( cin >> n ) {
		vector< pair<int, int> > v(n);
		for(int i=0; i<n; i++) {
			cin >> v[i].first >> v[i].second;
		}
		sort(v.begin(), v.end());

		set<int> tentar;
		for(int i=0; i<n; i++) {
			tentar.insert( v[i].second-1 );
			tentar.insert( v[i].second+1 );
		}

		int maxN = 0;
		for(set<int>::iterator it=tentar.begin(); it!=tentar.end(); it++) {
			int atual = bestA(*it, v);
			if(atual>maxN) maxN = atual;
		}
		cout << maxN << endl;
	}
}