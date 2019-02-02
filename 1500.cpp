//1500 Consultas Horríveis

//1477

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;

/*	bignum.c
	Implementation of large integer arithmetic: addition, subtraction,
		multiplication, and division.

	begun: February 7, 2002
	by: Steven Skiena
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved. 

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/


#include <stdio.h>

#define	MAXDIGITS	100		/* maximum length bignum */ 

#define PLUS		1		/* positive sign bit */
#define MINUS		-1		/* negative sign bit */

typedef struct {
        char digits[MAXDIGITS];         /* represent the number */
		int signbit;			/* 1 if positive, -1 if negative */ 
        int lastdigit;			/* index of high-order digit */
} bignum;

void zero_justify(bignum *n);
int compare_bignum(bignum *a, bignum *b);	

void print_bignum(bignum *n)
{
	int i;

	if (n->signbit == MINUS) printf("- ");
	for (i=n->lastdigit; i>=0; i--)
		printf("%c",'0'+ n->digits[i]);

	printf("\n");
}

void int_to_bignum(long long int s, bignum *n)
{
	int i;				/* counter */
	int t;				/* int to work with */

	if (s >= 0) n->signbit = PLUS;
	else n->signbit = MINUS;

	for (i=0; i<MAXDIGITS; i++) n->digits[i] = (char) 0;

	n->lastdigit = -1;

	t = s<0 ? -s: s;//abs(s);

	while (t > 0) {
		n->lastdigit ++;
		n->digits[ n->lastdigit ] = (t % 10);
		t = t / 10;
	}

	if (s == 0) n->lastdigit = 0;
}

void initialize_bignum(bignum *n)
{
	int_to_bignum(0,n);
}


int max(int a, int b)
{
	if (a > b) return(a); else return(b);
}

// /*	c = a +-/* b;	*/

void subtract_bignum(bignum *a, bignum *b, bignum *c);

void add_bignum(bignum *a, bignum *b, bignum *c)
{
	int carry;			/* carry digit */
	int i;				/* counter */

	initialize_bignum(c);

	if (a->signbit == b->signbit) c->signbit = a->signbit;
	else {
		if (a->signbit == MINUS) {
			a->signbit = PLUS;
			subtract_bignum(b,a,c);
			a->signbit = MINUS;
		} else {
                        b->signbit = PLUS;
                        subtract_bignum(a,b,c);
                        b->signbit = MINUS;
		}
		return;
	}

	c->lastdigit = max(a->lastdigit,b->lastdigit)+1;
	carry = 0;

	for (i=0; i<=(c->lastdigit); i++) {
		c->digits[i] = (char) (carry+a->digits[i]+b->digits[i]) % 10;
		carry = (carry + a->digits[i] + b->digits[i]) / 10;
	}

	zero_justify(c);
}


void subtract_bignum(bignum *a, bignum *b, bignum *c)
{
	int borrow;			/* has anything been borrowed? */
	int v;				/* placeholder digit */
	int i;				/* counter */

	initialize_bignum(c);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
                b->signbit = -1 * b->signbit;
                add_bignum(a,b,c);
                b->signbit = -1 * b->signbit;
		return;
        }

	if (compare_bignum(a,b) == PLUS) {
		subtract_bignum(b,a,c);
		c->signbit = MINUS;
		return;
	}

        c->lastdigit = max(a->lastdigit,b->lastdigit);
        borrow = 0;

        for (i=0; i<=(c->lastdigit); i++) {
		v = (a->digits[i] - borrow - b->digits[i]);
		if (a->digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}

                c->digits[i] = (char) v % 10;
        }

	zero_justify(c);
}

int compare_bignum(bignum *a, bignum *b)
{
	int i;				/* counter */

	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return(PLUS);
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return(MINUS);

	if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
	if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

	for (i = a->lastdigit; i>=0; i--) {
		if (a->digits[i] > b->digits[i]) return(MINUS * a->signbit);
		if (b->digits[i] > a->digits[i]) return(PLUS * a->signbit);
	}

	return(0);
}

void zero_justify(bignum *n)
{
	while ((n->lastdigit > 0) && (n->digits[ n->lastdigit ] == 0))
		n->lastdigit --;

        if ((n->lastdigit == 0) && (n->digits[0] == 0))
		n->signbit = PLUS;	/* hack to avoid -0 */
}


void digit_shift(bignum *n, int d)		/* multiply n by 10^d */
{
	int i;				/* counter */

	if ((n->lastdigit == 0) && (n->digits[0] == 0)) return;

	for (i=n->lastdigit; i>=0; i--)
		n->digits[i+d] = n->digits[i];

	for (i=0; i<d; i++) n->digits[i] = 0;

	n->lastdigit = n->lastdigit + d;
}



