#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll N, K, Q;

vector<ll> dp;
vector<int> P, nx;
vector<vector<int>> C;
vector<bool> st;

signed main() {
	cin >> N >> K >> Q;

	P.resize(N);
	C.resize(N);

	for (int i = 1; i < N; i++) {
		int x; cin >> x; --x;
		P[i] = x;
		C[x].push_back(i);
	}

	dp.assign(N, 1);
	st.assign(N, 1);
	nx.assign(N, -1);

	function<void(int)> dfs = [&] (int cur) {
		ll mx = -1; int id = -1;
		for (int nxt : C[cur]) {
			dfs(nxt);
			if (dp[nxt] > mx) {
				mx = dp[nxt];
				id = nxt;
			}
		}
		if (id != -1) {
			dp[cur] += dp[id];
			nx[cur] = id;
			st[id] = 0;
		}
	};

	dfs(0);

	vector<vector<int>> G;
	for (int i = 0; i < N; i++) {
		if (!st[i]) continue;
		G.push_back({});
		int cur = i;
		while (cur != -1) {
			G.back().push_back(cur);
			cur = nx[cur];
		}
	}

	function<ll(ll, ll)> sum = [&] (ll l, ll r) {
		if (l > r) return 0ll;
		return (l + r) * (r - l + 1ll) / 2ll;
	};

	ll B = 0;
	for (vector<int> &v : G) {
		B += sum(1ll, (ll) v.size() - 1ll);
	}

	if (K > B) {
		cout << "TIDAK\n";
		return 0;
	}

	cout << "YA\n";
	if (Q == 1) {
		vector<int> ans(N);

		int cur = 1;
		for (vector<int> &v : G) {
			ll cs = sum(1ll, (ll) v.size() - 1);
			if (K == 0) {
				for (int x : v) ans[x] = cur++;
			}
			else if (K >= cs) {
				K -= cs;
				for (int i = 0; i < (int) v.size(); i++) {
					ans[v[i]] = cur + ((int) v.size() - i - 1);
				}
				cur += (int) v.size();
			}
			else {
				ll lo = 1, hi = (ll) v.size(), id = (ll) v.size();
				while(lo <= hi) {
					ll md = (lo + hi) >> 1;
					if (sum(md, (ll) v.size() - 1) <= K) {
						id = md, hi = md - 1;
					} else {
						lo = md + 1;
					}
				}

				vector<int> aux;
				for (int i = (int) v.size(); i > id; i--) {
					aux.push_back(i + cur - 1);
				}

				for (int i = 1; i < id; i++) {
					if (id - i == K - sum(id, (ll) v.size() - 1)) {
						aux.push_back(id + cur - 1);
					}
					aux.push_back(i + cur - 1);
				}

				if (K == sum(id, (ll) v.size() -1 )) aux.push_back(id + cur - 1);

				for (int i = 0; i < (int) v.size(); i++) {
					ans[v[i]] = aux[i];
				}

				K = 0, cur += (int) v.size();
			}
		}

		for (int a : ans) {
			cout << a << ' ';
		}
		cout << '\n';
	}
}
