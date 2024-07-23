#include<bits/stdc++.h>
using namespace std;

string que() {
	string s;
	cin >> s;
	return s;
}

signed main() {
	int N, T;
	cin >> N >> T;

	int lo = 1, hi = N;

	vector<int> S;
	S.push_back((lo + hi) / 2);
	S.push_back((lo + hi) / 2 + 1);

	for (int i = 0; i < T; i++) {
		int cur = S[S.size() - 2];
		if (S[i] == S[i-1]) S[i]++;
		cout << min(S[i], N) << '\n';
		cout.flush();
		if (i>0) {
			string q = que();
			if (q == "KEKECILAN") {
				lo = min(cur+1, N);
			} else if (q == "KEBESARAN") {
				hi = max(cur-1, 1);
			} else {
				return 0;
			}
			S.push_back((lo + hi) / 2);
		}
	}
}
