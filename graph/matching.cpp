#include <bits/stdc++.h>
using namespace std;

#define INF 1e9 + 2

enum {UNVISITED = -1, EXPLORED = -2, VISITED = -3};

vector<vector<pair<int, int>>> AL; // Adjecent List


// Bipartite Graph Check
bool isBipartite() {
    int s = 0;
    queue<int> q; q.push(s);
    vector<int> color(n, INF);
    color[s]  = 0;
    bool isBipartiteG = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(auto &[v, w]: AL[u]) {
            if(color[v] == INF) {
                color[v] = 1 - color[u];
                q.push(v);
            }
            else if (color[v] == color[u]) {
                isBipartiteG = false;
                break;
            }
        }
    }
    return isBipartiteG;
}

/* 
    Kuhn's Algorithm -> Unweighted Maximum Bipartite Matching
        - finds maximum matching in a bipartite graph using DFS-based augmenting paths.

    Augmenting Path:
        - A path that:
            1. starts from an unmatched left node
            2. ends at an unmatched right node
            3. alternates between:
                a. unmatched edge
                b. matched edge

    Step-by-Step Algorithm
    - For each left node u:
        1. Try DFS
        2. For each neighbor v:
            a. if v is free → match it
            b. else → try to rematch the current owner of v
        3. If rematching succeeds → assign v to u

    Time Complexity: O(E * V)
*/

vector<vector<int>> AL;
vector<int> match;
vector<bool> vis;

bool KuhnDfs(int u) {
    if (vis[u]) return false;
    vis[u] = true;

    for (int v : AL[u]) {
        if (match[v] == -1 || KuhnDfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int KuhnDfsmain() {
    int n, m; // left size, right size
    cin >> n >> m;

    AL.resize(n);
    match.assign(m, -1);

    int e; cin >> e;
    while (e--) {
        int u, v;
        cin >> u >> v;
        AL[u].push_back(v);
    }

    int maxMatching = 0;
    for (int u = 0; u < n; u++) {
        vis.assign(n, false);
        if (KuhnDfs(u)) maxMatching++;
    }

    cout << maxMatching << endl;
}

/* 
    Hopcroft–Karp Algorithm -> Unweighted Maximum Bipartite Matching
        - improves upon Kuhn's algorithm by finding multiple augmenting paths in parallel using BFS and DFS.

    PHASE:
        BFS → build shortest layers
        DFS → extract all shortest augmenting paths
    repeat until no more augmenting paths

    Time Complexity: O(sqrt(V) * E)
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<vector<int>> AL;
vector<int> pairU, pairV, dist;
int n, m;

bool bfs() {
    queue<int> q;

    for (int u = 0; u < n; u++) {
        if (pairU[u] == -1) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }

    bool foundAugPath = false;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : AL[u]) {
            if (pairV[v] != -1 && dist[pairV[v]] == INF) {
                dist[pairV[v]] = dist[u] + 1;
                q.push(pairV[v]);
            }
            if (pairV[v] == -1) {
                foundAugPath = true;
            }
        }
    }

    return foundAugPath;
}

bool dfs(int u) {
    for (int v : AL[u]) {
        if (pairV[v] == -1 ||
            (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
            
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }

    dist[u] = INF;
    return false;
}

int hopcroftKarp() {
    pairU.assign(n, -1);
    pairV.assign(m, -1);
    dist.resize(n);

    int matching = 0;

    while (bfs()) {
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1 && dfs(u)) {
                matching++;
            }
        }
    }

    return matching;
}

/*
    Hungarian Algorithm -> Weighted Maximum Bipartite Matching
        - finds maximum weight matching in a bipartite graph 
        - Assignment Problem: n workers, n jobs, cost matrix a[i][j] = cost of assigning worker i to job j

    Steps: 
        1. Row Reduction
            For each row: subtract the minimum element from all elements
        2. Column Reduction
            For each column: subtract the minimum element
        3. Cover all zeros with minimum lines
            Draw minimum number of lines (rows/columns) to cover all zeros.
            Case 1: If number of lines = n → optimal matching can be found among zeros
            Case 2: If number of lines < n → adjust the matrix:
        4. Adjust the Matrix
            Find the smallest uncovered value = k
            then, 
                Subtract k from all uncovered elements
                Add k to all elements covered by two lines
            Repeat from step 3 until optimal matching is found
    
    Time Complexity: O(n^3)
*/


#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// cost matrix is 1-indexed
int hungarian(vector<vector<int>> &a) {
    int n = a.size() - 1;
    vector<int> u(n+1), v(n+1), p(n+1), way(n+1);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        vector<int> minv(n+1, INF);
        vector<char> used(n+1, false);
        int j0 = 0;

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;

            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    return -v[0]; // minimum cost
}