//1934 Quebra-cabeça

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

#define MAXSIZE 101

int l, c;

long long int sumL[MAXSIZE];
long long int sumC[MAXSIZE];

vector< map<string, int> > occuVarL(MAXSIZE);
vector< map<string, int> > occuVarC(MAXSIZE);

map<string, long long int> varValue;

string m[MAXSIZE][MAXSIZE];

void resolve(string var, long long int val) {
	vector<string> nextToResolve;
	varValue[var] = val;
	for(int i=0; i<l; i++) {
		if(occuVarL[i].count(var)) {
			sumL[i] -= (val*occuVarL[i][var]);
			occuVarL[i].erase(var);
		}
	}
	for(int j=0; j<c; j++) {
		if(occuVarC[j].count(var)) {
			sumC[j] -= (val*occuVarC[j][var]);
			occuVarC[j].erase(var);
		}
	}
}

int main() {
	cin >> l >> c;

	for(int i=0; i<l; i++) {
		for(int j=0; j<c; j++){
			cin >> m[i][j];
			if(occuVarL[i].count(m[i][j])) {
				occuVarL[i][ m[i][j] ]++;
			}
			else {
				occuVarL[i][ m[i][j] ] = 1;
			}
			if(occuVarC[j].count(m[i][j])) {
				occuVarC[j][ m[i][j] ]++;
			}
			else {
				occuVarC[j][ m[i][j] ] = 1;
			}
		}
		cin >> sumL[i];
 	}
 	for(int j=0; j<c; j++)
 		cin >> sumC[j];

 	while(true) {
 		bool resolveAny =  false;
	 	for(int i=0; i<l; i++) {
	 		if(occuVarL[i].size()==1) {
	 			string var = occuVarL[i].begin()->first;
	 			int occu = occuVarL[i].begin()->second;
	 			resolve(var, sumL[i]/occu);
	 			resolveAny = true;
	 		}
	 	}
	 	for(int j=0; j<c; j++) {
	 		if(occuVarC[j].size()==1) {
	 			string var = occuVarC[j].begin()->first;
	 			int occu = occuVarC[j].begin()->second;
	 			resolve(var, sumC[j]/occu);
	 			resolveAny = true;
	 		}
	 	}
	 	if(!resolveAny) break;
	 	//else break;
	 }

	 for(map<string, long long int>::iterator it=varValue.begin(); it!=varValue.end(); it++ ) {
	 	cout << it->first << " " << it->second << endl;
	 }

}
