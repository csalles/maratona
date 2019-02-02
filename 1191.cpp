//1191 Recuperação da Árvore

#include <iostream>
#include <string>
#include <map>
using namespace std;

string prefixo, infixo;

map<char, char> leftNode;
map<char, char> rightNode;

char search(int &index, string s) {
	char root =	prefixo[index++];
	if(index>=prefixo.size()) return root;

	int pos;
	for(pos=0; pos<s.size(); pos++) if(s[pos]==root) break;
	string l = pos-1<0 ? "" : s.substr(0, pos);
	string r = pos+1>=s.size() ? "" : s.substr(pos+1);

	//cout << "root = " << root << " " << infixo << " l=" << l << " r=" << r << endl;

	if(l.size()>0) leftNode[root] = search(index, l);
	if(r.size()>0) rightNode[root] = search(index, r);

	return root;
}

string posfixo(char c) {
	string ret = "";
	if(leftNode.count(c)) ret += posfixo(leftNode[c]);
	if(rightNode.count(c)) ret += posfixo(rightNode[c]);
	return ret + c;
}

int main() {
	while( cin >> prefixo >> infixo) {
		leftNode.clear();
		rightNode.clear();
		int index = 0;
		char root = search(index, infixo);
		cout << posfixo(root) << endl;
	}	
}
