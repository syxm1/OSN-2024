#include<bits/stdc++.h>
using namespace std;

using ll = long long;

signed main() {
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<ll> H(N);
    for (ll &x : H) cin >> x;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(N, 0);
    vector<vector<pair<ll, int>>> S;

    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;

        S.push_back(vector<pair<ll, int>>{});

        stack<int> dfs;
        dfs.push(i);
        vis[i] = 1;

        while(!dfs.empty()) {
            int cur = dfs.top();
            dfs.pop();

            S.back().push_back(make_pair(H[cur], cur));

            for (int nxt : adj[cur]) {
                if (!vis[nxt]) {
                    vis[nxt] = 1;
                    dfs.push(nxt);
                }
            }
        }

        sort(S.back().begin(), S.back().end());
    }


    if ((int) S.size() == 1) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    if (((int) S.size() - 1) * 2 > N) {
        cout << -1 << '\n';
        return 0;
    }

    vector<pair<pair<ll, int>, int>> V;
    vector<vector<int>> G(S.size());

    ll C = 0;
    for (int i = 0; i < (int) S.size(); i++) {
        C += S[i][0].first;
        G[i].push_back(S[i][0].second);
        for (int j = 1; j < (int) S[i].size(); j++) {
            V.push_back(make_pair(S[i][j], i));
        }
    }

    sort(V.begin(), V.end());

    for (int i = 0; i < (int) S.size() - 2; i++) {
        C += V[i].first.first;
        G[V[i].second].push_back(V[i].first.second);
    }

    cout << C << '\n';

    vector<int> single;
    vector<vector<int>> multi;
    vector<pair<int, int>> ans;

    for (int i = 0; i < S.size(); i++) {
        if (G[i].size() == 1) {
            single.push_back(G[i][0]);
        } else if (G[i].size() > 1) {
            multi.push_back(G[i]);
        }
    }

    sort(G.begin(), G.end(), [&] (const vector<int> &a, const vector<int> &b) {
        return a.size() > b.size();
    });

    while (!single.empty() && !multi.empty()) {
        vector<int> &a = multi.back();
        int u = a.back(), v = single.back();
        ans.push_back(make_pair(u, v));

        a.pop_back();
        single.pop_back();

        if (a.size() == 1) {
            single.push_back(a[0]);
            multi.pop_back();
        }
    }

    while (!single.empty()) {
        int u = single[single.size()-1], v = single[single.size()-2];
        ans.push_back(make_pair(u, v));
        single.pop_back();
        single.pop_back();
    }

    while (!multi.empty()) {
        while(!multi.back().empty()) {
            int u = multi.back().back();
            int v = multi[multi.size()-2].back();
            multi.back().pop_back();
            multi[multi.size()-2].pop_back();
            ans.push_back(make_pair(u, v));
        }
    }

    cout << ans.size() << '\n';
    for (auto [u, v] : ans) {
        cout << u+1 << ' ' << v+1 << '\n';
    }
}


/*
15 15 1
1 6 9 1 6 10 2 6 8 1 7 10 3 4 5
1 2
2 3
1 3
4 6
5 6
4 5
7 9
7 8
8 9
10 12
11 12
10 11
13 14
13 15
14 15
*/
