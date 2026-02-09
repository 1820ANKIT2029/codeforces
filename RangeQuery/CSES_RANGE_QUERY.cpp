#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<int, pii> pipii;

const ll MOD = 1e9 + 7;

#define Left(x) ((x)<<1)+1
#define Right(x) ((x)<<1)+2

class _1646 { // static prefix array -> works for static sum and XOR
	public:
	int n, q;
	vector<ll> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n+1);
		for(int i=1; i<=n; i++) cin >> x[i];
		
		for(int i=1; i<=n; i++) x[i] += x[i-1];
		
		int a, b;
		while(q--) {
			cin >> a >> b;
			
			cout << x[b] - x[a-1] << endl;
		}
		
	}
};

class SparseTableMin {
public:
    int n, log_size;
    vector<int> a;
    vector<vector<int>> st;
    vector<int> lg;

    SparseTableMin(int size, vector<int> &x) : n(size), a(x), lg(size + 1) {
        log_size = floor(log2(n)) + 1; 
        st.assign(n, vector<int>(log_size)); 

        build_log();
        build_sparse_table();
    }

    void build_log() {
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
    }

    void build_sparse_table() {
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];

        for (int k = 1; k < log_size; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[i][k] = min(
                    st[i][k - 1],
                    st[i + (1 << (k - 1))][k - 1]
                );
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int k = lg[len];
        return min(
            st[l][k],
            st[r - (1 << k) + 1][k]
        );
    }
};

class _1647 {
	public:
	int n, q;
	vector<int> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n);
		for(int &i: x) cin >> i;
		
		SparseTableMin st(n, x);
		
		int a, b;
		while(q--) {
			cin >> a >> b;
			cout << st.query(a-1, b-1) << endl;
		}
	}
};

class segmentTreeSum {
	int size;
	vector<ll> tree;
	
	// [L..R] segment cover by index p on tree
	void buildTree(int p, int L, int R, vector<ll> &a) {
		if(L == R) {
			if(L < (int)a.size()) tree[p] = a[L];
			return;
		}
		
		int mid = L + ((R - L) >> 1);
		buildTree(Left(p), L, mid, a);
		buildTree(Right(p), mid+1, R, a);
		tree[p] = tree[Left(p)] + tree[Right(p)];
	}
	
	ll rangeSum(int p, int L, int R, int l, int r) {
		if(L >= l && R <= r) return tree[p];
		if(L > r || R < l) return 0;
		
		int mid = L + ((R - L) >> 1);
		
		return rangeSum(Left(p), L, mid, l, r) + rangeSum(Right(p), mid+1, R, l, r);
	}
	
	void update(int p, int L, int R, int ind, ll num) {
		if(L == R) {
			tree[p] = num; return;
		}
		
		int mid = L + ((R-L)>>1);
		if(ind <= mid) update(Left(p), L, mid, ind, num);
		else update(Right(p), mid+1, R, ind, num);
		
		tree[p] = tree[Left(p)] + tree[Right(p)];
	}

public:
	segmentTreeSum(vector<ll> &a) {
		int n = a.size();
		size = 1;
		while(size < n) size *= 2;
		
		tree.assign(2*size, 0LL);
		
		buildTree(0, 0, size-1, a);
	}
	
	ll query(int l, int r) {
		return rangeSum(0, 0, size-1, l, r);
	}
	
	void update(int ind, ll num) {
		update(0, 0, size-1, ind, num);
	}
};

class _1648 {
	public:
	int n, q;
	vector<ll> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n);
		for(ll &i: x) cin >> i;
		
		segmentTreeSum seg(x);
		
		int type, a, b, k; ll u;
		while(q--) {
			cin >> type;
			if(type == 1) {
				cin >> k >> u;
				seg.update(k-1, u);
			}
			else {
				cin >> a >> b;
				cout << seg.query(a-1, b-1) << "\n";
			}
		}
	}
};

class segmentTreeMin {
	int size;
	vector<ll> tree;
	
	// [L..R] segment cover by index p on tree
	void buildTree(int p, int L, int R, vector<ll> &a) {
		if(L == R) {
			if(L < (int)a.size()) tree[p] = a[L];
			return;
		}
		
		int mid = L + ((R - L) >> 1);
		buildTree(Left(p), L, mid, a);
		buildTree(Right(p), mid+1, R, a);
		tree[p] = min(tree[Left(p)], tree[Right(p)]);
	}
	
	ll rangeMin(int p, int L, int R, int l, int r) {
		if(L >= l && R <= r) return tree[p];
		if(L > r || R < l) return 1e15;
		
		int mid = L + ((R - L) >> 1);
		
		return min(
			rangeMin(Left(p), L, mid, l, r), 
			rangeMin(Right(p), mid+1, R, l, r)
		);
	}
	
