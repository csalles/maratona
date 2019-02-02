//624

#include <iostream>
#include <vector>
using namespace std;

int N;
int numMusics, cd[21];

int MAX;
vector<int> solution;

void bt(int index, int sum, vector<int> sol) {
	if(index>=numMusics) {
		if(sum>MAX) {
			solution = sol;
			MAX = sum;
		}
	}
	else {
		if(sum+cd[index]<=N) {
			vector<int> sol2 = sol;
			sol2.push_back(cd[index]);
			bt(index+1, sum+cd[index], sol2);
		}
		bt(index+1, sum, sol);
	}
}

int main() {
	while( cin >> N ) {
		cin >> numMusics;
		for(int i=0; i<numMusics; i++)
			cin >> cd[i];
		vector<int> sol;
		MAX = 0;
		bt(0, 0, sol);
		for(int i=0; i<solution.size(); i++)
			cout << solution[i] << " ";
		cout << "sum:" << MAX << endl;
	}
}
