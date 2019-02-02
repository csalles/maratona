//1477

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;
/*
int n;
long int m;
int last[100010];
int play[100010];

#define MFUNC(a) ( (a)==2 ? 0 : (a)+1 )

void printConsult(int left, int right) {
	int cont[3] = {0,0,0};

	for(int bg=1; last[bg]!=-1; bg=last[bg]+1) {
		if(bg>right) break;
		if(last[bg]<left) continue;
		cont[ play[bg] ] += (min(right, last[bg]) - max(bg, left) + 1);
	}

	printf("%d %d %d\n", cont[0], cont[1], cont[2]);
}

void change(int left, int right) {
	for(int bg=1; last[bg]!=-1; bg=last[bg]+1) {
		if(bg>right) break;
		if(last[bg]<left) continue;
		if(left==bg) { //starting a change interval in bg
			if(right>=last[bg]) {
				play[bg] = MFUNC( play[bg] );
			}
			else {
				int oldLast = last[bg];
				int oldPlay = play[bg];
				play[bg] = MFUNC( oldPlay );
				last[bg] = right;
				play[right+1] = oldPlay;
				last[right+1] = oldLast;
				break;
			}
		}
		else if(left>bg && left<=last[bg]) { //starting a change interval into bg
			int oldLast = last[bg];
			int oldPlay = play[bg];
			
			last[bg] = left-1;
			play[bg] = oldPlay;
			if(right<oldLast) {
				last[left] = right;
				play[left] = MFUNC(oldPlay);
				last[right+1] = oldLast;
				play[right+1] = oldPlay;
				break;
			}
			else {
				last[left] = oldLast;
				play[left] = MFUNC(oldPlay);
				bg = left;
			}
		}
		else { //starting into interval
			int oldLast = last[bg];
			int oldPlay = play[bg];
			if(right<last[bg]) {
				last[bg] = right;
				play[bg] = MFUNC(oldPlay);
				last[right+1] = oldLast;
				play[right+1] = oldPlay;
				break;
			}
			else {
				play[bg] = MFUNC(oldPlay);
			}
		}
	}	
}

void debugIntervals() {
	for(int bg=1; last[bg]!=-1; bg=last[bg]+1) {
		printf("from %d to %d play %d\n", bg, last[bg], play[bg]);
	}
}

int main() {
	char cmd[5];
	int left, right;
	while( scanf("%d%ld", &n, &m)!=EOF ) {
		//printf("%d %ld\n", n, m);
		last[1] = n;
		play[1] = 0;
		last[n+1] = -1;
		for(int i=0; i<m; i++) {
			scanf("%s%d%d", cmd, &left, &right);
			if(cmd[0]=='C') {
				//printf("C %d %d\n", left, right);
				printConsult(left, right);
			}
			else { // M
				//printf("M %d %d\n", left, right);
				change(left, right);
				//debugIntervals();			
			}
		}
		printf("\n");
	}
}
*/


