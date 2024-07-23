#include<bits/stdc++.h>
using namespace std;

// dp[i] := maximum number of safe day from day 1 to day i with position A[i] at day i
// pref[i] := max(dp[j]), 1 <= j <= i
// mx[i] := max(dp[j]), for every j:= a[i] - i
// dp[i] := max(pref[i - a[i]], mx[a[i] - i]) + 1
// ans = N - pref[N]

signed main() {
	int N;
	cin >> N;
	
	vector<int> A(N+1);
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}

	vector<int> dp(N+1, 0), pref(N+1, 0);
	map<int, int> mx;

	for (int i = 1; i <= N; i++) {
		if (i >= A[i]) {
			dp[i] = pref[i - A[i]] + 1;
			//cout << i << ' ';
		}
		if (mx.find(A[i] - i) != mx.end() && i >= A[i]) dp[i] = max(dp[i], mx[A[i] - i] + 1);
		pref[i] = max(pref[i - 1], dp[i]);
		mx[A[i] - i] = max(mx[A[i] - i], dp[i]);
	}
	//cout << '\n';

	//for (int i = 1; i <= N; i++) cout << dp[i] << ' '; cout << '\n';
	//for (int i = 1; i <= N; i++) cout << pref[i] << ' '; cout << '\n';

	cout << N - pref[N] << '\n';
}
