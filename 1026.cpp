//1026

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<bool> binario(unsigned long int n) {
	vector<bool> b(32);
	for(int i=0; i<32; i++) {
		if(n%2) b[i] = true;
		else b[i] = false;
		n /= 2;
	}
	return b;
}

vector<bool> Mofiz(vector<bool> a1, vector<bool> a2) {
	vector<bool> sum(32);
	for(int i=0; i<32; i++) {
		if( (a1[i]&&a2[i]) || (!a1[i]&&!a2[i]) )
			sum[i] = false;
		else
			sum[i] = true;
	}
	return sum;
}

unsigned long int converte(vector<bool> v) {
	unsigned long int ret = 0;
	unsigned long int casa = 1;
	for(int i=0; i<32; i++) {
		if(v[i]) ret += casa;
		casa *= 2;
	}
	return ret;
}

int main() {
	unsigned long int a, b;
	while(cin >> a >> b) {
		vector<bool> a1 = binario(a);
		vector<bool> a2 = binario(b);
		vector<bool> sum = Mofiz(a1, a2);
		cout << converte(sum) << endl;
	}
}