	void update(int p, int L, int R, int ind, ll num) {
		if(L == R) {
			tree[p] = num; return;
		}
		
		int mid = L + ((R-L)>>1);
		if(ind <= mid) update(Left(p), L, mid, ind, num);
		else update(Right(p), mid+1, R, ind, num);
		
		tree[p] = min(tree[Left(p)], tree[Right(p)]);
	}

public:
	segmentTreeMin(vector<ll> &a) {
		int n = a.size();
		size = 1;
		while(size < n) size *= 2;
		
		tree.assign(2*size, 1e15);
		
		buildTree(0, 0, size-1, a);
	}
	
	ll query(int l, int r) {
		return rangeMin(0, 0, size-1, l, r);
	}
	
	void update(int ind, ll num) {
		update(0, 0, size-1, ind, num);
	}
};

class _1649 {
	public:
	int n, q;
	vector<ll> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n);
		for(ll &i: x) cin >> i;
		
		segmentTreeMin seg(x);
		
		int type, a, b, k; ll u;
		while(q--) {
			cin >> type;
			if(type == 1) {
				cin >> k >> u;
				seg.update(k-1, u);
			}
			else {
				cin >> a >> b;
				cout << seg.query(a-1, b-1) << "\n";
			}
		}
	}
};

class _1650 {
	public:
	int n, q;
	vector<int> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n + 1); x[0] = 0;
		
		for(int i=1; i<=n; i++) {
			cin >> x[i];
			x[i] ^= x[i-1];
		}
		
		int a, b;
		while(q--) {
			cin >> a >> b;
			
			cout << (x[b] ^ x[a-1]) << endl;
		}
	}
};

class SegmentTreeAddSeg { // Range Update Point Query
	int size;
	vector<ll> tree;
	
	void build(int p, int L, int R, vector<ll> &a) {
		if(L == R) {
			if(L < (int) a.size()) tree[p] = a[L];
			return;
		}
		
		int mid = L + ((R - L) >> 1);
		build(Left(p), L, mid, a);
		build(Right(p), mid+1, R, a);
	}
	
	void rangeAdd(int p, int L, int R, int l, int r, ll v) {
		if(L >= l && R <= r) {
			tree[p] += v; return;
		}
		if(R < l || L > r) return;
		
		int mid = L + ((R - L) >> 1);
		rangeAdd(Left(p), L, mid, l, r, v);
		rangeAdd(Right(p), mid+1, R, l, r, v);
	}
	
	ll pointQuery(int p, int L, int R, int ind) {
		if(L == R) return tree[p];
		
		int mid = L + ((R - L) >> 1);
		ll ans;
		if(ind <= mid) ans = pointQuery(Left(p), L, mid, ind);
		else ans = pointQuery(Right(p), mid+1, R, ind);
		
		return ans + tree[p];
	}
	
public:
	SegmentTreeAddSeg(vector<ll> &a) {
		int n = a.size();
		size = 1;
		while(size < n) size *= 2;
		
		tree.assign(2 * size, 0LL);
		
		build(0, 0, size-1, a);
	}
	
	void rangeAdd(int l, int r, ll v) {
		rangeAdd(0, 0, size-1, l, r, v);
	}
	
	ll pointQuery(int ind) {
		return pointQuery(0, 0, size-1, ind);
	}
};

class _1651 {
	public:
	int n, q;
	vector<ll> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n);
		for(ll &i: x) cin >> i;
		
		SegmentTreeAddSeg seg(x);
		
		int type, a, b, k; ll u;
		while(q--) {
			cin >> type;
			if(type == 1) {
				cin >> a >> b >> u;
				seg.rangeAdd(a-1, b-1, u);
			}
			else {
				cin >> k;
				cout << seg.pointQuery(k-1) << endl;
			}
		}
	}
};

class _1652 { // 2D prefix sum 
	public:
	int n, q;
	vector<vector<int>> forest;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		forest.assign(n + 1, vector<int>(n + 1, 0));
		char c;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++) {
				cin >> c;
				if(c == '*') forest[i][j] = 1;
			}
		
		// preprocessing
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				forest[i][j] = (
					forest[i][j] + forest[i-1][j] + 
					forest[i][j-1] - forest[i-1][j-1]
				);
			}
		}
		
		int x1, x2, y1, y2;
		while(q--) {
			cin >> y1 >> x1 >> y2 >> x2;
			
			cout << (
				forest[y2][x2]
				- forest[y1-1][x2]
				- forest[y2][x1-1]
				+ forest[y1-1][x1-1]
			) << endl;
		}
	}
};

class segmentTreeFirstElementGreaterThanK { // First Element >= k
	int size;
	vector<ll> tree;
	
