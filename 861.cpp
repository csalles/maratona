//861
#include <iostream>
#include <vector>
#include <set>
using namespace std;

unsigned long long int cont;
/*
	0,14 => 7
	1,13 => 6, 8
	2,12 => 5, 7, 9
	3,11 => 4, 6, 8, 10
	4,10 => 3, 5, 7, 9, 11
	5,9 => 2, 4, 6, 8, 10, 12
	6,8 => 1, 3, 5, 7, 9, 11, 13
	7 => 0, 2, 4, 6, 8, 10, 12, 14
*/
vector< pair<int, int> > fillBishops(int n) {
	vector< pair<int,int> > ret;
	int start=n-1, end=n-1;
	for(int i=0; i<n; i++) {
		vector< int > bishops;
		for(int j=start; j<=end; j+=2) {
			pair<int,int> p(i, j);
			ret.push_back(p);
			if(p.first!=2*n-2-i) {
				p.first = 2*n-2-i;
				ret.push_back(p);
			}
		}
		start--;
		end++;
	}
	return ret;
}

void bt(vector< pair<int,int> > &bishops, 
	vector< bool > &used1,
	vector< bool > &used2,
	int index, int k)
{
	if(k==0) {
		cont++;
		return;
	}
	if(index>=bishops.size())
		return;

	int col1 = bishops[index].first;
	int col2 = bishops[index].second;
	bt(bishops, used1, used2, index+1, k);

	if(!used1[col1] && !used2[col2]) {
		used1[col1] = true;
		used2[col2] = true;
		bt(bishops, used1, used2, index+1, k-1);
		used1[col1] = false;
		used2[col2] = false;
	}
}


int main() {
	int n, k;

	for(n=1; n<=8; n++)
		for(k=1; k<=n*n; k++) {

			vector< pair<int,int> >bishops = fillBishops(n);
			vector< bool >used1(2*n, false);
			vector< bool >used2(2*n, false);		

			cont = 0;
			if(k<=2*n-2)
				bt(bishops, used1, used2, 0, k);
			cout << "if(n==" << n << "&&k==" << k << ") cout << " << cont << " << endl;" << endl;

		}
	return 0;
}

