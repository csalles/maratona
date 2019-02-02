//2852

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main() {
	char cifra[26][26];

	for(int i=0; i<26; i++) {
		for(int j=0; j<26; j++) {
			cifra[i][j] = (i+j)%26 + 'a';
		}
	}
	string pass;
	getline(cin, pass);
	int n;
	string line;
	getline(cin, line);
	n = atoi(line.c_str());

	while(n--) {
		getline(cin, line);
		bool beginWord = true;
		bool translate = false;
		int index = 0;
		for(int i=0; i<line.size(); i++) {
			if(line[i]==' ') 
				beginWord=true;
			else {
				if(beginWord) {
					beginWord = false;
					if(line[i]=='a'||line[i]=='e'||line[i]=='i'
						||line[i]=='o'||line[i]=='u') 
					{
						translate = false;
					}
					else {
						translate = true;
						line[i] = cifra[ line[i]-'a' ][ pass[index]-'a' ];
						index = (index+1)%pass.size();
					}
				}
				else {
					if(translate) {
						line[i] = cifra[ line[i]-'a' ][ pass[index]-'a' ];
						index = (index+1)%pass.size();				
					}
				}
			}
		}
		cout << line << endl;
	}

}