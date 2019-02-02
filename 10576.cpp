//10576
#include <iostream>
using namespace std;

long long int v[12];
long long int s, d;
long long int MAX;

void bt(int index) {

//cout << "bt(" << index << ")" << endl;

	if(index>=12) {
		long long int sum = 0;
		for(int i=0; i<12; i++) {
			sum += v[i];
		}
		if(sum>MAX) MAX=sum;
		return;
	}
	if(index-4>=0) {
		long long int sum  = 0;
		for(int i=1; i<=4; i++)
			sum+=v[index-i];
		if(sum+s<0) {
			v[index] = s;
			bt(index+1);
		}
		if(sum+d<0) {
			v[index] = d;
			bt(index+1);
		}
	}
	else {
		v[index] = s;
		bt(index+1);
		v[index] = d;
		bt(index+1);
	}
}

int main() {
	while( cin >> s >> d) {
		d = -d;
		MAX = -1;
		bt(0);
		if(MAX<0) cout << "Deficit" << endl;
		else cout << MAX << endl;
	}
}
