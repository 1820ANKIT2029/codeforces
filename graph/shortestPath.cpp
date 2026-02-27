#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
vector<vector<pii>> AL;

int main() {
  cout << "Shortest paths" << endl;
}

// Single Source Shortest Paths (SSSP)

// BFS (Breadth first Search) -> unweighted graph
vector<int> p;

void printPath(int u) {
	if (u == s) { printf("%d", s); return; }
	printPath(p[u]);
	printf(" %d", u); // output: s -> ... -> t
}

void BFS() {
	// suppose s: source and t: goal have been defined
	vector<int> dist(V, INF); dist[s] = 0; // V is number of nodes
	queue<int> q; q.push(s);
	p.assign(V, -1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (auto &[v, w] : AL[u]) {
			if (dist[v] != INF) continue;
			dist[v] = dist[u]+1;
			p[v] = u;
			q.push(v);
		}
	}
	printPath(t), printf("\n");
}

// Dijkstra Algorithms -> Non-Negative Weighted Graph

void Dijkstra_BST() {
	vi dist(V, INF); dist[s] = 0;
	set<pii> pq;                          // balanced BST version
	for (int u = 0; u < V; ++u)          // dist[u] = INF
		pq.emplace(dist[u], u);
	
	while (!pq.empty()) {
		auto [d, u] = *pq.begin();        // shortest unvisited u
		pq.erase(pq.begin());
		for (auto &[v, w] : AL[u]) {     // all edges from u
			if (dist[u]+w >= dist[v]) continue;  // not improving, skip
			pq.erase(pq.find({dist[v], v}));     // erase old pair
			dist[v] = dist[u]+w;                 // relax operation
			pq.emplace(dist[v], v);              // enqueue better pair
		}
	}
	for (int u = 0; u < V; ++u)
		printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);
}

void Dijkstra_Heap() {
	vi dist(V, INF); dist[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, s);
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();        // shortest unvisited u
		if (d > dist[u]) continue;               // a very important check
		for (auto &[v, w] : AL[u]) {
			if (dist[u]+w >= dist[v]) continue;  // not improving, skip
			dist[v] = dist[u]+w;                 // relax operation
			pq.emplace(dist[v], v);              // enqueue better pair
		}
	}
	
	for (int u = 0; u < V; ++u)
		printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);
}

// Bellman-Ford -> Negative cycle weighted graph

void bellmanFord() {
	vi dist(V, INF); dist[s] = 0;
	for (int i = 0; i < V-1; ++i)                 // total O(V*E)
		for (int u = 0; u < V; ++u)               // these two loops = O(E)
			if (dist[u] != INF)                   // important check
				for (auto &[v, w] : AL[u])
					dist[v] = min(dist[v], dist[u]+w);
}


// with negative cycle check
void modified_bellmanFord() {
	vector<int> dist(V, INF); dist[s] = 0;
	for (int i = 0; i < V-1; ++i) {            // total O(V*E)
		bool modified = false;                 // optimization
		for (int u = 0; u < V; ++u) {            // these two loops = O(E)
			if (dist[u] != INF) {
				for (auto &[v, w] : AL[u]) {
					if (dist[u]+w >= dist[v]) continue;  // not improving, skip
					dist[v] = dist[u]+w;                 // relax operation
					modified = true;                     // optimization
				}
			}
		}
		if (!modified) break;                        // optimization
	}
	
	bool hasNegativeCycle = false;
	for (int u = 0; u < V; ++u) 
		if (dist[u] != INF)
			for (auto &[v, w] : AL[u]) // C++17 style
				if (dist[v] > dist[u]+w)             // should be false
					hasNegativeCycle = true;         // if true => -ve cycle
	
	if (hasNegativeCycle)
		printf("Negative Cycle Exist\n");
	else {
		for (int u = 0; u < V; ++u)
		printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);
	}
}

// O(kE) : k can be V
void Bellman_Ford_Moore() {
	vector<int> dist(V, INF); dist[s] = 0;
	queue<int> q; q.push(s);                         // like BFS queue
	vector<int> in_queue(V, 0); in_queue[s] = 1;     // unique to SPFA
	
	while (!q.empty()) {
		int u = q.front(); q.pop(); in_queue[u] = 0; // pop from queue
		for (auto &[v, w] : AL[u]) {
			if (dist[u]+w >= dist[v]) continue;      // not improving, skip
			dist[v] = dist[u] + w;                   // relax operation
			if (in_queue[v]) continue;               // v already in q, skip
			q.push(v);
			in_queue[v] = 1;                         // v is currently in q
		}
	}
	
	for (int u = 0; u < V; ++u)
		printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);
}


