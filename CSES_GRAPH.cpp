#include <bits/stdc++.h>
using namespace std;

const int xdir[] = {1, 0, -1, 0};
const int ydir[] = {0, 1, 0, -1};
const char dir[] = {'D', 'R', 'U', 'L'};

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<int, pii> pipii;

class _1192 {
	public:
	int n, m;
	vector<string> grid;
	
	bool isGood(int x, int y) {
		if(x<0 || x>=n) return false;
		if(y<0 || y>=m) return false;
		return true;
	}
	
	void dfs(int x, int y) {
		grid[x][y] = '#';
		int _x, _y;
		for(int i=0; i<4; i++) {
			_x = x + xdir[i];
			_y = y + ydir[i];
			if(isGood(_x, _y) && grid[_x][_y] == '.') dfs(_x, _y);
		}
	}
	
	void solve() {
		cin >> n >> m;
		
		grid.assign(n, "");
		string s;
		for(int i=0; i<n; i++) {cin >> s; grid[i] = s;}
		
		int cnt = 0;
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				if(grid[i][j] == '.') {
					cnt++;
					dfs(i, j);
				}
			}
		}
		
		cout << cnt << endl;
	}
};

class _1193 { // can use BFS or Dijsktra or A*
	public:
	vector<string> grid;
	vector<char> path;
	int n, m;
	pii start, end;
	
	bool isGood(int x, int y) {
		if(x<0 || x>=n) return false;
		if(y<0 || y>=m) return false;
		return true;
	}
	
	void getPath() {
		int x = end.first;
		int y = end.second;
		
		int tmp;
		while(grid[x][y] != 'A') {
			tmp = grid[x][y];
			path.emplace_back(dir[tmp]);
			tmp = (tmp + 2) % 4;
			x += xdir[tmp];
			y += ydir[tmp];
		}
		
		reverse(path.begin(), path.end());
	}
	
	bool BFS() {
		queue<pii> q;
		q.push(start);
		
		int _x, _y;
		while(!q.empty()) {
			pii &tmp = q.front(); q.pop();
			if(tmp == end) return true;
			
			for(int i=0; i<4; i++) {
				_x = tmp.first + xdir[i];
				_y = tmp.second + ydir[i];
				if(isGood(_x, _y) && grid[_x][_y] == '.') {
					q.emplace(_x, _y);
					grid[_x][_y] = i;
				}
			}
		}
		return false;
	}
	
	
	bool Dijsktra() {
		priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
		pq.emplace(0, start);
		
		int _x, _y;
		while(!pq.empty()) {
			auto [dist, tmp] = pq.top(); pq.pop();
			if(tmp == end) return true;
			
			for(int i=0; i<4; i++) {
				_x = tmp.first + xdir[i];
				_y = tmp.second + ydir[i];
				if(isGood(_x, _y) && grid[_x][_y] == '.') {
					pq.emplace(dist + 1, pii(_x, _y));
					grid[_x][_y] = i;
				}
			}
		}
		
		return false;
	}
	
	int h_func(int x, int y) {
		return abs(end.first - x) + abs(end.second - y);
	}
	
	bool A_star() {
		vector<vector<int>> d(n, vector<int>(m, 1e9));
		priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
		pq.emplace(0 + h_func(start.first, start.second), start);
		d[start.first][start.second] = 0;
		
		int _x, _y;
		while(!pq.empty()) {
			auto [dist, tmp] = pq.top(); pq.pop();
			
			if (dist > d[tmp.first][tmp.second] + h_func(tmp.first, tmp.second)) continue;
			if(tmp == end) return true;
			
			for(int i=0; i<4; i++) {
				_x = tmp.first + xdir[i];
				_y = tmp.second + ydir[i];
				
				int new_dist = d[tmp.first][tmp.second] + 1 ;
				if(isGood(_x, _y) && grid[_x][_y] == '.' && new_dist < d[_x][_y]) {
					d[_x][_y] = new_dist;
					pq.emplace(new_dist + h_func(_x, _y), pii(_x, _y));
					grid[_x][_y] = i;
				}
			}
		}
		
		return false;
	}
	
	void solve() {
		cin >> n >> m;
		grid.assign(n, "");
		for(int i=0; i<n; i++) cin >> grid[i];
		
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++) {
				if(grid[i][j] == 'A') 
					start = {i, j};
				if(grid[i][j] == 'B')
					end = {i, j};
			}
				
