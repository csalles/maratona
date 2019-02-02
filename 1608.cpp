//1608 Bolos da Maria

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int t;
	cin >> t;

	while(t--) {
		long int d, i, b;
		cin >> d >> i >> b;

		vector<long int> cost(i);
		for(int j=0; j<i; j++)
			cin >> cost[j];

		long int cakeCost;
		long int minCost = -1;
		for(int j=0; j<b; j++) {
			cakeCost = 0;
			int qi;
			cin >> qi;
			while(qi--) {
				int index, qtd;
				cin >> index >> qtd;
				cakeCost += cost[index]*qtd;
			}
			if(j==0 || cakeCost<minCost) minCost = cakeCost;
		}

		cout << d/minCost << endl;
	}
}