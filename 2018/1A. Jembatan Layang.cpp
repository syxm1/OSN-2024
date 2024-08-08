#include <bits/stdc++.h>
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
        if (lf[i][0] == rg[i][2] && lf[i][2] == rg[i][0]) {
            ans = (((ans * fac[lf[i][0]]) % mod) * fac[lf[i][2]]) % mod;
            if (lf[i][1] && rg[i][1]) {
                ans = (ans * (lf[i][0] + lf[i][1] + lf[i][2])) % mod;
            }
        }
        else if (rg[i][0] == lf[i][2] - 1 && rg[i][1]) {
            ans = (((ans * fac[rg[i][0] + 1]) % mod) * fac[rg[i][2]]) % mod;
        }
        else if (rg[i][0] == lf[i][2] + 1 && lf[i][1]) {
            ans = (((ans * fac[lf[i][0]]) % mod) * fac[lf[i][2] + 1]) % mod;
        }
        else if (lf[i][0] == rg[i][2] - 1 && lf[i][1]) {
            ans = (((ans * fac[lf[i][0] + 1]) % mod) * fac[lf[i][2]]) % mod;
        }
        else if (lf[i][0] == rg[i][2] + 1 && rg[i][1]) {
            ans = (((ans * fac[rg[i][0]]) % mod) * fac[rg[i][2] + 1]) % mod;
        }
        else {
            ans = 0;
            break;
        }
    }

    cout << ans << '\n';
}
