
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#include <cstdio>

#define MAX 100100

int main(){
    
    // variáveis que vou usar
    char pilha[MAX], num;
        int topo, n, d, apagados, i;
    
    // enquanto houver entrada
        while(scanf("%d%d", &n, &d) && (n+d)){
        
        // a quantidade de números apagados começa zero
            apagados = 0;
        
        // para cada algarismo do número
            for(i = 0, topo = -1; i < n; i++){
            
            // leio seu valor
                scanf(" %c", &num);
            
            // enquanto houver algum número na pilha, ainda não houver d apagados
            // e o algarismo atual for maior que o topo da pilha
                    while(topo > -1 && apagados < d && num > pilha[topo]){
                
                // apago o número que está no topo da pilha
                topo--;
                
                // e aumento a quantidade de números apagados
                apagados++;
            }
            
            // se o tamanho da pilha for menor que n-d
            // insiro o  novo número na pilha
                    if(topo+1 < n-d) pilha[++topo] = num;
            }
        
        // por fim, adiciono '\0' ao fim da pilha
            pilha[++topo] = '\0';
        
        // para imprimi-la só com um printf
        printf("%s\n", pilha);
        }
    
        return 0;
}

/*
int main() {
    int n, d;
    char s[100010];
    int eraseCount;

    while(1) {
        cin >> n >> d;
        if(!n && !d) break;
        cin >> s;

        stack<char> st;
        eraseCount=0;
        st.push(s[0]);
        for(int i=1; i<n; i++) {
            if(st.size()<n-d) {

            }
            if(s[i]>st.top() && eraseCount<d) {
                st.pop();
                eraseCount++;
                st.push(s[i]);
            }
            else {
                if(st.size()<=n-d) st.push(s[i]);
            }
        }
 
        stack<char> out;
        while(!st.empty()) {
            out.push( st.top() );
            st.pop();
        }

        while(!out.empty()) {
            cout << out.top();
            out.pop();
        }
        cout << endl;

    }

}*/
