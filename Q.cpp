/*
1820ANKIT2029 (AGENTVEER)

g++ Q.cpp && ./a.exe < input.txt > output.txt && diff --color=always output.txt actualOutput.txt | less -R
*/

#include <bits/stdc++.h>
using namespace std;

// loop
#define loop(x, n) for(int i=(x); i<(n); i++)
#define rloop(x, n) for(int i=(x); i>=(n); i--)  // eg: x=n-1, x=0

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
typedef vector<string> vs;

const ll mod = 1e9 + 7;
const ll inf = 1e18;
const int inx[] = {0, 1, -1, 0};
const int iny[] = {1, 0, 0, -1};
const vector<string> stepDir = {"R","D","U","L"};

bool cmp(pll &a, pll &b){
    return (a.second - a.first)> (b.second - b.first);
}

void solve(){
    int n, N;
    cin >> n;
    N = 2*n+10;
    vi a(n);
    vi index(N, 0);
    for(int i=0; i<n; i++) {cin >> a[i]; index[a[i]] = i+1;}

    sort(a.begin(), a.end());
    int cnt = 0;
    int tmp;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            tmp = a[i]*a[j];
            if(tmp > N) break;
            if(tmp == index[a[i]]+index[a[j]]) cnt++;
        }
    }

    cout << cnt << endl;
}

main(){
    ll t;

    t = 1;
    cin >> t;
    while(t--)
        solve();
}

/*
g++ Q.cpp && ./a.exe < input.txt > output.txt && diff --color=always output.txt actualOutput.txt | less -R
*/