int main2() {
	int n, k;

//	main2();

	while(1) {
		cin >> n >> k;
		if(!n&&!k) break;
		
		if(n==1&&k==1) cout << 0 << endl;
		if(n==2&&k==1) cout << 4 << endl;
		if(n==2&&k==2) cout << 4 << endl;
		if(n==2&&k==3) cout << 0 << endl;
		if(n==2&&k==4) cout << 0 << endl;
		if(n==3&&k==1) cout << 9 << endl;
		if(n==3&&k==2) cout << 26 << endl;
		if(n==3&&k==3) cout << 26 << endl;
		if(n==3&&k==4) cout << 8 << endl;
		if(n==3&&k==5) cout << 0 << endl;
		if(n==3&&k==6) cout << 0 << endl;
		if(n==3&&k==7) cout << 0 << endl;
		if(n==3&&k==8) cout << 0 << endl;
		if(n==3&&k==9) cout << 0 << endl;
		if(n==4&&k==1) cout << 16 << endl;
		if(n==4&&k==2) cout << 92 << endl;
		if(n==4&&k==3) cout << 232 << endl;
		if(n==4&&k==4) cout << 260 << endl;
		if(n==4&&k==5) cout << 112 << endl;
		if(n==4&&k==6) cout << 16 << endl;
		if(n==4&&k==7) cout << 0 << endl;
		if(n==4&&k==8) cout << 0 << endl;
		if(n==4&&k==9) cout << 0 << endl;
		if(n==4&&k==10) cout << 0 << endl;
		if(n==4&&k==11) cout << 0 << endl;
		if(n==4&&k==12) cout << 0 << endl;
		if(n==4&&k==13) cout << 0 << endl;
		if(n==4&&k==14) cout << 0 << endl;
		if(n==4&&k==15) cout << 0 << endl;
		if(n==4&&k==16) cout << 0 << endl;
		if(n==5&&k==1) cout << 25 << endl;
		if(n==5&&k==2) cout << 240 << endl;
		if(n==5&&k==3) cout << 1124 << endl;
		if(n==5&&k==4) cout << 2728 << endl;
		if(n==5&&k==5) cout << 3368 << endl;
		if(n==5&&k==6) cout << 1960 << endl;
		if(n==5&&k==7) cout << 440 << endl;
		if(n==5&&k==8) cout << 32 << endl;
		if(n==5&&k==9) cout << 0 << endl;
		if(n==5&&k==10) cout << 0 << endl;
		if(n==5&&k==11) cout << 0 << endl;
		if(n==5&&k==12) cout << 0 << endl;
		if(n==5&&k==13) cout << 0 << endl;
		if(n==5&&k==14) cout << 0 << endl;
		if(n==5&&k==15) cout << 0 << endl;
		if(n==5&&k==16) cout << 0 << endl;
		if(n==5&&k==17) cout << 0 << endl;
		if(n==5&&k==18) cout << 0 << endl;
		if(n==5&&k==19) cout << 0 << endl;
		if(n==5&&k==20) cout << 0 << endl;
		if(n==5&&k==21) cout << 0 << endl;
		if(n==5&&k==22) cout << 0 << endl;
		if(n==5&&k==23) cout << 0 << endl;
		if(n==5&&k==24) cout << 0 << endl;
		if(n==5&&k==25) cout << 0 << endl;
		if(n==6&&k==1) cout << 36 << endl;
		if(n==6&&k==2) cout << 520 << endl;
		if(n==6&&k==3) cout << 3896 << endl;
		if(n==6&&k==4) cout << 16428 << endl;
		if(n==6&&k==5) cout << 39680 << endl;
		if(n==6&&k==6) cout << 53744 << endl;
		if(n==6&&k==7) cout << 38368 << endl;
		if(n==6&&k==8) cout << 12944 << endl;
		if(n==6&&k==9) cout << 1600 << endl;
		if(n==6&&k==10) cout << 64 << endl;
		if(n==6&&k==11) cout << 0 << endl;
		if(n==6&&k==12) cout << 0 << endl;
		if(n==6&&k==13) cout << 0 << endl;
		if(n==6&&k==14) cout << 0 << endl;
		if(n==6&&k==15) cout << 0 << endl;
		if(n==6&&k==16) cout << 0 << endl;
		if(n==6&&k==17) cout << 0 << endl;
		if(n==6&&k==18) cout << 0 << endl;
		if(n==6&&k==19) cout << 0 << endl;
		if(n==6&&k==20) cout << 0 << endl;
		if(n==6&&k==21) cout << 0 << endl;
		if(n==6&&k==22) cout << 0 << endl;
		if(n==6&&k==23) cout << 0 << endl;
		if(n==6&&k==24) cout << 0 << endl;
		if(n==6&&k==25) cout << 0 << endl;
		if(n==6&&k==26) cout << 0 << endl;
		if(n==6&&k==27) cout << 0 << endl;
		if(n==6&&k==28) cout << 0 << endl;
		if(n==6&&k==29) cout << 0 << endl;
		if(n==6&&k==30) cout << 0 << endl;
		if(n==6&&k==31) cout << 0 << endl;
		if(n==6&&k==32) cout << 0 << endl;
		if(n==6&&k==33) cout << 0 << endl;
		if(n==6&&k==34) cout << 0 << endl;
		if(n==6&&k==35) cout << 0 << endl;
		if(n==6&&k==36) cout << 0 << endl;
		if(n==7&&k==1) cout << 49 << endl;
		if(n==7&&k==2) cout << 994 << endl;
		if(n==7&&k==3) cout << 10894 << endl;
		if(n==7&&k==4) cout << 70792 << endl;
		if(n==7&&k==5) cout << 282248 << endl;
		if(n==7&&k==6) cout << 692320 << endl;
		if(n==7&&k==7) cout << 1022320 << endl;
		if(n==7&&k==8) cout << 867328 << endl;
		if(n==7&&k==9) cout << 389312 << endl;
		if(n==7&&k==10) cout << 81184 << endl;
		if(n==7&&k==11) cout << 5792 << endl;
		if(n==7&&k==12) cout << 128 << endl;
		if(n==7&&k==13) cout << 0 << endl;
		if(n==7&&k==14) cout << 0 << endl;
		if(n==7&&k==15) cout << 0 << endl;
		if(n==7&&k==16) cout << 0 << endl;
		if(n==7&&k==17) cout << 0 << endl;
		if(n==7&&k==18) cout << 0 << endl;
		if(n==7&&k==19) cout << 0 << endl;
		if(n==7&&k==20) cout << 0 << endl;
		if(n==7&&k==21) cout << 0 << endl;
		if(n==7&&k==22) cout << 0 << endl;
		if(n==7&&k==23) cout << 0 << endl;
		if(n==7&&k==24) cout << 0 << endl;
		if(n==7&&k==25) cout << 0 << endl;
		if(n==7&&k==26) cout << 0 << endl;
		if(n==7&&k==27) cout << 0 << endl;
		if(n==7&&k==28) cout << 0 << endl;
		if(n==7&&k==29) cout << 0 << endl;
		if(n==7&&k==30) cout << 0 << endl;
		if(n==7&&k==31) cout << 0 << endl;
		if(n==7&&k==32) cout << 0 << endl;
		if(n==7&&k==33) cout << 0 << endl;
		if(n==7&&k==34) cout << 0 << endl;
		if(n==7&&k==35) cout << 0 << endl;
		if(n==7&&k==36) cout << 0 << endl;
		if(n==7&&k==37) cout << 0 << endl;
		if(n==7&&k==38) cout << 0 << endl;
		if(n==7&&k==39) cout << 0 << endl;
		if(n==7&&k==40) cout << 0 << endl;
		if(n==7&&k==41) cout << 0 << endl;
		if(n==7&&k==42) cout << 0 << endl;
		if(n==7&&k==43) cout << 0 << endl;
		if(n==7&&k==44) cout << 0 << endl;
		if(n==7&&k==45) cout << 0 << endl;
		if(n==7&&k==46) cout << 0 << endl;
		if(n==7&&k==47) cout << 0 << endl;
		if(n==7&&k==48) cout << 0 << endl;
		if(n==7&&k==49) cout << 0 << endl;
		if(n==8&&k==1) cout << 64 << endl;
		if(n==8&&k==2) cout << 1736 << endl;
		if(n==8&&k==3) cout << 26192 << endl;
		if(n==8&&k==4) cout << 242856 << endl;
		if(n==8&&k==5) cout << 1444928 << endl;
		if(n==8&&k==6) cout << 5599888 << endl;
		if(n==8&&k==7) cout << 14082528 << endl;
		if(n==8&&k==8) cout << 22522960 << endl;
		if(n==8&&k==9) cout << 22057472 << endl;
		if(n==8&&k==10) cout << 12448832 << endl;
		if(n==8&&k==11) cout << 3672448 << endl;
		if(n==8&&k==12) cout << 489536 << endl;
		if(n==8&&k==13) cout << 20224 << endl;
		if(n==8&&k==14) cout << 256 << endl;
		if(n==8&&k==15) cout << 0 << endl;
		if(n==8&&k==16) cout << 0 << endl;
		if(n==8&&k==17) cout << 0 << endl;
		if(n==8&&k==18) cout << 0 << endl;
		if(n==8&&k==19) cout << 0 << endl;
		if(n==8&&k==20) cout << 0 << endl;
		if(n==8&&k==21) cout << 0 << endl;
		if(n==8&&k==22) cout << 0 << endl;
		if(n==8&&k==23) cout << 0 << endl;
		if(n==8&&k==24) cout << 0 << endl;
		if(n==8&&k==25) cout << 0 << endl;
		if(n==8&&k==26) cout << 0 << endl;
		if(n==8&&k==27) cout << 0 << endl;
		if(n==8&&k==28) cout << 0 << endl;
		if(n==8&&k==29) cout << 0 << endl;
		if(n==8&&k==30) cout << 0 << endl;
		if(n==8&&k==31) cout << 0 << endl;
		if(n==8&&k==32) cout << 0 << endl;
		if(n==8&&k==33) cout << 0 << endl;
		if(n==8&&k==34) cout << 0 << endl;
		if(n==8&&k==35) cout << 0 << endl;
		if(n==8&&k==36) cout << 0 << endl;
		if(n==8&&k==37) cout << 0 << endl;
		if(n==8&&k==38) cout << 0 << endl;
		if(n==8&&k==39) cout << 0 << endl;
		if(n==8&&k==40) cout << 0 << endl;
		if(n==8&&k==41) cout << 0 << endl;
		if(n==8&&k==42) cout << 0 << endl;
		if(n==8&&k==43) cout << 0 << endl;
		if(n==8&&k==44) cout << 0 << endl;
		if(n==8&&k==45) cout << 0 << endl;
		if(n==8&&k==46) cout << 0 << endl;
		if(n==8&&k==47) cout << 0 << endl;
		if(n==8&&k==48) cout << 0 << endl;
		if(n==8&&k==49) cout << 0 << endl;
		if(n==8&&k==50) cout << 0 << endl;
		if(n==8&&k==51) cout << 0 << endl;
		if(n==8&&k==52) cout << 0 << endl;
		if(n==8&&k==53) cout << 0 << endl;
		if(n==8&&k==54) cout << 0 << endl;
		if(n==8&&k==55) cout << 0 << endl;
		if(n==8&&k==56) cout << 0 << endl;
		if(n==8&&k==57) cout << 0 << endl;
		if(n==8&&k==58) cout << 0 << endl;
		if(n==8&&k==59) cout << 0 << endl;
		if(n==8&&k==60) cout << 0 << endl;
		if(n==8&&k==61) cout << 0 << endl;
		if(n==8&&k==62) cout << 0 << endl;
		if(n==8&&k==63) cout << 0 << endl;
		if(n==8&&k==64) cout << 0 << endl;
		
	}
	return 0;
}