/*
version 2

#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int n;
long int m;

int hMat[20][100010];
int eMat[20][100010];
int rMat[20][100010];

map< pair<int, int>, int > hMemo;
map< pair<int, int>, int > eMemo;
map< pair<int, int>, int > rMemo;

void fill(int left, int right) {
	if(left<=right) {
		pair<int,int> p(left,right);
		hMemo[p] = right-left+1;
		eMemo[p] = 0;
		rMemo[p] = 0;
	}
	
	if(left<right) {
		int mid = (left+right)/2;
		fill(left, mid);
		fill(mid+1, right);
	}
}

int h, e, r;
void C(int left, int right, int limEsq, int limDir) {
	//[left, right]
	if(left>limDir) return;
	if(right<limEsq) return;

	//printf("* C %d %d\n", limEsq, limDir);

	if(limEsq>=left && limDir<=right) { //[limEsq, limDir] into [esq,dir]
		pair<int,int>p(limEsq, limDir);
		h += hMemo[p];
		e += eMemo[p];
		r += rMemo[p];
	}
	else {
		int mid = (limEsq+limDir)/2;
		//[limEsq, mid]
		C(left, right, limEsq, mid);
		C(left, right, mid+1, limDir);
		//[mid+1, limDir]
	}
}

void M(int left, int right, int limEsq, int limDir) {
	
	if(limEsq>limDir) return;

	//[left, right]
	if(left>limDir) return;
	if(right<limEsq) return;

	pair<int,int> p(limEsq, limDir);
	//printf("**M %d %d h=%d e=%d r=%d\n", limEsq, limDir, hMemo[p], eMemo[p], rMemo[p]);

	if(limEsq==limDir) {
		int aux = rMemo[p];
		rMemo[p] = eMemo[p];
		eMemo[p] = hMemo[p];
		hMemo[p] = aux;
	}
	else if(limEsq<limDir) {
		int mid = (limEsq+limDir)/2;
		//[limEsq, mid]
		M(left, right, limEsq, mid);
		M(left, right, mid+1, limDir);
		//[mid+1, limDir]
		pair<int,int> pLeft(limEsq, mid);
		pair<int,int> pRight(mid+1, limDir);
		hMemo[p] = hMemo[pLeft] + hMemo[pRight];
		eMemo[p] = eMemo[pLeft] + eMemo[pRight];
		rMemo[p] = rMemo[pLeft] + rMemo[pRight];	
	}
}

void printAll(int left, int right) {
	pair<int,int> p(left, right);
	printf("P %d %d h=%d e=%d r=%d\n", left, right, hMemo[p], eMemo[p], rMemo[p]);
	if(left<right) {
		printAll(left, (left+right)/2);
		printAll((left+right)/2+1, right);
	}
}


int main() {
	char cmd[5];
	int left, right;
	while( scanf("%d%ld", &n, &m)!=EOF ) {
		hMemo.clear();
		eMemo.clear();
		rMemo.clear();
		fill(1, n);

		for(int i=0; i<m; i++) {
			scanf("%s%d%d", cmd, &left, &right);
			if(cmd[0]=='C') {
				h = e = r = 0;

				//printf("\n\n");
				//printAll(1, n);
				//printf("\n\n");

				//printf("C %d %d\n", left, right);
				C(left, right, 1, n);
				printf("%d %d %d\n", h, e, r);
			}
			else {
				//printf("M %d %d\n", left, right);
				M(left, right, 1, n);
			}	
		}	
		printf("\n");		
	}
}
*/


/*
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int n;
long int m;

int hMat[20][100010];
int eMat[20][100010];
int rMat[20][100010];

void fill(int left, int right, int level) {
	if(left<=right) {
		hMat[level][left] = right-left+1;
		eMat[level][left] = 0;
		rMat[level][left] = 0;
	}
	
	if(left<right) {
		int mid = (left+right)/2;
		fill(left, mid, level+1);
		fill(mid+1, right, level+1);
	}
}

int h, e, r;
void C(int left, int right, int limEsq, int limDir, int level) {
	//[left, right]
	if(left>limDir) return;
	if(right<limEsq) return;

	//printf("* C %d %d\n", limEsq, limDir);

	if(limEsq>=left && limDir<=right) { //[limEsq, limDir] into [esq,dir]
		h += hMat[level][limEsq];
		e += eMat[level][limEsq];
		r += rMat[level][limEsq];
	}
	else {
		int mid = (limEsq+limDir)/2;
		//[limEsq, mid]
		C(left, right, limEsq, mid, level+1);
		C(left, right, mid+1, limDir, level+1);
		//[mid+1, limDir]
	}
}

void M(int left, int right, int limEsq, int limDir, int level) {
	
	if(limEsq>limDir) return;

	//[left, right]
	if(left>limDir) return;
	if(right<limEsq) return;

	//printf("**M %d %d h=%d e=%d r=%d\n", limEsq, limDir, hMemo[p], eMemo[p], rMemo[p]);

	if(limEsq==limDir) {
		int aux = rMat[level][limEsq];
		rMat[level][limEsq] = eMat[level][limEsq];
		eMat[level][limEsq] = hMat[level][limEsq];
		hMat[level][limEsq] = aux;
	}
	else if(limEsq<limDir) {
		int mid = (limEsq+limDir)/2;
		//[limEsq, mid]
		M(left, right, limEsq, mid, level+1);
		M(left, right, mid+1, limDir, level+1);
		//[mid+1, limDir]
		hMat[level][limEsq] = hMat[level+1][limEsq] + hMat[level+1][mid+1];
		eMat[level][limEsq] = eMat[level+1][limEsq] + eMat[level+1][mid+1];
		rMat[level][limEsq] = rMat[level+1][limEsq] + rMat[level+1][mid+1];	
	}
}

int main() {
	char cmd[5];
	int left, right;
	while( scanf("%d%ld", &n, &m)!=EOF ) {
		fill(1, n, 0);

		for(int i=0; i<m; i++) {
			scanf("%s%d%d", cmd, &left, &right);
			if(cmd[0]=='C') {
				h = e = r = 0;

				//printf("\n\n");
				//printAll(1, n);
				//printf("\n\n");

				//printf("C %d %d\n", left, right);
				C(left, right, 1, n, 0);
				printf("%d %d %d\n", h, e, r);
			}
			else {
				//printf("M %d %d\n", left, right);
				M(left, right, 1, n, 0);
			}	
		}	
		printf("\n");		
	}
}
*/

