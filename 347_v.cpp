#include <stdio.h>
#include <string.h>

char s[10];
char out[10];

int bt(int index) {
	int i;
	int noQuestion = 1;
	for(i=0; out[i]!='\0'; i++) {
		if(out[i]=='?') {
			noQuestion = 0;
			break;
		}
	}
	int c = out[index]-'0';
	while(c--) {
		index++;
		if(out[index]=='\0') index=0;
	}
	if(out[index]!='?')
		return noQuestion && index==0;

	//check for ?
	for(i=0; i<index ;i++) {
		if(out[i]=='?') break;
		if(out[i]<s[i]) return 0;
		if(out[i]>s[i]) break;
	}
	char digit = '1';
	if(i>=index)
		digit = s[index];
	while(digit<='9') {
		int okDigit = 1;
		for(int j=0; out[j]!='\0'; j++) {
			if(out[j]==digit) okDigit=0;
		}
		if(okDigit) {
		   out[index] = digit;
		   if(bt(index)) return 1;
		}
		digit++;
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