//11085 

#include <iostream>
using namespace std;

int v[8];
int MIN;

void bt(int index, int moves) {
	if(index>=8) {
		if(moves<MIN) MIN=moves;
	}
	else {
		int save = v[index];
		for(int pos=1; pos<=8; pos++) {
			v[index] = pos;

			//trying not to move
			bool attacked = false;
			for(int i=0; i<index; i++) {
				int diff = index-i;
				if(v[i]+diff==v[index] || v[i]-diff==v[index]
					|| v[i]==v[index]) 
				{
					attacked = true;
					break;
				}
			}
			if(!attacked) {
				if(pos == save)
					bt(index+1, moves);
				else
					bt(index+1, moves+1);
			}
		}
		v[index] = save;
	}
}

int main() {
	int casos = 1;
	while( cin >> v[0] ) {
		for(int i=1; i<8; i++)
			cin >> v[i];
		MIN = 8;
		bt(0, 0);
		cout << "Case " << casos << ": " << MIN << endl;
		casos++;
	}
}