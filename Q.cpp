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

class segmentTreeSum {
    vl sum;
    int size;

    void build(int p, int L, int R, vl& a){
        if(L == R){
            if(L < (int)a.size()) sum[p] = a[L]; 
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        sum[p] = sum[Left(p)] + sum[Right(p)];
    }

    void set(int p, int L, int R, int ind, int v){
        if(L == R) {sum[p] += v; return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        sum[p] = sum[Left(p)] + sum[Right(p)];
    }

    long long rangeSum(int p, int L, int R, int l, int r){
        if(L>=l && R<=r) return sum[p];      
        if(R < l || L > r) return 0;    

        int mid = L + ((R-L)>>1);

        return rangeSum(Left(p), L, mid, l, r) + rangeSum(Right(p), mid+1, R, l, r);
    }

public:
    segmentTreeSum(int n){
        size = 1;
        while(size < n) size *= 2;
        sum.assign(2*size, 0LL);
    }

    segmentTreeSum(vl& a) : segmentTreeSum((int)a.size()) {
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){ set(0, 0, size-1, ind, v); }
    long long rangeSum(int l, int r){ return rangeSum(0, 0, size-1, l, r);}
};


void solve(){
	int n, m;
    cin >> n;
    vl a(n);
    for(ll &i: a) cin >> i;

    segmentTreeSum st(n);

    for(int i=0; i<n; i++) {
        cout << st.rangeSum(0, n-1) - st.rangeSum(0, a[i]-1) << " ";
        st.set(a[i]-1, 1);
    }
    cout << "\n";
    
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
