//#include <bits/stdc++.h>

#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>


#define MAXN 100100
#define MAXT 400400

using namespace std;
typedef long long int lli;

lli arvore[MAXT];
lli lazy[MAXT];
int n, q;

void build(int no, int i, int j){

    if(i == j){
        arvore[no] = 0;
        lazy[no] = 0;
        return;
    }

    int esq = 2*no;
    int dir = 2*no+1;
    int meio = (i+j)/2;

    build(esq,i,meio);
    build(dir,meio+1,j);
    arvore[no] = 0;
    lazy[no]   = 0;
}

void atualiza(int no, int i, int j, int A, int B, lli novo){

    int esq = 2*no;
    int dir = 2*no+1;
    int meio = (i+j)/2;

    if(lazy[no]){
        arvore[no] += (j-i+1)*lazy[no];
        if(i != j){
            lazy[esq] += lazy[no];
            lazy[dir] += lazy[no];
        }
        lazy[no] = 0;
    }

    if( i > j || i > B || j < A) return;

    if( A <= i && j <= B ){
        arvore[no] += novo*(j-i+1);
        if(i != j){
            lazy[esq] += novo;
            lazy[dir] += novo;
        }
    }
    else{
        atualiza(esq,i,meio,A,B,novo);
        atualiza(dir,meio+1,j,A,B,novo);
        arvore[no] = arvore[esq] + arvore[dir];
    }
}

lli consulta(int no, int i, int j, int A, int B){
    int esq = 2*no;
    int dir = 2*no+1;
    int meio = (i+j)/2;

    if(lazy[no]){
        arvore[no] += lazy[no]*(j-i+1);
        if( i != j){
            lazy[esq] += lazy[no];
            lazy[dir] += lazy[no];
        }
        lazy[no] = 0;
    }

    if( i > B || j < A) return 0;

    if( A <= i && j <= B){
        return arvore[no];
    }
    return consulta(esq, i, meio, A,B) + consulta(dir, meio+1, j, A,B);
}

int main (){
    int i;
    int p;

    cin >> p;

    while(p--){
        cin >> n >> q;
        build(1,1,n);

        int op;
        lli ax, bx, k;
        for(i = 1; i <= q; i++){
            cin >> op >> ax >> bx;
            if(ax > bx) swap(ax,bx);
            if(op == 0){
                cin >> k;
                atualiza(1,1,n,ax,bx,k);
            }
            else{
                cout << consulta(1,1,n,ax,bx) << endl;
            }
        }
    }

}
