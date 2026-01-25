#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << "Minimum spanning Tree" << endl;
}

// Kruskal's Algorithm
// O(E log E) = O(E log V^2) = O(2 * E log V ) = O(E log V)

void Kruskal() {
	int V, E; scanf("%d %d", &V, &E);
	vector<iii> EL(E);                 // EdgeList
	for (int i = 0; i < E; ++i) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w); // read as (u, v, w)
		EL[i] = {w, u, v};                          // reorder as (w, u, v)
	}
	
	sort(EL.begin(), EL.end());
	int mst_cost = 0, num_taken = 0;
	UnionFind UF(V);               // to check if select edge create cycle or not
	for (auto &[w, u, v] : EL) {
		if (UF.isSameSet(u, v)) continue;   // already in the same CC
		mst_cost += w;                      // add w of this edge
		UF.unionSet(u, v);                  // link them
		++num_taken;                        // 1 more edge is taken
		if (num_taken == V-1) break;        // optimization
	}
	printf("MST cost = %d (Kruskal’s)\n", mst_cost);
}

// Prim's Algorithm
// = O(E * log E) = O(E log V )

typedef pair<int, int> pii;

vector<vector<pii>> AL;        // the graph stored in AL
vector<int> taken;             // to avoid cycle
priority_queue<pii, vector<pii>, greater<pii>> pq;      // to select shorter edges (min heap)

void process(int u) { // set u as taken and enqueue neighbors of u
	taken[u] = 1;
	for (auto &[v, w] : AL[u])
		if (!taken[v])
			pq.emplace(w, v);        // sort by non-dec weight
}

void Prim() {
	int V, E; scanf("%d %d", &V, &E);
	AL.assign(V, vector<pii>());
	for (int i = 0; i < E; ++i) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);    // read as (u, v, w)
		AL[u].emplace_back(v, w);
		AL[v].emplace_back(u, w);
	}
	taken.assign(V, 0);              // no vertex is taken
	process(0);                      // take+process vertex 0
	
	int mst_cost = 0, num_taken = 0; // no edge has been taken
	while (!pq.empty()) {            // up to O(E)
		auto [w, u] = pq.top(); pq.pop();
		if(taken[u]) continue;       // already taken, skipped
		mst_cost += w;               // add w of this edge
		process(u);                  // take+process vertex u
		++num_taken;                 // 1 more edge is taken
		if (num_taken == V-1) break; // optimization
	}
	printf("MST cost = %d (Prim’s)\n", mst_cost);
}