#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int n;
long int m;

int hTree[2000010];
int eTree[2000010];
int rTree[2000010];
int lazy [2000010];

void build(int node, int start, int end) {
	if(start==end) {
		hTree[node] = 1;
		eTree[node] = 0;
		rTree[node] = 0;
		lazy[node]  = 0;
	}
	else {
		int mid = (start+end)/2;
		build(2*node, start, mid);
		build(2*node+1, mid+1, end);
		hTree[node] = hTree[2*node] + hTree[2*node+1];
		eTree[node] = eTree[2*node] + eTree[2*node+1];
		rTree[node] = rTree[2*node] + rTree[2*node+1];	
		lazy[node] = 0;	
	}
}

/*
//update ... no lazy propagation
void updateRange(int node, int start, int end, int l, int r) {
	// out of range
    if (start > end or start > r or end < l)
        return;

    // Current node is a leaf node
    if (start == end)
    {
        // Add the difference to current node
        int aux = rTree[node];
        rTree[node] = eTree[node];
        eTree[node] = mTree[node];
        mTree[node] = aux;
        return;
    }

    // If not a leaf node, recur for children.
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r);
    updateRange(node*2 + 1, mid + 1, end, l, r);

    // Use the result of children calls to update this node
	hTree[node] = hTree[2*node] + hTree[2*node+1];
	eTree[node] = eTree[2*node] + eTree[2*node+1];
	rTree[node] = rTree[2*node] + rTree[2*node+1];		
}
*/

void updateStrategy(int node) {
	int aux = rTree[node];
	rTree[node] = eTree[node];
	eTree[node] = hTree[node];
	hTree[node] = aux;	
}

void updateRange(int node, int start, int end, int l, int r)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        //int sz = (end - start + 1) * lazy[node];
        if(lazy[node]%3>0)
        	updateStrategy(node);
        
        if(lazy[node]%3>1)
	        updateStrategy(node);

        if(start != end)
        {
            lazy[node*2] += lazy[node];                  // Mark child as lazy
            lazy[node*2+1] += lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l and end <= r)
    {
        // Segment is fully within range
        updateStrategy(node);
        if(start != end)
        {
            // Not leaf node
            lazy[node*2]++;
            lazy[node*2+1]++;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r);   // Updating right child
	hTree[node] = hTree[2*node] + hTree[2*node+1];
	eTree[node] = eTree[2*node] + eTree[2*node+1];
	rTree[node] = rTree[2*node] + rTree[2*node+1];		
}

int humanResult, elephantResult, ratResult;

void queryRange(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        if(lazy[node]%3>0)
        	updateStrategy(node);
        
        if(lazy[node]%3>1)
	        updateStrategy(node);

       if(start != end)
        {
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l and end <= r) {            // Current segment is totally within range [l, r]
    	humanResult += hTree[node];
    	elephantResult += eTree[node];
    	ratResult += rTree[node];
    	return;
    }
    int mid = (start + end) / 2;
    queryRange(node*2, start, mid, l, r);         // Query left child
    queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    //h += hTree[node*2] + hTree[node*2+1];
    //e += eTree[node*2] + eTree[node*2+1];
    //r += rTree[node*2] + rTree[node*2+1];
 }

int main() {
	char cmd[5];
	int left, right;
	while( scanf("%d%ld", &n, &m)!=EOF ) {
		build(1, 1, n);

		for(int i=0; i<m; i++) {
			scanf("%s%d%d", cmd, &left, &right);
			if(cmd[0]=='C') {
				humanResult = 0;
				elephantResult = 0;
				ratResult = 0;
				queryRange(1, 1, n, left, right);
				printf("%d %d %d\n", humanResult, elephantResult, ratResult);
			}
			else {
				//printf("M %d %d\n", left, right);
				updateRange(1, 1, n, left, right);
			}	
		}	
		printf("\n");		
	}
}

