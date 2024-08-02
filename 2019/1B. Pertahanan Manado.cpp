#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

using ll = long long;

// dp[i] := cost minimum sehingga jenis obat dari 1 sampai i sudah terbeli

const int mxn = 2e5+48;
int n, m, s;
vector<pair<int, int>> e[mxn];
ll dp[mxn], st[4 * mxn];

void upd(int v, int tl, int tr, int id, ll val) {
	if (tl == tr) {
		st[v] = val;
	} else {
		int tm = (tl + tr) >> 1;
		if (id <= tm) upd(2 * v + 1, tl, tm, id, val);
		else upd(2 * v + 2, tm + 1, tr, id, val);
		st[v] = min(st[2 * v + 1], st[2 * v + 2]);
	}
}

ll que(int v, int tl, int tr, int l, int r) {
	if (tl > r || tr < l) {
		return 1e18;
	} else if (tl >= l && tr <= r) {
		return st[v];
	} else {
		int tm = (tl + tr) >> 1;
		return min(que(2 * v + 1, tl, tm, l, r),
				que(2 * v + 2, tm + 1, tr, l, r));
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 4*mxn; i++) st[i] = 1e18;
	for (int i = 0; i < mxn; i++) dp[i] = 1e18;

	cin >> n >> m >> s;
	for (int i = 0; i < m; i++) {
		int a, b, p;
		cin >> a >> b >> p;
		e[b].push_back(make_pair(a, p));
	}

	dp[0] = 0;
	upd(0, 0, n-1, 0, 0);

	for (int i = 1; i <= n; i++) {
		dp[i] = s + dp[i-1];
		for (auto [j, c] : e[i]) {
			dp[i] = min(dp[i], que(0, 0, n-1, j-1, i-1) + c);
		}
		upd(0, 0, n-1, i, dp[i]);
	}

	cout << dp[n] << '\n';
}
