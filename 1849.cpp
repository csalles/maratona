//1849

#include <iostream>
#include <algorithm>
using namespace std;

int quad(int a, int b, int c, int d) {
	int l1 = min(a,c);
	int l2 = b+d;
	return min(l1, l2);
}

int main() {
	int ld, cd, lv, cv;
	cin >> ld >> cd >> lv >> cv;
	int q1 = quad(ld, cd, lv, cv);
	int q2 = quad(ld, cd, cv, lv);
	int q3 = quad(cd, ld, lv, cv);
	int q4 = quad(cd, ld, cv, lv);
	int out = max(q1, q2);
	out = max(out, q3);
	out = max(out, q4);
	cout << out*out << endl;
}
