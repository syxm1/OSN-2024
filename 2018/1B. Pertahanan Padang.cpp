#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

int a, b, q;
string sub;
vector<int> v, pref;

bool check(int x, int y) {
	if (x == 0) return 0;
	if (y == 0) {
		v.push_back(x);
		return 1;
	}
	if (x > y) {
		v.push_back(x / (y + 1));
		return check(x % (y + 1), y);
	}
	else {
		v.push_back(y / x);
		return check(x, y % x);
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> sub >> a >> b >> q;

	if (check(a, b)) {
		cout << "MUNGKIN\n";

		reverse(v.begin(), v.end());

		pref.resize(v.size());
		for (int i = 0; i < (int) v.size(); i++) {
			pref[i] = v[i];
			if (i > 0) pref[i] += pref[i-1];
		}

		while (q--) {
			int l, r;
			cin >> l >> r;
			++l, ++r;
			if (r > pref[v.size() - 1]) {
				cout << "DI LUAR BATAS\n";
				continue;
			}
			// cari index terkanan dengan nilai prefix yang lebih kecil dari l
			int lo = -1, hi = (int) v.size(), lb = -1;
			while (lo <= hi) {
				int md = (lo + hi) >> 1;
				if (pref[md] < l) {
					lb = md;
					lo = md + 1;
				} else {
					hi = md - 1;
				}
			}
			lb++;

			int id = lb, rem = pref[lb] - l + 1, cnt = r - l + 1;
			while(cnt--) {
				if (id & 1) 
					cout << 0;
				else {
					cout << 1;
				}
				if (--rem == 0) {
					id++;
					rem = pref[id] - pref[id-1];
				}
			}
			cout << '\n';
		}
	} else {
		cout << "TIDAK MUNGKIN\n";
		while (q--) {
			int l, r;
			cin >> l >> r;
		}
	}
}

