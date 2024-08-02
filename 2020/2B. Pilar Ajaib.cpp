#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

const int mxn = 1e5+5, inf = 2e15;
int n, xs, ys, xf, yf, x[mxn], y[mxn], r[mxn], c[mxn], idx[mxn], idy[mxn], dist[mxn][2];
vector<int> adj[mxn][2];

// adj[i][0] := horizontal adjacent
// adj[i][1] := vertical adjacent
// dist[i][0] := distance if pillar i lighted horizontally
// dist[i][1] := distance if pillar i lighted vertically

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> xs >> ys >> xf >> yf;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> r[i] >> c[i];
	}
	x[n] = xf, y[n] = yf, r[n] = c[n] = 0, ++n;

	for (int i = 0; i < n; i++) {
		idx[i] = idy[i] = i;
	}

	sort(idx, idx + n, [&] (int i, int j) {
		return x[i] - r[i] == x[j] - r[j] 
			? x[i] + r[i] < x[j] + r[j] 
			: x[i] - r[i] < x[j] - r[j];
	});

	sort(idy, idy + n, [&] (int i, int j) {
		return y[i] - r[i] == y[j] - r[j] 
			? y[i] + r[i] < y[j] + r[j] 
			: y[i] - r[i] < y[j] - r[j];
	});

	int pre = -inf, pre_id = -1;
	for (int i = 0; i < n; i++) {
		int cur = idx[i];
		if (x[cur] - r[cur] <= pre) {
			adj[pre_id][1].push_back(cur);
			adj[cur][1].push_back(pre_id);
		}
		if (x[cur] + r[cur] >= pre) {
			pre = x[cur] + r[cur], pre_id = cur;
		}
	}

	pre = -inf, pre_id = -1;
	for (int i = 0; i < n; i++) {
		int cur = idy[i];
		if (y[cur] - r[cur] <= pre) {
			adj[pre_id][0].push_back(cur);
			adj[cur][0].push_back(pre_id);
		}
		if (y[cur] + r[cur] >= pre) {
			pre = y[cur] + r[cur], pre_id = cur;
		}
	}

	for (int i = 0; i < n; i++) {
		dist[i][0] = inf;
		dist[i][1] = inf;
	}

	// parameter: current pillar, current distance (cost), previous direction
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
	for (int i = 0; i < n; i++) {
		if (ys >= y[i] - r[i] && ys <= y[i] + r[i]) {
			dist[i][0] = 0;
			pq.push(make_tuple(i, dist[i][0], 0));
		}
	}

	while (!pq.empty()) {
		auto [cur, dis, ori] = pq.top();
		pq.pop();
		if (cur == n-1) {
			cout << dis << '\n';
			return 0;
		}
		if (dis > dist[cur][ori]) continue;
		for (int nxt : adj[cur][0]) {
			int cos = ori == 0 ? 0 : c[cur];
			if (dist[nxt][0] > dis + cos) {
				dist[nxt][0] = dis + cos;
				pq.push(make_tuple(nxt, dist[nxt][0], 0));
			}
		}
		for (int nxt : adj[cur][1]) {
			int cos = ori == 1 ? 0 : c[cur];
			if (dist[nxt][1] > dis + cos) {
				dist[nxt][1] = dis + cos;
				pq.push(make_tuple(nxt, dist[nxt][1], 1));
			}
		}
	}

	cout << -1 << '\n';
}
