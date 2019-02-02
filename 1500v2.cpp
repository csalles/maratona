#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

const int DIG = 4;
const int BASE = 10000; // BASE**3 < 2**51 
const int TAM = 5;//2048;
struct bigint {
  int v[TAM], n;
  bigint(int x = 0): n(1) {
    memset(v, 0, sizeof(v));
    v[n++] = x;
    fix();
  }
  bigint(char * s): n(1) {
    memset(v, 0, sizeof(v));
    int sign = 1;
    while ( * s && !isdigit( * s))
      if ( * s++ == '-') sign *= -1;
    char * t = strdup(s), * p = t + strlen(t);
    while (p > t) {* p = 0;
      p = max(t, p - DIG);
      sscanf(p, "%d", & v[n]);
      v[n++] *= sign;
    }
    free(t);
    fix();
  }
  bigint & fix(int m = 0) {
    n = max(m, n);
    int sign = 0;
    for (int i = 1, e = 0; i <= (n || e) && (n = i); i++) {
      v[i] += e;
      e = v[i] / BASE;
      v[i] %= BASE;
      if (v[i]) sign = (v[i] > 0) ? 1 : -1;
    }
    for (int i = n - 1; i > 0; i--)
      if (v[i] * sign < 0) {
        v[i] += sign * BASE;
        v[i + 1] -= sign;
      }
    while (n && !v[n]) n--;
    return *this;
  }
  //int cmp(const int a, const int b) { return a-b;}
  int cmp(const bigint & x = 0) const {
    int i = max(n, x.n), t = 0;
    while (1)
      if ((t = (v[i] - x.v[i])) || i-- == 0) return t;
  }
  bool operator < (const bigint & x) const {
    return cmp(x) < 0;
  }
  bool operator == (const bigint & x) const {
    return cmp(x) == 0;
  }
  bool operator != (const bigint & x) const {
    return cmp(x) != 0;
  }
  operator string() const {
    ostringstream s;
    s << v[n];
    for (int i = n - 1; i > 0; i--) {
      s.width(DIG);
      s.fill('0');
      s << abs(v[i]);
    }
    return s.str();
  }
  friend ostream & operator << (ostream & o,
    const bigint & x) {
    return o << (string) x;
  }
  bigint & operator += (const bigint & x) {
    for (int i = 1; i <= x.n; i++) v[i] += x.v[i];
    return fix(x.n);
  }
  bigint operator + (const bigint & x) {
    return bigint( * this) += x;
  }
  bigint & operator -= (const bigint & x) {
    for (int i = 1; i <= x.n; i++) v[i] -= x.v[i];
    return fix(x.n);
  }
  bigint operator - (const bigint & x) {
    return bigint( * this) -= x;
  }
  bigint operator - () {
    bigint r = 0;
    return r -= * this;
  }
  void ams(const bigint & x, int m, int b) { 
  // *this += (x * m) << b; 
    for (int i = 1, e = 0; (i <= x.n || e) && (n = i + b); i++) { 
        v[i+b] += x.v[i] * m + e; e = v[i+b] / BASE; v[i+b] %= BASE; 
    }
  }
  bigint operator * (const bigint & x) const {
    bigint r;
    for (int i = 1; i <= n; i++) r.ams(x, v[i], i - 1);
    return r;
  }
  bigint & operator *= (const bigint & x) {
    return *this = * this * x;
  } // cmp(x / y) == cmp(x) * cmp(y); cmp(x % y) == cmp(x); 
  bigint div(const bigint& x) {
    if (x == 0) return 0; 
    bigint q; 
    q.n = max(n - x.n + 1, 0); 
    int d = x.v[x.n] * BASE + x.v[x.n-1]; 
    for (int i = q.n; i > 0; i--) { 
        int j = x.n + i - 1; 
        q.v[i] = int((v[j] * double(BASE) + v[j-1]) / d); 
        ams(x, -q.v[i], i-1); 
        if (i == 1 || j == 1) break; 
        v[j-1] += BASE * v[j]; 
        v[j] = 0; 
    }
    fix(x.n);
    return q.fix();
  }
bigint & operator /= (const bigint & x) {
  return *this = div(x);
}
bigint & operator %= (const bigint & x) {
  div(x);
  return *this;
}
bigint operator / (const bigint & x) {
  return bigint( * this).div(x);
}
bigint operator % (const bigint & x) {
  return bigint( * this) %= x;
}
bigint pow(int x) {
  if (x < 0) return ( * this == 1 || * this == -1) ? pow(-x) : 0;
  bigint r = 1;
  for (int i = 0; i < x; i++) r *= * this;
  return r;
}
bigint root(int x) {
  if (cmp() == 0 || (cmp() < 0 && x % 2 == 0)) return 0;
  if ( * this == 1 || x == 1) return *this;
  if (cmp() < 0) return -(- * this).root(x);
  bigint a = 1, d = * this;
  while (d != 1) {
    bigint b = a + (d /= 2);
    if (cmp(b.pow(x)) >= 0) {
      d += 1;
      a = b;
    }
  }
  return a;
}
};

