//1124

#include <iostream>
#include <cmath>
using namespace std;

#define MOD(a) ( (a)<0 ? -(a) : (a) )

double dist(double x1, double y1, double x2, double y2) {
	double dx = (x1-x2)*(x1-x2);
	double dy = (y1-y2)*(y1-y2);
	return sqrt(dx + dy);
}

bool gtEq(double a, double b) {
	if(a>b) return true;
	else if(a<b) return false;
	if( MOD(a-b)<0.0001 ) return true;
	else return false;
}

int main() {
	int l, c, r1, r2;
	while(1) {
		cin >> l >> c >> r1 >> r2;
		if(!l&&!c&&!r1&&!r2) break;

		if(2*r1>l || 2*r1>c || 2*r2>l || 2*r2>c ) {
			cout << "N" << endl;
			continue;
		}

		double d = dist( (double)r1, (double)r1, (double)l-r2, (double)c-r2 );
		if( gtEq(d, (double)(r1+r2) ) ) cout << "S" << endl;
		else cout << "N" << endl;
	}
}

