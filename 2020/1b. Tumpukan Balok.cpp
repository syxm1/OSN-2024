#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, q, k;
vector<int> h, pref;
vector<pair<int, int>> st;
vector<tuple<int, int, int>> v;

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) return a;
    if (a.first > b.first) return b;
    return make_pair(a.first, min(a.second, b.second));
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        st[v] = make_pair(h[tl], tl);
    } else {
        int tm = (tl + tr) >> 1;
        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm + 1, tr);
        st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
    }
}

pair<int, int> que(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) {
        return make_pair(1e18, 1e18);
    } else if (tl >= l && tr <= r) {
        return st[v];
    } else {
        int tm = (tl + tr) >> 1;
        return merge(que(2 * v + 1, tl, tm, l, r), que(2 * v + 2, tm + 1, tr, l, r));
    }
}

pair<int, int> que(int l, int r) {
    return que(0, 0, n - 1, l, r);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    h.resize(n);
    st.resize(4*n+5);

    for (int i = 0; i < n; i++) cin >> h[i];

    build(0, 0, n - 1);

    stack<tuple<int, int, int>> dfs;

    pair<int, int> p = que(0, n-1);
    if (p.first > 0) v.push_back(make_tuple(0, n-1, p.first));
    if (p.second + 1 < n) dfs.push(make_tuple(p.second + 1, n-1, p.first));
    if (p.second - 1 >= 0) dfs.push(make_tuple(0, p.second - 1, p.first));

    while (!dfs.empty()) {
        auto [l, r, pre] = dfs.top();
        dfs.pop();

        p = que(l, r);
        if (p.first - pre > 0) v.push_back(make_tuple(l, r, p.first - pre));

        if (p.second + 1 <= r) dfs.push(make_tuple(p.second + 1, r, p.first));
        if (p.second - 1 >= l) dfs.push(make_tuple(l, p.second - 1, p.first));
    }

    pref.resize(v.size());
    for (int i = 0; i < (int) v.size(); i++) {
        auto [l, r, c] = v[i];
        if (i == 0) {
            pref[i] = (r - l + 1) * c;
        } else {
            pref[i] = pref[i-1] + (r - l + 1) * c;
        }
    }

    cin >> q;
    while (q--) {
        cin >> k;
        
        int lo = 0, hi = v.size() - 1, id = -1;
        while (lo <= hi) {
            int md = (lo + hi) >> 1;
            int cl = (md == 0 ? 0 : pref[md-1]), cr = pref[md];
            if (cl < k && k <= cr) {
                id = md;
                break;
            } else if (k <= cl) {
                hi = md - 1;
            } else {
                lo = md + 1;
            }
        }

        auto [l, r, c] = v[id];
        int len = r - l + 1;
        int pos = (k - (id == 0 ? 0 : pref[id-1])) % len;
        int ans = (pos == 0 ? r : l + pos - 1);

        cout << ans + 1 << '\n';
    }
}
