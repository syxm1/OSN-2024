#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 135
#endif

using ll = long long;

const int mxN = 2e5+5;

int N, Q, H[mxN], st[3*mxN], mn[3*mxN], mx[3*mxN];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		st[v] = H[tl];
		mn[v] = tl - H[tl];
		mx[v] = tl + H[tl];
	} else {
		int tm = (tl + tr) >> 1;
		build(2*v+1, tl, tm);
		build(2*v+2, tm+1, tr);
		st[v] = max(st[2*v+1], st[2*v+2]);
		mn[v] = min(mn[2*v+1], mn[2*v+2]);
		mx[v] = max(mx[2*v+1], mx[2*v+2]);
	}
}

int get_peak(int v, int tl, int tr, int l, int r) {
	if (tl > r || tr < l) {
		return -1;
	} else if (l <= tl && tr <= r) {
		return st[v];
	} else {
		int tm = (tl + tr) >> 1;
		int lf = get_peak(2*v+1, tl, tm, l, r);
		int rg = get_peak(2*v+2, tm+1, tr, l, r);
		return max(lf, rg);
	}
}

int get_left(int v, int tl, int tr, int l, int r) {
	if (tl > r || tr < l) {
		return 2e9;
	} else if (l <= tl && tr <= r) {
		return mn[v];
	} else {
		int tm = (tl + tr) >> 1;
		int lf = get_left(2*v+1, tl, tm, l, r);
		int rg = get_left(2*v+2, tm+1, tr, l, r);
		return min(lf, rg);
	}
}

int get_right(int v, int tl, int tr, int l, int r) {
	if (tl > r || tr < l) {
		return -1;
	} else if (l <= tl && tr <= r) {
		return mx[v];
	} else {
		int tm = (tl + tr) >> 1;
		int lf = get_right(2*v+1, tl, tm, l, r);
		int rg = get_right(2*v+2, tm+1, tr, l, r);
		return max(lf, rg);
	}

}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}
	
	build(0, 0, N-1);

	cin >> Q;
	while (Q--) {
		int S, T;
		cin >> S >> T;
		--S, --T;
		
		bool swapped = 0;
		if (S > T) {
			swap(S, T);
			swapped = 1;
		}

		int pk = get_peak(0, 0, N-1, S, T);
		int lf = get_left(0, 0, N-1, S, T) + pk;
		int rg = get_right(0, 0, N-1, S, T) - pk;

		if (!swapped) {
			cout << 4ll * (pk - H[S]) + 2ll * (rg - lf) + (pk - H[T]) << '\n';
		} else {
			cout << 4ll * (pk - H[T]) + 2ll * (rg - lf) + (pk - H[S]) << '\n';
		}
	}
}
