#include <stdio.h>
#include <string.h>

char s[10];
char out[10];

int bt(int index) {
	int c = out[index]-'0';
	int newIndex = index;

//printf("bt(%s)\n", out);

	while(c--) {
		newIndex++;
		if(out[newIndex]=='\0') newIndex=0;
	}
	if(out[newIndex]!='?') {
		if(newIndex!=0) return 0;
		int noneQuestions = 1;
		for(int i=0; out[i]!='\0'; i++)
			if(out[i]=='?') {
				noneQuestions=0;
				break;
			}
		return noneQuestions;
	}

	int hasDigit[10];
	for(int i=0; i<10; i++)
		hasDigit[i] = 0;
	for(int i=0; out[i]!='\0'; i++) {
		if(out[i]!='?') {
			hasDigit[ out[i]-'0' ] = 1;
		}
	}

/*
	printf("[%s]\n", out);
	for(int i=1; i<10; i++) {
		printf("hasDigit[%d]=%d\n", i, hasDigit[i]);
	}
*/

	for(char c='1'; c<='9'; c++) {
		if(!hasDigit[c-'0']) {
			int ok = 1;
			out[newIndex] = c;
			for(int i=0; i<=newIndex; i++) {
				if(out[i]=='?') break;
				if(out[i]<s[i]) ok=0;
				if(out[i]>s[i]) break;
			}
			if(ok && bt(newIndex)) {
				return 1;
			}
		}
	}
	return 0;
}

int main() {
   for(int casos=1; ;casos++) {
      scanf("%s", s);
      if(s[0]=='0') break;

      strcpy(out, "?????????");
      out[strlen(s)] = '\0';
      printf("Case %d: ", casos);

      int ok = 0;
      out[0] = s[0];
      while(out[0]<='9') {
	      if(bt( 0 )) {
	      	ok=1;
	      	break;
	      }
	      out[0]++;
      }
      if(!ok) {
         strcpy(out, "11111111");
         out[strlen(s)+1] = '\0';      	
      }
      printf("%s\n", out);
   }
}