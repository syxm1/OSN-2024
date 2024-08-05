#include<stdio.h>

using ll = long long;

struct mx_pair {
	int mx1, mx2;
	void add(const int &c) {
		if (c > mx1) mx2 = mx1, mx1 = c;
		else if (c > mx2) mx2 = c;
	}
	int get_not(const int &x) {
		return x == mx1 ? mx2 : mx1;
	}
};

struct mn_pair {
	int mn1, mn2;
	void add(const int &c) {
		if (c < mn1) mn2 = mn1, mn1 = c;
		else if (c < mn2) mn2 = c;
	}
	int get_not(const int &x) {
		return x == mn1 ? mn2 : mn1;
	}
};

void swap(int &u, int &v) {
	int &w = u;
	u = v;
	v = w;
}

int min(const int &u, const int &v) {
	return u < v ? u : v;
}

int max(const int &u, const int &v) {
	return u > v ? u : v;
}

const int mxn = 1e5+5;
ll ans = 0;
int n, m, u, v;
mx_pair lf[mxn];
mn_pair rg[mxn];

signed main() {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++) {
		lf[i].mx1 = lf[i].mx2 = -1;
		rg[i].mn1 = rg[i].mn2 = n;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		--u, --v;
		if (u > v) swap(u, v);
		lf[v].add(u);
		rg[u].add(v);
	}

	for (int i = 0; i < n; i++) {
		if (lf[rg[i].mn1].mx1 == i) { // no adjacent of i and rg[i] between i and rg[i]
			int j = rg[i].mn1;
			int l = max(lf[i].mx1, lf[j].get_not(i));
			int r = min(rg[j].mn1, rg[i].get_not(j));
			ans += 2ll * (ll) (i - l) * (ll) (r - j); // pair node contribution
		}
		ans += (ll) (i - lf[i].mx1) * (ll) (rg[i].mn1 - i); // single node contribution
	}

	printf("%lld\n", ans);
}
