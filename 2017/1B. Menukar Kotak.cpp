#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

const int mxn = 300, mxk = 3000, inf = 2e18;
string sub;
vector<int> ones;
int n, k, ans, p[mxn], dp[mxn][mxk], pref_min[mxn][mxk];
// definition : dp[v][w] 	   := minimum operation with last index 
// 								  taken 'v' and total sum is 'w'.
// 				pref_min[v][w] := minimum of dp[0][w], ..., dp[v][w].

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> sub >> n >> k;

	k = min(k, n * (n - 1) / 2);

	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		p[i] = c-'0';
	}

	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if (c == '1') ones.push_back(i);
	}

	// base case: pref_min[v][w] = (w == 0 ? 0 : inf);
	for (int v = 0; v < n; v++) {
		for (int w = 0; w <= 9 * n; w++) {
			pref_min[v][w] = w == 0 ? 0 : inf;
		}
	}

	// transition
	for (int u = 0; u < (int) ones.size(); u++) {
		for (int v = 0; v < n; v++) {
			dp[v][0] = 0;
		}
		for (int w = 1; w <= 9 * n; w++) {
			// base case
			dp[0][w] = (p[0] == w ? ones[u] : inf);
			if (dp[0][w] <= k) {
				ans = max(ans, w);
			}
			for (int v = 1; v < n; v++) {
				// if current sum is greater than current val.
				// and 'w - p[v]' has occured before.
				if (w >= p[v] && pref_min[v-1][w-p[v]] != inf) {
					dp[v][w] = pref_min[v-1][w-p[v]] + abs(v-ones[u]);
				}
				// otherwise
				else {
					dp[v][w] = inf;
				}
				// if dp[v][w] <= k, then 'w' is a candidate answer
				if (dp[v][w] <= k) {
					ans = max(ans, w);
				}
			}
		}
		// change pref_min to current dp.
		for (int w = 0; w <= 9 * n; w++) {
			pref_min[0][w] = dp[0][w];
			for (int v = 1; v < n; v++) {
				pref_min[v][w] = min(pref_min[v-1][w], dp[v][w]);
			}
		}
	}

	cout << ans << '\n';
}
