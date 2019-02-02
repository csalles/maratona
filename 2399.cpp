//2399 Campo Minado

#include <iostream>
using namespace std;

int main() {

	int v[51];
	int n;

	cin >> n;
	for(int i=0; i<n; i++) cin >> v[i];

	for(int i=0; i<n; i++) {
		int c = 0;
		if(i>0 && v[i-1]==1) c++;
		if(v[i]==1) c++;
		if(i+1<n && v[i+1]==1) c++;
		cout << c << endl;
	}

	
}