void multiply_bignum(bignum *a, bignum *b, bignum *c)
{
	bignum row;			/* represent shifted row */
	bignum tmp;			/* placeholder bignum */
	int i,j;			/* counters */

	initialize_bignum(c);

	row = *a;

	for (i=0; i<=b->lastdigit; i++) {
		for (j=1; j<=b->digits[i]; j++) {
			add_bignum(c,&row,&tmp);
			*c = tmp;
		}
		digit_shift(&row,1);
	}

	c->signbit = a->signbit * b->signbit;

	zero_justify(c);
}


void divide_bignum(bignum *a, bignum *b, bignum *c)
{
        bignum row;                     /* represent shifted row */
        bignum tmp;                     /* placeholder bignum */
	int asign, bsign;		/* temporary signs */
        int i,j;                        /* counters */

	initialize_bignum(c);

	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
        b->signbit = PLUS;

	initialize_bignum(&row);
	initialize_bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for (i=a->lastdigit; i>=0; i--) {
		digit_shift(&row,1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;
		while (compare_bignum(&row,b) != PLUS) {
			c->digits[i] ++;
			subtract_bignum(&row,b,&tmp);
			row = tmp;
		}
	}

	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}

void resto_bignum(bignum *a, bignum *b, bignum *c)
{
	bignum div;
	bignum mult;
	divide_bignum(a, b, &div);
	multiply_bignum(&div, b, &mult);
	subtract_bignum(a, &mult, c);
}

// a = b
void attrib_bignum(bignum *a, bignum *b)
{
	int i;
	a->lastdigit = b->lastdigit;
	a->signbit = b->signbit;
	for(i=0; i<MAXDIGITS; i++)
		a->digits[i] = b->digits[i];
}

/*
void mdc_bignum(bignum *a, bignum *b, bignum *c)
{
	if(compare_bignum(a,b)<0) mdc(b,a,c);
	
	bignum zero, resto;
	bignum *r = &resto;
	initialize_bignum(&zero);
	
	while(compare_bignum(b, &zero) != 0){
		resto_bignum(a, b, r);
		attrib_bignum(a, b);
		attrib_bignum(b, r);
	}
	attrib_bignum(a, c);
}
*/
//Algoritmo do MMC
/*void mmc_bignum(bignum *a, bignum *b, bignum *c){
	bignum mdc;
	bignum div;
	mdc_bignum(a, b, &mdc);
	divide_bignum(b, &mdc, &div);
	multiply_bignum(a, &div, c);
	//return a * (b / mdc(a, b));
}
*/
/*
int main()
{
	int a,b;
	bignum n1,n2,n3,zero;

	while (scanf("%d %d\n",&a,&b) != EOF) {
		printf("a = %d    b = %d\n",a,b);
		int_to_bignum(a,&n1);
		int_to_bignum(b,&n2);

		add_bignum(&n1,&n2,&n3);
		printf("addition -- ");
		print_bignum(&n3);

		printf("compare_bignum a ? b = %d\n",compare_bignum(&n1, &n2));

		subtract_bignum(&n1,&n2,&n3);
		printf("subtraction -- ");
		print_bignum(&n3);

                multiply_bignum(&n1,&n2,&n3);
		printf("multiplication -- ");
                print_bignum(&n3);

		int_to_bignum(0,&zero);
		if (compare_bignum(&zero, &n2) == 0)
			printf("division -- NaN \n");
                else {
			divide_bignum(&n1,&n2,&n3);
			printf("division -- ");
                	print_bignum(&n3);
		}
		printf("--------------------------\n");
	}
}
*/


int n;
int m;

#define MAXTREE 2000100

bignum tree[MAXTREE];
bignum lazy[MAXTREE];

void build(long int node, long int start, long int end) {
	initialize_bignum(&tree[node]);
	initialize_bignum(&lazy[node]);
	
	if(start!=end) {
		int mid = (start+end)/2;
		build(2*node, start, mid);
		build(2*node+1, mid+1, end);
	}
}


void updateRange(long int node, long int start, long int end, 
	             long int l, long int r, long long int v)
{
	bignum zero;
	initialize_bignum(&zero);

    if(compare_bignum(&lazy[node], &zero)!=0) //lazy[node] != 0)
    { 
        // This node needs to be updated
        //int sz = (end - start + 1) * lazy[node];
        bignum mul;
        bignum interval;
        int_to_bignum(end-start+1, &interval);
        multiply_bignum(&lazy[node], &interval, &mul);
        add_bignum(&tree[node], &mul, &interval);
        attrib_bignum(&tree[node], &interval);
        //tree[node] +=  lazy[node]*(unsigned long long int)(end-start+1);

        if(start != end)
        {
            bignum aux;
            add_bignum(&lazy[node*2], &lazy[node], &aux);
            attrib_bignum(&lazy[node*2], &aux);
            add_bignum(&lazy[node*2+1], &lazy[node], &aux);
            attrib_bignum(&lazy[node*2+1], &aux);
            //lazy[node*2] += lazy[node];                  // Mark child as lazy
            //lazy[node*2+1] += lazy[node];                // Mark child as lazy
        }
        initialize_bignum(&lazy[node]);
        //lazy[node] = 0;                                  // Reset it
    }
    if(start > end || start > r || end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l && end <= r)
    {
        // Segment is fully within range
        //tree[node] += (unsigned long long int)(end-start+1)*v;
        bignum interval;
        bignum val;
        bignum mul;
        bignum sum;
        int_to_bignum(end-start+1, &interval);
        int_to_bignum(v, &val);
        multiply_bignum(&interval, &val, &mul);
        add_bignum(&mul, &tree[node], &sum);
        attrib_bignum(&tree[node], &sum);
        if(start != end)
        {
            // Not leaf node
            bignum val;
            bignum sum;
            int_to_bignum(v, &val);
            add_bignum(&lazy[node*2], &val, &sum);
            attrib_bignum(&lazy[node*2], &sum);
            add_bignum(&lazy[node*2+1], &val, &sum);
            attrib_bignum(&lazy[node*2+1], &sum);
            //lazy[node*2] += v;
            //lazy[node*2+1] += v;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, v);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, v);   // Updating right child
	bignum sum;
	add_bignum(&tree[2*node], &tree[2*node+1], &sum);
	attrib_bignum(&tree[node], &sum);
//	tree[node] = tree[2*node] + tree[2*node+1];
}

//PAREI AQUI
void queryRange(long int node, long int start, long int end, long int l, long int r, bignum *result)
{
    if(start > end || start > r || end < l) {
        initialize_bignum(result);
        return;         // Out of range
    }
 	bignum zero;
	initialize_bignum(&zero);

    if(compare_bignum(&lazy[node], &zero)!=0) //lazy[node] != 0)
   	{
        // This node needs to be updated
       //tree[node] +=  lazy[node] * (unsigned long long int)(end-start+1);
       
       bignum interval;
       bignum mul;
       bignum sum;
       int_to_bignum(end-start+1, &interval);
       multiply_bignum(&lazy[node], &interval, &mul);
       add_bignum(&tree[node], &mul, &sum);
       attrib_bignum(&tree[node], &sum);

       if(start != end)
        {
        	bignum sum;
        	add_bignum(&tree[node*2], &lazy[node], &sum);
        	attrib_bignum(&tree[node*2], &sum);
            //lazy[node*2] += lazy[node];         // Mark child as lazy
            //lazy[node*2+1] += lazy[node];    // Mark child as lazy
        	add_bignum(&tree[node*2+1], &lazy[node], &sum);
        	attrib_bignum(&tree[node*2+1], &sum);	
        }
        //lazy[node] = 0;                 // Reset it
    	initialize_bignum(&lazy[node]);
    }
    if(start >= l && end <= r) {            // Current segment is totally within range [l, r]
    	attrib_bignum(result, &tree[node]);
    	return;
    	//return tree[node];
    }
    int mid = (start + end) / 2;
    //return queryRange(node*2, start, mid, l, r)         // Query left child
    //	+ queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
 	bignum p1;
 	bignum p2;
 	queryRange(node*2, start, mid, l, r, &p1);
 	queryRange(node*2 + 1, mid + 1, end, l, r, &p2);
 	add_bignum(&p1, &p2, result);
 }

int main() {
	int t;
	cin >> t;

	while(t--) {
		long int n, c;
		cin >> n >> c;
		build(1, 1, n);
		for(int i=0; i<c; i++) {
			int tipo;
			long int p, q;
			unsigned long long int v;
			cin >> tipo >> p >> q;
			if(tipo==0) {
				cin >> v;
				updateRange(1, 1, n, p, q, v);
			}
			else {
				bignum out;
				queryRange(1, 1, n, p, q, &out);
				print_bignum(&out);
			}
		}
	}
}



void updateRange(int node, int start, int end, int l, int r, int val)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];    // Update it
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
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] + tree[node*2+1];        // Updating root with max value 
}

int queryRange(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return 0;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];            // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l and end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);         // Query left child
    int p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}


