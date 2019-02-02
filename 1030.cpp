//1030

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>	
using namespace std;

int main() {
	int n, m;
	int caseTotal, caseCount;

	cin >> caseTotal;
	for(caseCount=1; caseCount<=caseTotal; caseCount++) {
		cin >> n >> m;
		queue<int> q;
		for(int i=1; i<=n; i++)
			q.push(i);
		
		for(int i=0; i<n-1; i++) {
			for(int j=0; j<m-1; j++) {
				int atual = q.front();
				q.pop();
				q.push(atual);
			}
			q.pop();
		}
		cout << "Case " << caseCount << ": " << q.front() << endl;
	}


}