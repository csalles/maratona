//1024


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

string cripto(string s) {
	string ret = s;
	//cout << "{" << ret << "}" << endl;
	for(int i=0; i<ret.size(); i++)
		if( (ret[i]>='a' && ret[i]<='z') ||
			(ret[i]>='A' && ret[i]<='Z') )
			ret[i] = ret[i]+3;
	//cout << "[ " << ret << " ]" << endl;
	for(int i=0; i<ret.size()/2; i++)
		swap(ret[i], ret[ret.size()-1-i]);
	//cout << "[[ " << ret << " ]]" << endl;
	for(int i=ret.size()/2; i<ret.size(); i++)
		ret[i]--;
	return ret;
}

int main() {
	int n;
	string line;
	getline(cin, line);
	n = atoi(line.c_str());

	while(n--) {
		getline(cin, line);
		cout << cripto(line) << endl;
	}

}