		grid[end.first][end.second] = '.';
		//cout << end.first << " " << end.second << endl;
		// algo
		bool exist = A_star();
		// path
		if(exist) {
			cout << "YES\n";
			getPath();
			//for(string &s: grid) cout << s << endl;
			cout << path.size() << endl;
			for(char c: path) cout << c;
			cout << endl;
		}
		else cout << "NO\n";
	}
};

class _1666 {
	public:
	int n, m;
	vector<vector<int>> AL;
	vector<bool> c;
	
	void dfs(int u) {
		c[u] = true;
		
		for(int v: AL[u]) {
			if(c[v]) continue;
			dfs(v);
		}
	}
	
	void solve() {
		cin >> n >> m;
		AL.assign(n, vector<int>());
		int n1, n2;
		for(int i=0; i<m; i++) {
			cin >> n1 >> n2;
			AL[n1 - 1].emplace_back(n2 - 1);
			AL[n2 - 1].emplace_back(n1 - 1);
		}
		
		
		vector<int> nodes;
		c.assign(n, false);
		for(int i=0; i<n; i++) {
			if(c[i]) continue;
			
			dfs(i);
			nodes.emplace_back(i);
		}
		
		int ans = nodes.size() - 1;
		cout << ans << endl;
		if(ans == 0) return;
		for(int i=ans; i>0; i--) {
			cout << nodes[0] + 1 << " " << nodes[i] + 1 << endl;
		}
		
	}
};

class _1667 {
	public:
	int n, m;
	vector<vector<int>> AL;
	vector<int> p;
	vector<int> path;
	
	bool bfs(int u, int v){
		queue<int> q;
		q.push(u);
		p[u] = u;
		
		while(!q.empty()) {
			int u_ = q.front(); q.pop();
			if(u_ == v) return true;
			for(int v_: AL[u_]) {
				if(p[v_] != -1) continue;
				q.push(v_);
				p[v_] = u_;
			}
		}
		
		return false;
	}
	
	void get_path(int u, int g) {
		while(g != u) {
			path.push_back(g+1);
			g = p[g];
		}
		path.push_back(g+1);
		reverse(path.begin(), path.end());
	}
	
	void solve() {
		cin >> n >> m;
		AL.assign(n, vector<int>());
		int u, v;
		for(int i=0; i<m; i++) {
			cin >> u >> v;
			AL[u-1].push_back(v-1);
			AL[v-1].push_back(u-1);
		}
		
		p.assign(n, -1);
		bool exist = bfs(0, n-1);
		if(exist) {
			get_path(0, n-1);
			cout << path.size() << endl;
			for(int p: path) cout << p << " ";
			cout << endl;
		}
		else cout << "IMPOSSIBLE" << endl;
	}
};

class _1668 {
	public:
	int n, m;
	vector<vector<int>> AL;
	vector<char> c;
	bool bfs(int u) {
		queue<int> q;
		q.push(u);
		c[u] = 1;
		
		while(!q.empty()) {
			u = q.front(); q.pop();
			for(int v: AL[u]){
				if(c[v] != -1 && c[v] == c[u]) 
					return false;
				if(c[v] == -1) {
					q.push(v);
					c[v] = 1 - c[u];
				}
			}
		}
		return true;
	}
	void solve() {
		cin >> n >> m;
		AL.assign(n, vector<int>());
		int u, v;
		for(int i=0; i<m; i++) {
			cin >> u >> v;
			AL[u-1].push_back(v-1);
			AL[v-1].push_back(u-1);
		}
		c.assign(n, -1);
		
		bool exist = true;
		for(int i=0; i<n; i++) {
			if(c[i] != -1) continue;
			exist &= bfs(i);
			if(!exist) break;
		}
		
		if(exist) {
			for(int x: c) cout << x + 1 << " ";
			cout << endl;
		}
		else cout << "IMPOSSIBLE" << endl;
	}
};

class _1669 {
	public:
	int n, m;
	vector<vector<int>> AL;
	vector<int> p, path;
	
	pii dfs(int u) {
		pii tmp = {-1, -1};
		for(int v: AL[u]) {
			if(p[u] == v) continue;
			if(p[v] != -1) {
				return pii(v, u);
			}
			
			p[v] = u;
			tmp = dfs(v);
			if(tmp.first != -1 && tmp.second != -1) break;
		} 
		return tmp;
	}
	
