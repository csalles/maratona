//2689

#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define ABS(a) ( (a)<0 ? -(a) : (a) )

int main() {
	int p;
	int m[3][3];

	cin >> p;

	while(p--) {
		map<int,int> dv;

		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				cin >> m[i][j];
		for(int i=0; i<3; i++) {
			int diff = ABS(m[i][0]-m[i][1]);
			if(dv.count(diff)) dv[diff]+=2;
			else dv[diff] = 2;			
			diff = ABS(m[i][2]-m[i][1]);
			if(dv.count(diff)) dv[diff]++;
			else dv[diff] = 1;
		}

		int maiorRepeticao = -1;
		for( map<int,int>::iterator it = dv.begin(); it!=dv.end(); it++) {
			if(maiorRepeticao==-1) maiorRepeticao = it->first;
			else if(it->second>dv[maiorRepeticao]) maiorRepeticao = it->first;
		}

		vector<int> output;
		for(int i=0; i<3; i++) {
			if(ABS(m[i][0]-m[i][1])!=maiorRepeticao && ABS(m[i][0]-m[i][2])!=maiorRepeticao )
					output.push_back(m[i][0]);
			if(ABS(m[i][1]-m[i][0])!=maiorRepeticao && ABS(m[i][1]-m[i][2])!=maiorRepeticao )
					output.push_back(m[i][1]);
			if(ABS(m[i][2]-m[i][0])!=maiorRepeticao && ABS(m[i][2]-m[i][1])!=maiorRepeticao )
					output.push_back(m[i][2]);
		}
		//cout << "-- maiorRepeticao = " << maiorRepeticao << endl;
		//cout << "-- freq = " << dv[maiorRepeticao] << endl;

		cout << "Possiveis maletas:";
		for(int i=0; i<output.size()-1; i++) {
			cout << " " << output[i] << ",";
		}
		if(output.size()>0)
			cout << " " << output[output.size()-1] << ";";
		cout << endl;

	}

}