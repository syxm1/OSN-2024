#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

using ll = long long;

const int mxn = 105;
int n;
vector<pair<int, int>> adj[mxn];

/*
 * a vs b:
 * 	0 := tied
 * 	1 := a win
 * 	-1 := a lose
 */

int combine(int pre, int cur) {
	int ret = pre + cur;
	if (ret == 2) ret = -1;
	if (ret == -2) ret = 1;
	return ret;
}

int dfs(int s, int e) {
	stack<tuple<int, int, int>> st;
	for (auto [i, w] : adj[s]) {
		st.push(make_tuple(i, s, w));
	}
	
	while (!st.empty()) {
		auto [i, h, d] = st.top();
		st.pop();

		if (i == e) return d;

		for (auto [j, w] : adj[i]) {
			if (j != h)	{
				st.push(make_tuple(j, i, combine(d, w)));
			}
		}
	}

	return 1e9;
}

void ask(int a, int b) {
	int d = dfs(a, b);

	if (d != 1e9) {
		if (d == -1) cout << b+1 << ' ' << "MENANG" << endl;
		else if (d == 1) cout << a+1 << ' ' << "MENANG" << endl;
		else cout << "SERI" << endl;
		cout.flush();
		return;
	}

	cout << "PASS" << endl;
	cout.flush();

	string s1, s2;
	cin >> s1;

	if (s1 == "SERI") {
		adj[a].push_back(make_pair(b, 0));
		adj[b].push_back(make_pair(a, 0));
	}
	else {
		cin >> s2;
		int win = stoi(s1);
		if (--win == a) {
			adj[a].push_back(make_pair(b, 1));
			adj[b].push_back(make_pair(a, -1));
		} else {
			adj[a].push_back(make_pair(b, -1));
			adj[b].push_back(make_pair(a, 1));
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string sub;
	cin >> sub;

	cin >> n;
	for (int i = 0; i < n * (n - 1) / 2; i++) {
		int a, b;
		cin >> a >> b;
		ask(--a, --b);
	}
}
