#include<bits/stdc++.h>
using namespace std;

using ll = long long;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll N, Q;
    cin >> N >> Q;

    if (N <= 1000) {
        vector<ll> pref(N+1, 0);
        for (ll i = 1; i <= N; i++) {
            if (i & 1) pref[i] = pref[i-1] + (i + 1) / 2;
            else pref[i] = pref[i-1] + N + 1 - i / 2;
        }
        map<ll, ll> cnt;
        for (ll i = 1; i <= N; i++) {
            for (ll j = i; j <= N; j++) {
                cnt[pref[j] - pref[i-1]]++;
            }
        }
        while (Q--) {
            ll X; cin >> X;
            cout << cnt[X] << '\n';
        }
        return 0;
    }

    while (Q--) {
        ll X; cin >> X;
        ll ans = 0, pref = 0;
        map<ll, ll> cnt;
        cnt[0] = 1;
        for (ll i = 1; i <= N; i++) {
            if (i & 1) pref += (i + 1) / 2;
            else pref += N + 1 - i / 2;
            ans += cnt[pref - X];
            cnt[pref]++;           
        }
        cout << ans << '\n';
    }
}
