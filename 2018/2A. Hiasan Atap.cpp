#include<bits/stdc++.h>
using namespace std;

#define int long long

const int mxn = 1e5+69;
int k, q, a[mxn], b[mxn], n;
string sub, s;

pair<int, int> f(int y) {
	if (y == 1) return make_pair(1, n);
	int l = 1, r = n;
	l += b[s.length()-1] * ((y-1) / ((int)s.length()));
	r -= a[s.length()-1] * ((y-1) / ((int)s.length()));
	int re = (y-1) % ((int)s.length()) - 1;
	l += b[re];
	r -= a[re];
	return make_pair(l, r);
}

bool intersect(int l1, int r1, int l2, int r2) {
	return l2 <= r1 && r2 >= l1;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> sub >> s >> k >> q;
	n = ((int) s.length()) * k + 1;
	for (int i = 0; i < (int) s.size(); i++) {
		if (s[i] == 'A') a[i]++;
		if (s[i] == 'B') b[i]++;
		if (i > 0) a[i] += a[i-1], b[i] += b[i-1];
	}
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		int lo = 1, hi = n, ans = -1;
		while (lo <= hi) {
			int md = (lo + hi) >> 1;
			auto [lf, rg] = f(md);
			if (intersect(l, r, lf, rg)) {
				ans = md;
				lo = md + 1;
			} else {
				hi = md - 1;
			}
		}
		cout << ans << '\n';
	}
}
