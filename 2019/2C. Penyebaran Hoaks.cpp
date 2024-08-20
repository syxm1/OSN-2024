#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

const int mxn = 2e5+5;
int n, s, q, t, a, b, p, par[mxn], sz[mxn];
vector<tuple<int, int, int>> v;

int get(int x) {
	return par[x] = par[x] == x ? x : get(par[x]);
}

void merge(int x, int y) {
	x = get(x), y = get(y);
	if (x != y) {
		if (sz[x] > sz[y]) swap(x, y);
		par[x] = y;
		sz[y] += sz[x];
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> s >> q;

	for (int i = 0; i < n; i++) {
		par[i] = i, sz[i] = 1;
		cin >> t;
		for (int j = 0; j < t; j++) {
			cin >> a >> b;
			v.push_back(make_tuple(a, b, i));
		}
	}

	sort(v.begin(), v.end());

	int mxr = -1, id_mxr = -1;
	for (int i = 0; i < (int) v.size(); i++) {
		auto [l,r,id_cur] = v[i];
		if (l > mxr) {
			mxr = r;
			id_mxr = id_cur;
		}
		merge(id_cur, id_mxr);
		if (r > mxr) {
			mxr = r;
			id_mxr = id_cur;
		}
	}

	while(q--) {
		cin >> p;
		cout << sz[get(--p)] << '\n';
	}
}
