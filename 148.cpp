#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//#define DEBUG

int sizeD;
char D[2001][21];
int C[2001][26];
int isInPhrase[2001];

int P[26];
char phrase[21];

char output[44];

/*
int P[27], sizeP;

void tryIt(int index) {

}

void bt(){
	memset(P, 0, 27);
	sizeP=0;
	for(int i=0; phrase[i]!='\0'; i++) {
		if(phrase[i]>='A' && phrase[i]<='Z') {
			P[ phrase[i]-'A' ]++;
			sizeP++;
		}
	}

	tryIt(0);

}
*/



int bt(int index) {
	int i, ok;

	ok = 1;
	for(i=0; i<26; i++) {
		if(P[i]<0)
		   return 0;
		if(P[i]!=0) {
		   ok=0;
		   break;
		}
	}
	if(ok) {
		printf("%s =%s\n", phrase, output);
		return 1;
	}

	if(index>=sizeD) return 0;

	// elimina os que ja aparecem
	if(isInPhrase[index]) {
		return bt(index+1);
	}

	int spacePosition = strlen(output);
	int occurs;
	for(occurs=1; ;occurs++) {
		int stop = 0;
		for(i=0; i<26; i++) {
			P[i] -= C[index][i];
			if(P[i]<0) stop=1;
		}
		strcat(output, " ");
		strcat(output, D[index]);
		if(stop) break;
/*
		int allZero = 1;
		for(i=0; i<26; i++) if(P[i]!=0) allZero=0;
		if(!allZero) bt(index);
*/
		bt(index+1);
		
	}
	//desfazendo
	for(i=0; i<26; i++) P[i] += occurs*C[index][i];
	output[spacePosition] = '\0';
	return bt(index+1);
}

void checkWordsInPhrase() {
	char s[21];
	int index, ss=0;

	for(int i=0; i<sizeD; i++)
		isInPhrase[i] = 0;

	for(index=0; ; index++) {
		char c = phrase[index];
		if(c>='A' && c<='Z')
 		   s[ss++] = c;
 		else {
 			s[ss++] = '\0';

#ifdef DEBUG
			printf("[%s]\n", s);
#endif

			for(int i=0; i<sizeD; i++) {
				int cmp = strcmp(s, D[i]);
				if(cmp==0) {
#ifdef DEBUG
					printf("\n   GOTCHA <%s>\n", s);
#endif
					isInPhrase[i] = 1;
				}
				//else if(cmp>0) break;
			}
			ss = 0;
			if(phrase[index]=='\0') break;
		}
	}
}

int main() {
	int i;

	for(sizeD=0; ;sizeD++) {
		gets(D[sizeD]);
		
		if(D[sizeD][0]=='#') break;
		for(i=0; i<26; i++)
			C[sizeD][i]=0;
		for(i=0; D[sizeD][i]!='\0'; i++)
			C[sizeD][ D[sizeD][i]-'A' ]++;
	}

#ifdef DEBUG
	for(i=0; i<sizeD; i++)
		printf("DIC <%s>\n", D[i]);
#endif

	while(1) {
		gets(phrase);
		if(phrase[0]=='#') break;

		for(i=0; i<26; i++)
			P[i]=0;
		for(i=0; phrase[i]!='\0'; i++)
			P[ phrase[i]-'A' ]++;

#ifdef DEBUG
		printf("PHRASE {%s}\n", phrase);
#endif
		checkWordsInPhrase();

		output[0] = '\0';
		bt(0);
	}

}