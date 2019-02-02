//10404
//10404 - Bachet's Game

#include <iostream>
using namespace std;


int main() {
	bool memo[1000001];
	int n, m;
	int plays[10];
	while( cin >> n ) {
		cin >> m;
		for(int i=0; i<m; i++)
			cin >> plays[i];
		
		//calculating memo
		memo[0] = true;
		for(int i=1; i<=n; i++) {
			memo[i] = false;
			for(int j=0; j<m; j++) {
				if(i-plays[j]==0) {
					memo[i] = true;
					break;
				}
				else if(i-plays[j]>0){
					if(memo[i-plays[j]]==false) {
						memo[i] = true;
						break;
					}
				}
			}
		}
		if( memo[n] )
			cout << "Stan wins" << endl;
		else
			cout << "Ollie wins" << endl;
	}
}