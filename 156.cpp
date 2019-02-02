
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

string ordena(string s) {
	int cont[26];
	int i, index;
	for(i=0; i<26; i++) cont[i]=0;
	for(i=0; i<s.size(); i++) {
		if(s[i]>='a' && s[i]<='z')
			index = s[i]-'a';
		else
			index = s[i]-'A';
		cont[index]++;
	}
	string ret;
	for(i=0; i<26; i++) {
		while(cont[i]>0) {
			ret = ret + (char)('a'+i);
			cont[i]--;
		}
	}
	return ret;
}

int main() {
	vector<string> v;
	while(1) {
		char str[81];
		scanf("%s", str);
		if(str[0]=='#') break;
		v.push_back(str);
	}
	sort(v.begin(), v.end());

	set<string> firstSet, againSet;

	vector<string> emOrdem(v.size());
	for(int i=0; i<v.size(); i++) {
		emOrdem[i] = ordena(v[i]);
		//printf("%s %s\n", v[i].c_str(), ordena(v[i]).c_str());
	}

	for(int i=0; i<v.size(); i++) {
		if(!firstSet.count(emOrdem[i])) {
			firstSet.insert(emOrdem[i]);
		}
		else {
			againSet.insert(emOrdem[i]);
		}
	}

	for(int i=0; i<v.size(); i++) {
		if(!againSet.count(emOrdem[i])) {
			printf("%s\n", v[i].c_str());
		}
	}

}