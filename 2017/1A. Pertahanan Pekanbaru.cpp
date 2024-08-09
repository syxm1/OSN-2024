#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

priority_queue<int, vector<int>, greater<int>> pq;
int n, sd, sm, p, k, l, ans;
bool pass = 1;
string sub;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> sub >> n >> sd >> sm;
	for (int i = 0; i < n - 1; i++) {
		cin >> p >> k >> l;
		if (sd < p) {
			while (!pq.empty() && sd < p) {
				sd++, ans += pq.top();	
				pq.pop();
			}
		}
		if (sd < p) pass = 0;
		if (k >= l) sd++, ans += l;
		else { pq.push(l - k); ans += k; }
	}

	while (!pq.empty() && sd < sm) {
		sd++, ans += pq.top();
		pq.pop();
	}

	cout << (sd >= sm && pass ? ans : -1) << '\n';
}