#define MAXTREE 2000100

bigint lazy[MAXTREE];
bigint tree[MAXTREE];

void build(long int node, long int start, long int end)
{
    if(start == end)
    {
        // Leaf node will have a single element
        tree[node] = 0;
    }
    else
    {
        int mid = (start + end) / 2;
        // Recurse on the left child
        build(2*node, start, mid);
        // Recurse on the right child
        build(2*node+1, mid+1, end);
        // Internal node will have the sum of both of its children
        tree[node] = 0;//tree[2*node] + tree[2*node+1];
    }
}

void updateRange(long int node, long int start, long int end, long int l, long int r, long int val)
{
    bigint zero = 0;
    if(lazy[node].cmp(zero))
    { 
        // This node needs to be updated
        bigint interval = (end - start + 1);
        bigint mult = interval * lazy[node];
        tree[node] = tree[node] + mult;    // Update it
        if(start != end)
        {
            lazy[node*2] = lazy[node*2] + lazy[node];                  // Mark child as lazy
            lazy[node*2+1] = lazy[node*2+1] + lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l and end <= r)
    {
        // Segment is fully within range
        bigint interval = (end - start + 1);
        bigint infVal = val;
        bigint mult = interval * infVal;
        tree[node] = tree[node] + mult;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] = lazy[node*2] + infVal;
            lazy[node*2+1] = lazy[node*2+1] + infVal;
        }
        return;
    }
    long int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] + tree[node*2+1];        // Updating root with max value 
}

bigint queryRange(long int node, long int start, long int end, long int l, long int r)
{
    bigint zero = 0;
    if(start > end or start > r or end < l)
        return zero;         // Out of range
    
    if(lazy[node].cmp(zero))
    {
        // This node needs to be updated
        bigint interval = (end - start + 1);
        bigint mult = interval * lazy[node];
        tree[node] = tree[node] + mult;
        if(start != end)
        {
            lazy[node*2] = lazy[node*2] + lazy[node];         // Mark child as lazy
            lazy[node*2+1] = lazy[node*2+1] + lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l and end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    long int mid = (start + end) / 2;
    bigint p1 = queryRange(node*2, start, mid, l, r);         // Query left child
    bigint p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}

int main() {
    long int t;
    cin >> t;

    while(t--) {
        long int n, c;
        cin >> n >> c;

        build(1, 1, n);

        int tipo;
        long int p, q;

        for(long int i=0; i<c; i++) {
            cin >> tipo >> p >> q;
            if(tipo==0) {
                long int v;
                cin >> v;
                updateRange(1, 1, n, p, q, v);
            }
            else {
                cout << queryRange(1, 1, n, p, q) << endl;
                //cout << endl;
            }
        }
    }
}