	void build(int p, int L, int R, vector<ll> &a) {
		if(L == R) {
			if(L < (int)a.size()) tree[p] = a[L];
			return;
		}
		
		int mid = L + ((R - L) >> 1);
		build(Left(p), L, mid, a);
		build(Right(p), mid+1, R, a);
		
		tree[p] = max(tree[Left(p)], tree[Right(p)]);
	}
	
	void update(int p, int L, int R, int ind, int v) {
		if(L == R) {
			tree[p] -= v; return;
		}
		
		int mid = L + ((R-L)>>1);
		if(ind <= mid) update(Left(p), L, mid, ind, v);
		else update(Right(p), mid+1, R, ind, v);
		
		tree[p] = max(tree[Left(p)], tree[Right(p)]);
	}
	
	int find(int p, int L, int R, ll v) {
		if(tree[p] < v) return -1;
		if(L == R) {
			if(v <= tree[p]) return L;
			return -1;
		}
		
		int ans, mid = L + ((R - L) >> 1);
		ans = find(Left(p), L, mid, v);
		if(ans != -1) return ans;
		ans = find(Right(p), mid+1, R, v);
		return ans;
	}
	
public:
	segmentTreeFirstElementGreaterThanK(vector<ll> &a) {
		int n = a.size();
		size = 1;
		while(size < n) size *= 2;
		
		tree.assign(2 * size, -1);
		
		build(0, 0, size - 1, a);
	}
	
	void update(int ind, int v) {
		update(0, 0, size-1, ind, v);
	}
	
	int find(ll v) {
		int ans = find(0, 0, size-1, v);
		if(ans != -1) update(ans, v);
		return ans;
	}
};

class _1143 {
	public:
	int n, m;
	vector<ll> h;
	void solve() {
		FAST_IO;
		cin >> n >> m;
		h.resize(n);
		for(ll &i: h) cin >> i;
		
		segmentTreeFirstElementGreaterThanK seg(h);
		
		ll r;
		while(m--) {
			cin >> r;
			
			cout << seg.find(r) + 1 << " ";
		}
		cout << endl;
	}
};

class segmentTreeListRemovals {
	int size;
	vector<int> tree, nums;
	
	void build(int p, int L, int R, vector<int> &a) {
		if(L == R) {
			if(L < (int)a.size()) tree[p] = 1;
			return;
		}
		
		int mid = L + ((R-L) >> 1);
		build(Left(p), L, mid, a);
		build(Right(p), mid+1, R, a);
		
		tree[p] = tree[Left(p)] + tree[Right(p)];
	}
	
	void update(int p, int L, int R, int ind, int v) {
		if(L == R) { tree[p] -= v; return; }
		
		int mid = L + ((R-L)>>1);
		if(ind <= mid) update(Left(p), L, mid, ind, v);
		else update(Right(p), mid+1, R, ind, v);
		
		tree[p] = tree[Left(p)] + tree[Right(p)];
	}
	
	int find(int p, int L, int R, int ind) {
		if(L == R) return L;
		
		int mid = L + ((R-L)>>1);
		if(ind < tree[Left(p)]) return find(Left(p), L, mid, ind);
		return find(Right(p), mid+1, R, ind - tree[Left(p)]);
	}
	
public:
	segmentTreeListRemovals(vector<int> &a): nums(a) {
		int n = a.size();
		size = 1;
		while(size < n) size *= 2;
		tree.assign(2 * size, 0);
		
		build(0, 0, size - 1, a);
	}
	
	void update(int ind, int v) {
		update(0, 0, size-1, ind, v);
	}
	
	int find(int ind) {
		int i = find(0, 0, size-1, ind);
		update(i, 1);
		return nums[i];
	}
};

class _1749 {
	public:
	int n;
	vector<int> x;
	
	void solve() {
		FAST_IO;
		cin >> n;
		x.resize(n);
		for(int &i: x) cin >> i;
		
		segmentTreeListRemovals seg(x);
		
		int p;
		while(n--) {
			cin >> p;
			cout << seg.find(p - 1) << " ";
		}
		cout << endl;
	}
};

class segmentTreeCountBtwAAndB {
	int size;
	vector<int> tree;
	
	void update(int p, int L, int R, int ind, int v) {
		if(L == R) { tree[p] += v; return; }
		
		int mid = L + ((R-L)>>1);
		if(ind <= mid) update(Left(p), L, mid, ind, v);
		else update(Right(p), mid+1, R, ind, v);
		
		tree[p] = tree[Left(p)] + tree[Right(p)];
	}
	
	int query(int p, int L, int R, int l, int r) {
		if(l > R || r < L) return 0;
		if(l <= L && r >= R) return tree[p];
		
		int mid = L + ((R-L) >> 1);
		return query(Left(p), L, mid, l, r) + query(Right(p), mid+1, R, l, r);
	}
	
public:
	segmentTreeCountBtwAAndB(int n) {
		size = 1;
		while(size < n) size *= 2;
		tree.assign(2*size, 0);
	}
	
