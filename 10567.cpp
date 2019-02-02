//10567

#include <iostream>
using namespace std;

#define INDEX(c) (((c)>='a'&&(c)<='z') ? (c)-'a' : (c)-'A'+26)

char S[1000001];

int sz[52];
int m[52][1000001];

char SS[102];

int myBinSearch(int index, int startPos) {
	int esq = 0;
	int dir = sz[index]-1;

//cout << "binSearch (" << index << " sz=" << sz[index] << " startPos = " << startPos
//	 << ")" << endl;

	while(esq<=dir) {
		int meio = (esq+dir)/2;
		//cout << "meio = " << meio << endl;
		if(meio==0) {
			if(m[index][0]>=startPos) return m[index][0];
			else esq=1;
		}
		if(m[index][meio]>=startPos && m[index][meio-1]<startPos) {
			return m[index][meio];
		}
		if(m[index][meio]<startPos) {
			esq=meio+1;
		}
		else {
			dir=meio-1;
		}
	}
	return -1;
}

int main() {
	int i;
	cin >> S;

	for(i=0; i<52; i++) sz[i]=0;

	for(i=0; S[i]!='\0'; i++) {
		int index = INDEX(S[i]);
		//cout << "[" << S[i] << "] = " << index << endl;
		m[index][ sz[index]++ ] = i;
	}

	/*
	for(i=0; i<52; i++) {
		for(int j=0; j<sz[i]; j++) {
			cout << "index[" << i << "] = " << m[i][j] << endl;
		}
	}
	*/
	

	int Q;

	cin >> Q;

	while(Q--) {
		cin >> SS;
		int first=-1, last=-1;
		int pos = 0;
		for(i=0; SS[i]!='\0'; i++) {
			int index = INDEX(SS[i]);
			int foundON = myBinSearch(index, pos);
			//cout << "foundON = " << foundON << endl; 
			//cout << "pos = " << pos << endl;
			//cout << "SS[i] = " << SS[i] << endl;
			if(foundON==-1) {
				first=last=-1;
				break;
			}
			else {
				if(first==-1) {first = last = foundON;}
				else last = foundON;
			}
			pos = foundON+1;
		}
		if(first==-1) {
			cout << "Not matched" << endl;
		}
		else {
			cout << "Matched " << first << " " << last << endl;
		}
	}

}