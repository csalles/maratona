//1259


#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(int a, int b) {
	if(a%2!=b%2) return a%2==0;
	if(a%2==0) return a<b;
	else return a>b;
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);

	for(int i=0; i<n; i++){
		cin >> v[i];
	}
	sort(v.begin(), v.end(), cmp);
	for(int i=0; i<n; i++){
		cout << v[i] << endl;
	}

}