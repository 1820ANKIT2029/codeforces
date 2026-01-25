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