// All Pairs Shortest Paths (APSP)

// Floyd warshell Algorithm -> O(V^3)
void FloydWarshell () {
	// precondition: AM[i][j] contains the weight of edge (i, j)
	// or INF (1B) if there is no such edge, use memset(AM, 63, sizeof AM)
	// Adjacency Matrix AM is a 32-bit signed integer array
	
	for (int k = 0; k < V; ++k)    // loop order is k->i->j
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				AM[i][j] = min(AM[i][j], AM[i][k]+AM[k][j]);
}

// printing path
void FloydWarshell_with_path () {
	// let p be a 2D parent matrix, where p[i][j] is the last vertex before j
	// on a shortest path from u to v, i.e., i -> ... -> p[i][j] -> j
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			p[i][j] = i;                       // initialization
		
	
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				if (AM[i][k] + AM[k][j] < AM[i][j]) {
					AM[i][j] = AM[i][k] + AM[k][j];
					p[i][j] = p[k][j];        // update the p matrix
				}
				
	// when we need to print the shortest paths, we can call the method below:
}

void printPath(int i, int j) {
	if (i != j) printPath(i, p[i][j]);
	printf(" %d", v);
}

/*
Johnson’s Algorithm: All-Pairs Shortest Path (APSP) problem in sparse, 
	directed graphs that may contain negative edge weights.

	O(V^2 log V + V E)

	How it Works (The Reweighting Technique)
	1. Add a Dummy Vertex (q) with weight 0
	2. Bellman-Ford on Vertex q, finds the shortest path h[v] from q to every other vertex v
	3. Reweight Edges: w'(u, v) = w(u, v) + h[u] - h[v]
	4. Dijkstra’s Algorithm: Run Dijkstra’s algorithm from every vertex u using the new 
		non-negative weights w' to find the reweighted shortest paths d'(u, v).
	5. Restore Distances: d(u, v) = d'(u, v) - h[u] + h[v]
	
*/

bool bellman_ford(int V, const vector<vector<int>>& edges, vector<int>& h) {
    h.assign(V, 0);

    // Relax all edges V - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            if (h[u] != INF && h[u] + weight < h[v]) {
                h[v] = h[u] + weight;
            }
        }
    }

    // pass to check for negative-weight cycles
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        
        if (h[u] != INF && h[u] + weight < h[v]) {
            return false; // Negative cycle detected
        }
    }
    return true;
}

void dijkstra(int src, int V, const vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    dist.assign(V, INF);
    dist[src] = 0;
    
    // Min-heap priority queue: stores {distance, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
		
        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// Main function to orchestrate Johnson's Algorithm
void johnson_apsp(int V, const vector<vector<int>>& edges) {
    vector<int> h;

    // Step 1 & 2: Get potentials using Bellman-Ford
    if (!bellman_ford(V, edges, h)) {
        cout << "Graph contains a negative weight cycle. APSP is undefined.\n";
        return;
    }

    // Step 3: Create an adjacency list with reweighted, non-negative edges
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        
        // Formula: w'(u, v) = w(u, v) + h[u] - h[v]
        int reweighted = weight + h[u] - h[v];
        adj[u].push_back({v, reweighted});
    }

    vector<vector<int>> shortest_paths(V, vector<int>(V, INF));

    // Step 4: Run Dijkstra from every vertex
    for (int u = 0; u < V; u++) {
        vector<int> dist;
        dijkstra(u, V, adj, dist);

        // Step 5: Undo the reweighting to get the original shortest path distances
        for (int v = 0; v < V; v++) {
            if (dist[v] != INF) {
                // Formula: d(u, v) = d'(u, v) - h[u] + h[v]
                shortest_paths[u][v] = dist[v] - h[u] + h[v];
            }
        }
    }

    // Output the resulting All-Pairs Shortest Path matrix
    cout << "All-Pairs Shortest Path Matrix:\n";
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (shortest_paths[u][v] == INF) {
                cout << "INF\t";
            } else {
                cout << shortest_paths[u][v] << "\t";
            }
        }
        cout << "\n";
    }
}
