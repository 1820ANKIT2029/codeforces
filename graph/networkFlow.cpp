#include <bits/stdc++.h>
using namespace std;

/**********
 Network Flow
 * Residual Graph 
    - Understand capacities, flow conservation, and the concept of a source (s) and sink (t)
 * Ford–Fulkerson Method
 * Edmonds–Karp Algorithm
 * Dinic’s Algorithm (CP Standard)
**********/

/*
    Core Entities
        - The Source (s): The producer. It has infinite supply. In-degree is 0.
        - The Sink (t): The consumer. It has infinite demand. Out-degree is 0.
        - Capacity (c(u, v)): The maximum "width" of a pipe between two junctions.
        - Flow (f(u, v)): The actual amount of "liquid" currently in that pipe.

    Principles
        - Capacity Constraint: 0 <= f(u, v) <= c(u, v). (Don't burst the pipe).
        - Flow Skew Symmetry: f(u, v) = -f(v, u). (Flow in one direction is negative flow in the opposite direction).
        - Flow Conservation: Σ f_{in} = Σ f_{out} for every node except s and t. (Nodes don't "leak" or "drink").

    Residual Graph: "Undo" Button
        - one line explain, why residual graph is needed
            - to allow algorithms to "undo" bad previous choices by pushing flow back a
            long reverse edges, ensuring the ability to find the true maximum flow
            
        - For each edge (u, v) with capacity c and flow f, we have:
            - A forward edge (u, v) with residual capacity c - f. 
                (remaining capacity)
            - A backward edge (v, u) with residual capacity f. 
                (how much we can cancel)

*/


/*
    Ford–Fulkerson Method

    augmenting path: A path from the source (s) to the sink (t) in the residual 
        graph where every edge has positive residual capacity.
    
    Algorithm In a Nutshell:
        - Initialize flow to 0
        - While (there is an augmenting path from s to t in the Residual Graph):
            1. Find the bottleneck capacity (min edge) on this path.
            2. Add this bottleneck to the total max flow.
            3. For every edge on the path:
                a. Subtract bottleneck from the forward edge capacity.
                b. Add bottleneck to the backward edge capacity.
        - Return total max flow.

    maxFlow = 0
    while (there exists augmenting path P from s to t) {
        pathFlow = minimum residual capacity along P
        for each edge (u,v) in P:
            flow(u,v) += pathFlow
            flow(v,u) -= pathFlow   // reverse edge
        maxFlow += pathFlow
    }

    Time Complexity: O(maxFlow * E)
*/

const int MAXN = 505;

int capacity[MAXN][MAXN];
vector<int> AL[MAXN];
bool visited[MAXN];

int n; // number of nodes

// DFS to find augmenting path
int dfs(int u, int t, int flow) {
    if (u == t) return flow;

    visited[u] = true;

    for (int v : AL[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            int pushed = dfs(v, t, min(flow, capacity[u][v]));
            if (pushed > 0) {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int FordFulkerson(int s, int t) {
    int flow = 0;

    while (true) {
        memset(visited, false, sizeof(visited));
        int pushed = dfs(s, t, INT_MAX);
        if (pushed == 0) break;
        flow += pushed;
    }

    return flow;
}

int mainFordFulkerson() {
    int m; // edges
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].push_back(v);
        adj[v].push_back(u); // reverse edge for residual graph
        capacity[u][v] += c; // handle multi-edges
    }

    int s, t;
    cin >> s >> t;

    cout << FordFulkerson(s, t) << "\n";
    return 0;
}

/*
    Edmonds–Karp Algorithm
    - Always choose the shortest augmenting path (in edges).
    - How? Use BFS instead of DFS

    maxFlow = 0
    while (BFS finds augmenting path):
        pathFlow = bottleneck capacity
        update residual graph
        maxFlow += pathFlow

    Time Complexity: O(V * E^2)
*/

const int MAXN = 505;

int capacity[MAXN][MAXN];
vector<int> AL[MAXN];
int parent[MAXN];
int n;

// BFS to find shortest augmenting path
int bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    parent[s] = -2;

    queue<pair<int,int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto [u, flow] = q.front();
        q.pop();

        for (int v : AL[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);

                if (v == t)
                    return new_flow;

                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

// Edmonds–Karp
int EdmondsKarp(int s, int t) {
    int flow = 0;
    int new_flow;

    while ((new_flow = bfs(s, t))) {
        flow += new_flow;

        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int mainEdmondsKarp() {
    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        AL[u].push_back(v);
        AL[v].push_back(u); // reverse edge
        capacity[u][v] += c;
    }

    int s, t;
    cin >> s >> t;

    cout << maxflow(s, t) << "\n";
    return 0;
}

/*
    Dinic’s Algorithm (CP Standard)
        - idea: use BFS (shortest path) info multiple time
        - two distinct phases:
            1. Building a Level Graph (using BFS once).
            2. Finding a Blocking Flow (using multiple DFS runs).

    maxFlow = 0
    while (BFS builds level graph):
        reset pointers
        while (DFS pushes flow):
            add to maxFlow

    Time Complexity: O(V^2 * E) general, O(min(V^(2/3), √E) * E) Unit capacity
*/

const int MAXN = 200005;
const int INF = 1e9;

struct Edge {
    int to, cap, rev;
};

vector<Edge> AL[MAXN];
int level[MAXN];
int ptr[MAXN];
int n;

// add edge
void add_edge(int u, int v, int cap) {
    AL[u].push_back({v, cap, (int)AL[v].size()});
    AL[v].push_back({u, 0, (int)AL[u].size() - 1});
}

// BFS → build level graph
bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &e : AL[u]) {
            if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }

    return level[t] != -1;
}

// DFS → send blocking flow
int dfs(int u, int t, int pushed) {
    if (pushed == 0) return 0;
    if (u == t) return pushed;

    for (int &cid = ptr[u]; cid < AL[u].size(); cid++) {
        Edge &e = AL[u][cid];

        if (e.cap > 0 && level[e.to] == level[u] + 1) {
            int tr = dfs(e.to, t, min(pushed, e.cap));
            if (tr == 0) continue;

            e.cap -= tr;
            AL[e.to][e.rev].cap += tr;
            return tr;
        }
    }
    return 0;
}

long long Dinic(int s, int t) {
    long long flow = 0;

    while (bfs(s, t)) {
        memset(ptr, 0, sizeof(ptr));
        while (int pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    int s, t;
    cin >> s >> t;

    cout << Dinic(s, t) << "\n";
}