#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#ifdef local
#define trace(x) cerr << #x << ": " << x << endl;
#define trace2(x, y) cerr << #x << ": " << x << ", " << #y << ": " << y << endl;
#else
#define trace(x) 135
#define trace2(x, y) 135
#endif

int N;
vector<int> A, B, ans;
vector<bool> trav;
vector<vector<int>> G(30);

struct DSU {
	vector<int> par, sz;
	vector<ll> val;

	DSU(int n) {
		sz.assign(n, 1);
		val.resize(n);
		par.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i;
			val[i] = B[i];
		}
	}

	int get(int x) {
		return par[x] = (par[x] == x ? x : get(par[x]));
	}

	void merge(int u, int v) {
		u = get(u), v = get(v);
		if (u != v) {
			if (sz[u] > sz[v]) swap(u, v);
			par[u] = v;
			sz[v] += sz[u];
			val[v] += val[u];
		}
	}
};

int msb(int x) {
	return 31 - __builtin_clz(x);
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;

	A.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		G[msb(A[i])].push_back(i);
	}

	B.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> B[i];
	}

	DSU S(N);

	trav.assign(30, 0);
	for (int i = 29; i >= 0; i--) for (int j : G[i]) {
		for (int k = i-1; k >= 0; k--) {
			if (!(A[j] & (1 << k)) && (int) G[k].size() != 0) {
				if (trav[k]) {
					S.merge(G[k][0], j);
				} else {
					trav[k] = 1;
					for (int l : G[k])
						S.merge(j, l);
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
		cout << S.val[S.get(i)] << " \n"[i==N-1];
}