	void solve() {
		cin >> n >> m;
		AL.assign(n, vector<int>());
		int u, v;
		for(int i=0; i<m; i++) {
			cin >> u >> v;
			AL[u-1].push_back(v-1);
			AL[v-1].push_back(u-1);
		}
		
		p.assign(n, -1);
		pii tmp;
		for(int i=0; i<n; i++) {
			if(p[i] != -1) continue;
			p[i] = i;
			tmp = dfs(i);
			if(tmp.first != -1 && tmp.second != -1) break;
		}
		
		u = tmp.first;
		v = tmp.second;
		
		if(u == -1 && v == -1) {
			cout << "IMPOSSIBLE" << endl;
			return;
		}
		path.push_back(u+1);
		while(v != u) {
			path.push_back(v+1);
			v = p[v];
		}
		path.push_back(u+1);
		reverse(path.begin(), path.end());
		
		cout << path.size() << endl;
		for(int x: path) cout << x << " ";
		cout << endl;
	}
};

class _1194 {
	public:
	int n, m;
	vector<string> grid;
	vector<char> path;
	vector<vector<char>> c;
	vector<vector<bool>> manOrmonster;
	
	bool isGood(int x, int y) {
		if(x<0 || x>=n) return false;
		if(y<0 || y>=m) return false;
		return true;
	}
	
	bool isSolution(int x, int y) {
		if(x==0 || x==n-1) return true;
		if(y==0 || y==m-1) return true;
		return false;
	}
	
	void get_path(int x, int y){
		int ind;
		while(c[x][y] != 5) {
			ind = c[x][y];
			path.push_back(dir[ind]);
			ind = (ind + 2) % 4;
			x += xdir[ind];
			y += ydir[ind];
		}
		reverse(path.begin(), path.end());
	}
	
	void solve() {
		cin >> n >> m;
		grid.assign(n, "");
		for(int i=0; i<n; i++) cin >> grid[i];
		
		queue<pair<char, pii>> q;
		manOrmonster.assign(n, vector<bool>(m, true));
		c.assign(n, vector<char>(m, -1));
		pii ans;
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++){
				switch (grid[i][j]){
					case 'A': 
						ans = pii(i, j);
						c[i][j] = 5;
						break;
					case 'M': 
						q.emplace('M', pii(i, j));
						manOrmonster[i][j] = false;
						c[i][j] = 6;
						break;
				}
			}
		q.emplace('A', ans);
		
		bool exist = false;
		int x, y;
		while(!q.empty()) {
			auto [character, tmp] = q.front(); q.pop();
			if(character == 'A' && isSolution(tmp.first, tmp.second)) {
				ans = tmp;
				exist = true;
				break;
			}
			
			for(int i=0; i<4; i++) {
				x = tmp.first + xdir[i]; 
				y = tmp.second + ydir[i];
				
				if(isGood(x, y) && grid[x][y] != '#' && c[x][y] == -1){
					if(character == 'A' && !manOrmonster[x][y]) continue;
					if(character == 'M') {
						manOrmonster[x][y] = false;
					}
					q.emplace(character, pii(x, y));
					c[x][y] = i;
				}
			}
		}
		
		if(!exist) {
			cout << "NO" << endl;
			return;
		}
		
		/*
		for(vector<char> &v: c){
			for(int x: v) {
				cout << to_string(x) << " ";
			}
			cout << endl;
		}
		*/
		
		cout << "YES" << endl;
		get_path(ans.first, ans.second);
		cout << path.size() << endl;
		for(char c: path) {
			cout << c;
		}
		cout << endl;
	}
};

class _1671 {
	public:
	int n, m;
	vector<vector<pli>> AL;
	vector<ll> d;
	
	void dijkstra(int start) {
		priority_queue<pli, vector<pli>, greater<pli>> pq;
		pq.emplace(0, start);
		d[start] = 0;
		
		while(!pq.empty()) {
			auto [dist, u] = pq.top(); pq.pop();
			
			if(d[u] < dist) continue;
			
			for(auto [w, v]: AL[u]) {
				ll d_ = dist + w;
				if(d_ < d[v]) {
					pq.emplace(d_, v);
					d[v] = d_;
				}
			}
		}
	}
	
	void solve() {
		cin >> n >> m;
		AL.assign(n, vector<pli>());
		int a, b;
		ll c;
		for(int i=0; i<m; i++) {
			cin >> a >> b >> c;
			AL[a-1].emplace_back(c, b-1);
		}
		
		d.assign(n, LLONG_MAX);
		dijkstra(0);
		for(ll x: d) cout << x << " ";
		cout << endl;
	}
};

/* templete
class _QuesNum {
	public:
	void solve() {
		
	}
};
*/
void solve() {
	_1671 a;
	a.solve();
}

int main() {
	long long t = 1;
	//cin >> t;
	while(t--) solve();
}
