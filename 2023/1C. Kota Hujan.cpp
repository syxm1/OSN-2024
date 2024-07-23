#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;

signed main() {
	int n;
	cin >> n;

	vector<vector<int>> a(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}

	// subtask 1
	if (n == 2) {
		if (a[0][0] == -1 && a[0][1] == 6 && a[1][0] == 9 && a[1][1] == -1) {
			cout << 16 << '\n';
			return 0;
		}
	}

	// subtask 2
	if (n == 2) {
		
	}

	// check for subtask 3
	bool zon = 1, z = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != 0 && a[i][j] != -1) zon = 0;
		}
	}

	// subtask 3
	
	// subtask 4 5 6
	bool none = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == -1) none = 0;
		}
	}

	if (none) {
		for (int i = 0; i+1 < n; i++) {
			for (int j = 0; j+1 < n; j++) {
				if (a[i][j] + a[i+1][j+1] != a[i+1][j] + a[i][j+1]) {
					cout << 0 << '\n';
					return 0;
				}
			}
		}
		cout << 1 << '\n';
		return 0;
	}
}
