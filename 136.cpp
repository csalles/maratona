#include <iostream>
#include <map>
#include <set>
#include <queue>

using namespace std;

int main() {
	set<long int> descobertos;
	priority_queue<long int, vector<long int>, greater<long int>  > q;

	long int atual = 1;
	descobertos.insert(1);
	q.push(1);

	for(int i=0; i<1500; i++) {
		atual = q.top();
		q.pop();

		if(descobertos.count(atual*2)==0) {
			descobertos.insert(atual*2);
			q.push(atual*2);
		}

		if(descobertos.count(atual*3)==0) {
			descobertos.insert(atual*3);
			q.push(atual*3);
		}

		if(descobertos.count(atual*5)==0) {
			descobertos.insert(atual*5);
			q.push(atual*5);
		}

	}

	cout << "The 1500'th ugly number is " << atual << "." << endl;
	//cout << "859963392";
}