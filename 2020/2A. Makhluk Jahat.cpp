#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 135
#endif

#define int long long

const int mxK = 25, mxP = 105;

int n, k, S, mage[mxK], monster[mxP][mxK], dp[mxP][(1<<21)];

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;

	// get first magic config.
	for (int i = 0; i < 4; i++) {
		int s;
		cin >> s;
		--s;
		S ^= (1 << s);
	}
	// trace(S);

	// get ability
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			char c;
			cin >> c;
			if (c == '1') mage[i] ^= (1 << j);
		}
	}

	// get rooms
	int p = 0;
	for (int i = 0; i < n; i++) {
		int r;
		cin >> r;
		if (r == 1) {
			int a;
			cin >> a;
			monster[p][--a]++;
		} else {
			p++;
		}
	}

	/*
	for (int i = 0; i <= p; i++) {
		for (int j = 0; j < k; j++) {
			trace(i);
			trace(j);
			trace(monster[i][j]);
		}
	}
	*/

	// transition
	for (int i = p; i >= 0; i--) {
		for (int a = 0; a + 3 < k; a++) {
			for (int b = a + 1; b + 2 < k; b++) {
				for (int c = b + 1; c + 1 < k; c++) {
					for (int d = c + 1; d < k; d++) {
						int mask = ((1 << a) | (1 << b) | (1 << c) | (1 << d));

						dp[i][mask] = 0;
						for (int j = 0; j < k; j++) {
							int e = (1 << j);
							if ((mage[a] & e) || (mage[b] & e) || (mage[c] & e) || (mage[d] & e)) {
								dp[i][mask] += monster[i][j];
							}
						}

						if (i < p) {
							int mx = dp[i+1][mask];
							for (int j = 0; j < k; j++) {
								int e = (1 << j);
								if (!((e & (1 << a) || (e & (1 << b)) || (e & (1 << c)) || (e & (1 << d))))) {
									mx = max(mx, dp[i+1][((mask ^ (1 << a)) ^ e)]);
									mx = max(mx, dp[i+1][((mask ^ (1 << b)) ^ e)]);
									mx = max(mx, dp[i+1][((mask ^ (1 << c)) ^ e)]);
									mx = max(mx, dp[i+1][((mask ^ (1 << d)) ^ e)]);
								}
							}
							dp[i][mask] += mx;
						}
						// printf("dp(%d, %d, %d, %d, %d) = %d, mask = %d\n", i, a, b, c, d, dp[i][mask], mask);
					}
				}
			}
		}
	}

	// ans
	cout << dp[0][S] << '\n';
}
