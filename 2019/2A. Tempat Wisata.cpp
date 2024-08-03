#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

const int mxn = 2e5+5;
int n, m, s[mxn], e[mxn], p[mxn], ans[mxn], pref[mxn];

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> e[i];
		p[i] = i;
	}

	sort(p, p+n, [&](int i, int j) {
		return s[i] == s[j] ? e[i] < e[j] : s[i] < s[j];
	});


	for (int i = 0; i < n; i++) {
		int lo = i+1, hi = n-1, id = i;
		while (lo <= hi) {
			int j = (lo + hi) >> 1;
			if (s[p[j]] <= e[p[i]]) {
				lo = j + 1;
				id = j;
			} else {
				hi = j - 1;
			}
		}
		ans[p[i]] = id - i;
		if (id >= i + 1) {
			pref[i+1]++;
			pref[id+1]--;
		}
	}

	for (int i = 1; i < n; i++) {
		pref[i] = pref[i] + pref[i-1];
		ans[p[i]] += pref[i];
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << '\n';
	}
}
