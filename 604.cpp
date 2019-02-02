#include <stdio.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> WORDS;

char s[5];

#define isvowel(c) ((c)=='A'||(c)=='E'||(c)=='I'||(c)=='O'||(c)=='U'||(c)=='Y')

void bt(int index) {
	if(index>=4) {
		WORDS.push_back(string(s));
		return;
	}
	for(char c='A'; c<='Z'; c++) {
		int ok=1;
		s[index] = c;
		
		if(index==2 && isvowel(s[0]) 
		   && isvowel(s[1]) && isvowel(c))
			ok = 0;
		if(index==2 && !isvowel(s[0])
		   && !isvowel(s[1]) && !isvowel(c))
			ok = 0;

		if(index==3) {
			int vowels = 0;
			if(isvowel(s[0])) vowels++;
			if(isvowel(s[1])) vowels++;
			if(isvowel(s[2])) vowels++;
			if(isvowel(c)) vowels++;
			if(vowels!=2) ok=0;
		}

		if(ok) bt(index+1);
	}
}

int checkFromBoard(char b[4][4], int lin, int col, string s, int visited[4][4]) {
	if(s.size()==0) return 1;
	if(lin<0||lin>3||col<0||col>3) return 0;
	if(b[lin][col]!=s[0]) return 0;
	if(visited[lin][col]) return 0;
	visited[lin][col] = 1;

	if( checkFromBoard(b, lin-1, col-1, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin-1, col, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin-1, col+1, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin, col-1, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin, col+1, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin+1, col-1, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin+1, col, s.substr(1), visited) )
		return 1;
	if( checkFromBoard(b, lin+1, col+1, s.substr(1), visited) )
		return 1;

	visited[lin][col] = 0;
	return 0;
}

int haveWord(char b[4][4], string s) {
	int visited[4][4];
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			visited[i][j] = 0;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if( checkFromBoard(b, i, j, s, visited) ) return 1;
	return 0;
}

int main() {
	int first = 1;

	bt(0);

	/*
	for(int i=0; i<WORDS.size(); i++) {
		cout << WORDS[i] << endl;
	}
	*/

	char b1[4][4], b2[4][4];

	while(1) {
		for(int i=0; i<4; i++) {
			char s[10];
			for(int j=0; j<8; j++) {
				scanf("%s", s);
				if(s[0]=='#') return 0;
				if(j<4) b1[i][j] = s[0];
				else b2[i][j-4] = s[0];
			}
		}

		if(first) first=0;
		else cout << endl;

		int flag = 0;
		for(int i=0; i<WORDS.size(); i++) {
			/*if( haveWord(b1, WORDS[i]) && haveWord(b2,WORDS[i]) ) {
				cout << WORDS[i] << endl;
				flag = 1;
			}
			*/
		}
		if(!flag)
			cout << "There are no common words for this pair of boggle boards." << endl;
	}

}