
#include <string>
#include <iostream>
using namespace std;


string dobro(string n) {
	int vaium = 0;
	string ret;

	for(int i=n.size()-1; i>=0; i--) {
		int d = (n[i]-'0')*2 + vaium;
		vaium = d/10;
		d = d%10;
		ret = (char)('0'+d) + ret;
	}
	if(vaium) ret = '1' + ret;
	return ret;

}

int main() {
	long long int n;
	cin >> n;

	long long int f = 1;
	f += (n*(n-1))/2;
	f += (n*(n-1)*(n-2)*(n-3))/(4*3*2*1);
	cout << f << endl;
}