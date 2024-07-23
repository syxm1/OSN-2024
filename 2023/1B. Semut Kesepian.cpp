#include<bits/stdc++.h>
using namespace std;

using ll = long long;

struct mx_pair {
	int mx1, mx2;

	void add(int c) {
		if (c > mx1) mx2 = mx1, mx1 = c;
		else if (c > mx2) mx2 = c;
	}

	int get_not(int x) {
		return x == mx1 ? mx2 : mx1;
	}
};

struct mn_pair {
	int mn1, mn2;
	
	void add(int c) {
		if (c < mn1) mn2 = mn1, mn1 = c;
		else if (c < mn2) mn2 = c;
	}

	int get_not(int x) {
		return x == mn1 ? mn2 : mn1;
	}
};

signed main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> adj(n);

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	ll ans = 0;

	// single node contribution
	vector<mx_pair> lf(n);
	vector<mn_pair> rg(n);

	for (int i = 0; i < n; i++) {
		lf[i].mx1 = lf[i].mx2 = -1;
		rg[i].mn1 = rg[i].mn2 = n;
		for (int j : adj[i]) {
			if (j < i) lf[i].add(j);
			if (j > i) rg[i].add(j);
		}
		ans += (ll) (i - lf[i].mx1) * (ll) (rg[i].mn1 - i);
	}

	// pair node contribution
	for (int i = 0; i < n; i++) {
		for (int j : adj[i]) {
			if (i > j) continue;
			int l = max(lf[i].mx1, lf[j].get_not(i));
			int r = min(rg[j].mn1, rg[i].get_not(j));
			if (i < l || j > r) continue;
			ans += 2ll * (ll) (i - l) * (ll) (r - j);			
		}
	}

	cout << ans << '\n';
}
