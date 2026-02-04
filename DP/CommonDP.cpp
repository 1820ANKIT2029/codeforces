#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<int, pii> pipii;

const ll MOD = 1e9 + 7;

class TravellingSellingProblem {
	public:
    int n;
    int graph[20][20];
    vector<vector<int>> dp;

    // Solves TSP using backtracking and bitmasking
    int Memo(int mask, int pos) {
        if (mask == (1 << n) - 1) { //  All cities visited, return to start (0)
            return graph[pos][0];
        }
        if (memo[mask][pos] != -1) return memo[mask][pos];
    
        int ans = INF;
        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) { // Check if the city has not been visited
                int newDist = graph[pos][city] + tsp(mask | (1 << city), city);
                ans = min(ans, newDist);
            }
        }
    
        return memo[mask][pos] = ans;
    }

    int Tabu() {
        int FULL = (1 << n);
        dp[1][0] = 0;  // only city 0 visited
    
        // Iterate over all masks
        for (int mask = 1; mask < FULL; mask++) {
            for (int u = 0; u < n; u++) { // if u is not in mask, skip
                if (!(mask & (1 << u))) continue;
    
                int prev_mask = mask ^ (1 << u);
                if (prev_mask == 0 && u != 0) continue;
    
                // Try all previous cities v
                for (int v = 0; v < n; v++) {
                    if (!(prev_mask & (1 << v))) continue;
                    dp[mask][u] = min(
                        dp[mask][u],
                        dp[prev_mask][v] + graph[v][u]
                    );
                }
            }
        }
    
        // Return to city 0
        int ans = INF;
        for (int u = 1; u < n; u++) {
            ans = min(ans, dp[FULL - 1][u] + graph[u][0]);
        }
        return ans;
    }

	void solve() {
		FAST_IO;
		cin >> n;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)   
                cin >> graph[i][j];

        dp.assign(1 << n, vector<int>(n, 1e9)); // for Memo -> -1 and for Tabu -> 1e9;

        cout << Tabu() << endl;
	}
};


/* templete
class _QuesNum {
	public:
	void solve() {
		FAST_IO;
		
	}
};
*/
void solve() {
	
	//auto start = chrono::high_resolution_clock::now();
	
	TravellingSellingProblem a;
	a.solve();
	
	/*
	auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " ms\n";
	*/
}

int main() {
	long long t = 1;
	//cin >> t;
	while(t--) solve();
}
