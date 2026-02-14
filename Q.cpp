/*
1820ANKIT2029 (AGENTVEER)

g++ Q.cpp && ./a.exe < input.txt > output.txt && diff --color=always output.txt actualOutput.txt | less -R
*/

#include <bits/stdc++.h>
using namespace std;

// loop
#define FOR(i, x, n) for(int (i)=(x); (i)<(n); (i)++)
#define rFOR(i, x, n) for(int (i)=(x); (i)>=(n); (i)--)  // eg: x=n-1, x=0

// sort
#define srt(v) sort((v).begin(), (v).end())
#define srtR(v) sort(v.rbegin(), v.rend())

#define Left(p)     ((p)<<1)+1
#define Right(p)    ((p)<<1)+2

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
const double EPS = 1e-9;
const int inx[] = {0, 1, -1, 0};
const int iny[] = {1, 0, 0, -1};
const vector<string> stepDir = {"R","D","U","L"};
const int PrimeSize = 100001;

// bool cmp(pll &a, pll &b){
//     return (a.second - a.first)> (b.second - b.first);
// }

class segmentTreeAtLeastXAndJGreaterL {
    vl tree;
    int size;

    void build(int p, int L, int R, vl& a){
        if(L == R){
            if(L < (int)a.size()) tree[p] = a[L]; 
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        tree[p] = max(tree[Left(p)], tree[Right(p)]);
    }

    void pointUpdate(int p, int L, int R, int idx, int v){
        if(L == R){tree[p] = v; return;}

        int mid = L + ((R-L)>>1);
        if(idx <= mid) pointUpdate(Left(p), L, mid, idx, v);
        else pointUpdate(Right(p), mid+1, R, idx, v);

        tree[p] = max(tree[Left(p)], tree[Right(p)]);
    }

    int find(int p, int L, int R, ll x, int l){
        if(R < l || tree[p] < x) return -1;

        if(L == R) return L;

        int mid = L + ((R - L) >> 1);

        int res = find(Left(p), L, mid, x, l);
        if(res != -1) return res;

        return find(Right(p), mid+1, R, x, l);
    }


public:
    segmentTreeAtLeastX(vl &a){
        int n = a.size();
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size, INT64_MIN);
        build(0, 0, size-1, a);
    }

    void pointUpdate(int idx, ll v){ pointUpdate(0, 0, size-1, idx, v);}
    int find(ll x, int l) {return find(0, 0, size-1, x, l);}
};


void solve(){
	int n, m;
    cin >> n >> m;
    vl a(n);
    for(ll &i: a) cin >> i;

    segmentTreeAtLeastX st(a);

    int type, i, v, l; ll x;
    while(m--){
        cin >> type;
        if(type == 1){
            cin >> i >> v;
            st.pointUpdate(i, v);
        }
        else{
            cin >> x >> l;
            cout << st.find(x, l) << endl;
        }
    }
    
}

int main(){
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
