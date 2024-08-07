#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

const int mxn = 1e5+69, mod = 1e9+7;
int n, k, ans = 1, h[mxn], fac[mxn], lf[mxn][3], rg[mxn][3];
string subs;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	fac[0] = 1;
	for (int i = 1; i < mxn; i++) {
		fac[i] = (fac[i-1] * i) % mod;
	}

	cin >> subs >> n >> k;
    /* brute-force
	if (n <= 10) {
	vector<int> h(k), a(n), b(n);
		for (int i = 0; i < k; i++) {
			cin >> h[i];
			h[i]--;
		}
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			--a[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> b[i];
			--b[i];
		}

		vector<int> perm(n);
		iota(perm.begin(), perm.end(), 0);

		ans = 0;
		do {
			bool ok = 1;
			for (int i = 0; i < n; i++) {
				int cur = perm[i];
				if (a[cur] != b[i]) ok = 0;
				if (cur < h[a[cur]] && i < h[a[cur]]) { ok = 0; }
				if (cur > h[a[cur]] && i > h[a[cur]]) { ok = 0; }
			}
			ans += ok;
		} while (next_permutation(perm.begin(), perm.end()));

		cout << ans << '\n';
		return 0;
	}
	*/

	for (int i = 1; i <= k; i++) {
		cin >> h[i];
	}
	for (int i = 1; i <= n; i++) {
	 	int a; cin >> a;
	 	if (i < h[a]) lf[a][0]++;
	 	if (i == h[a]) lf[a][1]++;
	 	if (i > h[a]) lf[a][2]++;
	}
	for (int i = 1; i <= n; i++) {
		int b; cin >> b;
		if (i < h[b]) rg[b][0]++;
		if (i == h[b]) rg[b][1]++;
		if (i > h[b]) rg[b][2]++;
	}

	for (int i = 1; i <= k; i++) {
		// jumlah lantai kiri dibawah == jumlah lantai kanan diatas dan,
		// jumlah lantai kiri diatas == jumlah lantai kanan dibawah.
		if (lf[i][0] == rg[i][2] && lf[i][2] == rg[i][0]) {
			ans = ans * fac[lf[i][0]] % mod * fac[lf[i][2]] % mod;
			// jika ada lantai yang terletak di jembatan, maka dapat dialokasikan kemanapun
			if (lf[i][1] && rg[i][1]) {
				ans = ans * (lf[i][0] + lf[i][1] + lf[i][2]) % mod;
			}
		}
		// jika jumlah lantai di kanan atas lebih satu daripada kiri bawah, maka 
		// dapat diisi jika ada lantai yang terletak pada jembatan.
		else if (rg[i][2] - lf[i][0] == 1 && lf[i][1]) {
			ans = (((ans * fac[rg[i][2]]) % mod) * fac[lf[i][2]]) % mod;
		}
		// jika jumlah lantai di kanan bawah lebih satu daripada kiri atas, maka
		// dapat diisi jika ada lantai yang terletak pada jembatan.
		else if (rg[i][0] - lf[i][2] == 1 && lf[i][1]) {
			ans = (((ans * fac[rg[i][0]]) % mod) * fac[lf[i][0]]) % mod;
		}
		// jika jumlah lantai di kiri bawah lebih satu daripada kanan atas, maka
		// dapat dialokasikan ke lantai yang terletak pada jembatan (jika ada)
		else if (lf[i][0] - rg[i][2] == 1 && rg[i][1]) {
			ans = (((ans * fac[lf[i][0]]) % mod) * fac[rg[i][0]]) % mod;
		}
		// jika jumlah lantai di kanan bawah lebih satu daripada kanan atas, maka
		// dapat dialokasikan ke lantai yang terletak pada jembatan (jika ada)
		else if (lf[i][2] - rg[i][0] == 1 && rg[i][1]) {
			ans = (((ans * fac[lf[i][2]]) % mod) * fac[rg[i][2]]) % mod;
		}
		// selain semua kasus diatas, maka tidak ada konfigurasi yang mungkin.
		else {
			ans = 0;
			break;
		}
		
	}
	cout << ans << '\n';
}
