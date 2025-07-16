/*
1820ANKIT2029 (AGENTVEER)

g++ Q.cpp && ./a.exe < input.txt > output.txt && diff --color=always output.txt actualOutput.txt | less -R
*/

#include <bits/stdc++.h>
using namespace std;

// loop
#define for(i, x, n) for(int (i)=(x); (i)<(n); (i)++)
#define rfor(i, x, n) for(int (i)=(x); (i)>=(n); (i)--)  // eg: x=n-1, x=0

// sort
#define srt(v) sort((v).begin(), (v).end())
#define srtR(v) sort(v.rbegin(), v.rend())

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, int> pdi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<string> vs;

const ll MOD = 1e9 + 7;
const ll inf = 1e18;
const int inx[] = {0, 1, -1, 0};
const int iny[] = {1, 0, 0, -1};
const vector<string> stepDir = {"R","D","U","L"};

// bool cmp(pll &a, pll &b){
//     return (a.second - a.first)> (b.second - b.first);
// }

#define Left(p)     (p<<1)+1
#define Right(p)    (p<<1)+2

class segmentTreeRURQLazy {
    /*
        Segment Tree Range Update Range Query Lazy Propagation
    */

    int size;
    vl operations, values;

    ll NEUTRAL_ELEMENT = LLONG_MAX;
    ll NO_OPERATION = LLONG_MAX - 1;

    ll modify_op(ll a, ll b){
        if(b == NO_OPERATION) return a;
        return b;
    }

    ll query_op(ll a, ll b){
        return min(a, b);
    }

    void apply_mod_op(ll &a, ll b){
        a = modify_op(a, b);
    }

    void propagate(int p, int L, int R){
        if(L == R) return;

        int mid = L +  ((R-L)>>1);
        apply_mod_op(operations[Left(p)], operations[p]);
        apply_mod_op(values[Left(p)], operations[p]);
        apply_mod_op(operations[Right(p)], operations[p]);
        apply_mod_op(values[Right(p)], operations[p]);
        operations[p] = NO_OPERATION;
    }

    void modify(int p, int L, int R, int l, int r, int val){
        propagate(p, L, R);
        if(L > r || R < l) return;
        if(L >= l && R<=r){
            apply_mod_op(operations[p], val);
            apply_mod_op(values[p], val);
            return;
        }

        int mid = L + ((R-L)>>1);
        modify(Left(p), L, mid, l, r, val);
        modify(Right(p), mid+1, R, l, r, val);

        values[p] = query_op(values[Left(p)], values[Right(p)]);
        apply_mod_op(values[p], operations[p]);
    }

    ll query(int p, int L, int R, int l, int r){
        propagate(p, L, R);
        if(L > r || R < l) return NEUTRAL_ELEMENT;
        if(L >= l && R<=r) return values[p];

        int mid = L + ((R-L)>>1);
        ll a = query(Left(p), L, mid, l, r);
        ll b = query(Right(p), mid+1, R, l, r);
        ll ans = query_op(a, b);
        apply_mod_op(ans, operations[p]);
        return ans;
    }

    // void build(int p, int L, int R){
    //     if(L == R) {values[p] = 1; return;}

    //     int mid = L + ((R-L)>>1);
    //     build(Left(p), L, mid);
    //     build(Right(p), mid+1, R);

    //     values[p] = query_op(values[Left(p)], values[Right(p)]);
    // }

public:
    segmentTreeRURQLazy(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2 * size, 0LL);
        values.assign(2 * size, 0LL);
        // build(0, 0, size-1);
    }

    void modify(int l, int r, int v){modify(0, 0, size-1, l, r, v);}
    ll query(int l, int r){return query(0, 0, size-1, l, r);}
};

void solve(){
	int n, m;
    cin >> n >> m;

    segmentTreeRURQLazy st(n);

    int q, l, r, v, ind;
    for(i, 0, m){
        cin >> q;
        if(q == 1){
            cin >> l >> r >> v;
            st.modify(l, r-1, v);
        }
        else{
            cin >> l >> r;
            cout << st.query(l, r-1) << endl;
        }
    }
    
}

main(){
	ios::sync_with_stdio(0);
    ll t;

    t = 1;
    // cin >> t;
    while(t--)
        solve();
}

/*
g++ Q.cpp && ./a.exe < input.txt > output.txt && diff --color=always output.txt actualOutput.txt | less -R
*/
