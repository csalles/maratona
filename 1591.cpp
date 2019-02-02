//1591 Dia da Vovó

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
	char mat[51][51];

	int t;
	cin >> t;
	while(t--) {
		int l, c;
		cin >> l >> c;

		for(int i=0; i<l; i++)
			cin >> mat[i];

		int p;
		cin >> p;

		for(int i=0; i<p; i++) {
			char s[51];
			cin >> s;

			if(s[1]=='\0') {
				int out = 0;
				for(int i=0; i<l; i++)
					for(int j=0; j<c; j++)
						if(mat[i][j]==s[0]) out++;
				cout << out << endl;
			}
			else {
				int out = 0;
				int sz = strlen(s);
				for(int i=0; i<l; i++)
					for(int j=0; j<c; j++) {
						if(mat[i][j]==s[0]) {
							
							if(i+sz-1<l) {
								bool ok = true;
								for(int k=0; k<sz; k++) {
									if(mat[i+k][j]!=s[k]) {
										ok = false;
										break;
									}
								}
								if(ok) out++;
							}

							if(j+sz-1<c) {
								bool ok = true;
								for(int k=0; k<sz; k++) {
									if(mat[i][j+k]!=s[k]) {
										ok = false;
										break;
									}
								}
								if(ok) out++;
							}

						}
					}
				//for i
				cout << out << endl;
			}
		}


	}
}
