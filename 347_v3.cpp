#include <stdio.h>
#include <string.h>

#include <vector>
using namespace std;

#define MAXDIGITS 8

vector<long> OUTPUT;

int DIGITS;
int V[MAXDIGITS];
int hasDigit[10];

int checkRoundNumber() {
	int visited[MAXDIGITS];
	int i, index, c;
	for(i=0; i<MAXDIGITS; i++) visited[i]=0;
	index = 0;
	for(i=0;i<DIGITS; i++) {
	   if(visited[index]) return 0;
	   visited[index] = 1;
	   c = V[index];
	   while(c--) {
	      index = (index+1)%DIGITS;
	   }
	}
	return index==0;
}

void bt(int index) {
	if(index>=DIGITS) {
		if(checkRoundNumber()) {
			long n = 0;
			for(int i=0; i<DIGITS; i++)
				n = 10*n + V[i];
			OUTPUT.push_back(n);
		}
		return;
	}
	for(int i=1; i<10; i++) {
		if(!hasDigit[i]) {
			hasDigit[i] = 1;
			V[index] = i;
			bt(index+1);
			hasDigit[i] = 0;
		}
	}
}

int main() {
	for(DIGITS=1; DIGITS<=MAXDIGITS; DIGITS++) {
		for(int i=0; i<10; i++)
			hasDigit[i]=0;
		bt(0);
	}

/*
	for(int i=0; i<OUTPUT.size(); i++)
		printf("%ld\n", OUTPUT[i]);
*/

	for(int casos=1; ;casos++) {
		long int n;
		scanf("%ld", &n);
		if(n==0) break;
		for(int i=0; i<OUTPUT.size(); i++) {
			if(OUTPUT[i]>=n) {
				printf("Case %d: %ld\n", casos, OUTPUT[i]);
				break;
			}
		}
	}

}