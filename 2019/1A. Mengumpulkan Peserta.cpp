#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

using ll = long long;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int r, c, sum = 0;
	cin >> r >> c;

	vector<vector<int>> v(r+1, vector<int>(c+1, 0));
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			char c;
			cin >> c;
			if (c == '1') v[i][j] = 1, sum++;
			v[i][j] = v[i][j] + v[i-1][j] + v[i][j-1] - v[i-1][j-1];
		}
	}

	int ans = 2e9;
	for (int f = 1; f * f <= sum; f++) {
		if (sum % f != 0) continue;
		int x = f, y = sum / f;
		for (int i = 1; i + x - 1 <= r; i++) {
			for (int j = 1; j + y - 1 <= c; j++) {
				int cur = v[i+x-1][j+y-1] - v[i+x-1][j-1] - v[i-1][j+y-1] + v[i-1][j-1];
				ans = min(ans, sum - cur);
			}
		}
		if (x == y) continue;
		swap(x, y);
		for (int i = 1; i + x - 1 <= r; i++) {
			for (int j = 1; j + y - 1 <= c; j++) {
				int cur = v[i+x-1][j+y-1] - v[i+x-1][j-1] - v[i-1][j+y-1] + v[i-1][j-1];
				ans = min(ans, sum - cur);
			}
		}
	}

	cout << (ans == 2e9 ? -1 : ans) << '\n';
}