	void update(int ind, int v) {
		update(0, 0, size-1, ind, v);
	}
	
	int query(int l, int r) {
		if(l > r) return 0;
		return query(0, 0, size-1, l, r);
	}
};

class _1144 {
	public:
	int n, q;
	vector<int> p;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		p.resize(n);
		for(int &i: p) cin >> i;
		
		vector<pair<char, pair<int, int>>> queries;
		vector<int> all_values = p;
		char type; int a, b;
		for (int i = 0; i < q; i++) {
			cin >> type >> a >> b;
			queries.push_back({type, {a, b}});
			if (type == '!') {
				all_values.push_back(b);
			} else {
				all_values.push_back(a);
				all_values.push_back(b);
			}
		}
		
		// Coordinate Compression
		sort(all_values.begin(), all_values.end());
		all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());
		auto get_id = [&](int x) {
			return lower_bound(all_values.begin(), all_values.end(), x) - all_values.begin();
		};
		
		int m = all_values.size();
		segmentTreeCountBtwAAndB st(m);
		for (int x : p) {
			st.update(get_id(x), 1);
		}
		
		for (auto &qr : queries) {
			type = qr.first;
			a = qr.second.first;
			b = qr.second.second;

			if (type == '!') {
				int idx = a - 1;
				st.update(get_id(p[idx]), -1);
				p[idx] = b;
				st.update(get_id(p[idx]), 1);
			} else {
				int l = lower_bound(all_values.begin(), all_values.end(), a) - all_values.begin();
				int r = upper_bound(all_values.begin(), all_values.end(), b) - all_values.begin() - 1;
				if (l <= r)
					cout << st.query(l, r) << "\n";
				else
					cout << 0 << "\n";
			}
		}
	}
};

class segmentTreeMaxPrefixSum {
public:
	struct item {
		ll sum, prefixSum;
	};
	
private:
	int size;
	vector<item> tree;
	
	item NEUTRAL_ELEMENT = {0, 0};
	
	item merge(item &a, item &b) {
		return {
			a.sum + b.sum,
			max(a.prefixSum, a.sum + b.prefixSum)
		};
	}
	
	void build(int p, int L, int R, vector<ll> &a) {
		if(L == R) {
			if(L < a.size()) tree[p] = {a[L], max(0LL, a[L])};
			return;
		}
		
		int mid = L + ((R-L)>>1);
		build(Left(p), L, mid, a);
		build(Right(p), mid+1, R, a);
		
		tree[p] = merge(tree[Left(p)], tree[Right(p)]);
	}
	
	void update(int p, int L, int R, int idx, int val) {
		if(L == R) { tree[p] = {val, max(0, val)}; return;}
		
		int mid = L + ((R-L)>>1);
		if(idx <= mid) update(Left(p), L, mid, idx, val);
		else update(Right(p), mid+1, R, idx, val);
		
		tree[p] = merge(tree[Left(p)], tree[Right(p)]);
	}
	
	item rangeQuery(int p, int L, int R, int l, int r) {
		if(l <= L && r >= R) return tree[p];
		
		int mid = L + ((R-L) >> 1);
		
		if(r <= mid) return rangeQuery(Left(p), L, mid, l, r);
		if(l > mid) return rangeQuery(Right(p), mid+1, R, l, r);
		
		item ans1 = rangeQuery(Left(p), L, mid, l, r);
		item ans2 = rangeQuery(Right(p), mid+1, R, l, r);
		return merge(ans1, ans2);
	}
	
public:
	segmentTreeMaxPrefixSum(vector<ll> &a) {
		int n = a.size(); size = 1;
		while(size < n) size *= 2;
		
		tree.assign(2 * size, NEUTRAL_ELEMENT);
		build(0, 0, size-1, a);
	}
	
	void update(int idx, ll val) {
		update(0, 0, size-1, idx, val);
	}
	
	ll rangeQuery(int l, int r) {
		return rangeQuery(0, 0, size-1, l, r).prefixSum;
	}
};

class _2166 {
	public:
	int n, q;
	vector<ll> x;
	
	void solve() {
		FAST_IO;
		cin >> n >> q;
		x.resize(n);
		for(ll &i: x) cin >> i;
		
		segmentTreeMaxPrefixSum seg(x);
		
		int type, k, a, b; ll u;
		while(q--) {
			cin >> type;
			if(type == 1) {
				cin >> k >> u;
				seg.update(k-1, u);
			}
			else {
				cin >> a >> b;
				cout << seg.rangeQuery(a-1, b-1) << endl;
			}
		}
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
	
	_2166 a;
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
