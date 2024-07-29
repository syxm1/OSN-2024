include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 42
#endif

int query(int l, int r) {
	cout << "? " << l << ' ' << r << endl;
	int ret; cin >> ret; return ret;
}

signed main() {
	int T, N, Q;
	cin >> T >> N >> Q;

	int C[N+1];

	if (T == 1 || T == 2) {
		C[1] = 1;
		for (int i = 2, c = 1, pre = 1; i <= N; i++) {
			int cur = query(1, i);
			if (cur == pre) C[i] = c;
			else C[i] = ++c;
			pre = cur;
		}	
	}
	else if (T == 3 || T == 4) {
		C[1] = 1;
		for (int i = 1, c = 2; i < N; i++) {
			int prev2 = -1, prev3 = -1, prev4 = -1;

			set<int> s;
			for (int j = i; j >= 1; j--) {
				s.insert(C[j]);
				if ((int) s.size() == 2 && prev2 == -1) prev2 = j;
				if ((int) s.size() == 3 && prev3 == -1) prev3 = j;
				if ((int) s.size() == 4 && prev4 == -1) prev4 = j;
			}

			if (prev2 != -1) {
				if (query(prev2, i+1) == 2) {
					if (query(i, i+1) == 1) C[i+1] = C[i];
					else C[i+1] = C[prev2];
					continue;
				}
			} else {
				if (query(i, i+1) == 1) C[i+1] = C[i];
				else C[i+1] = c++;
				continue;
			}
			
			if (prev3 != -1) {
				if (query(prev3, i+1) == 3) C[i+1] = C[prev3];
				else {
					if (prev4 != -1) C[i+1] = C[prev4];
					else C[i+1] = c++;
				}
			} else {
				if (query(prev2, i+1) == 2) {
					if (query(i, i+1) == 1) C[i+1] = C[i];
					else C[i+1] = C[prev2];
				}
				else C[i+1] = c++;
			}
		}
	}
	else {
		memset(C, -1, sizeof(C));
		
		C[1] = 1;
		for (int i = 2, c = 2, pre = 1; i <= N; i++) {
			int cur = query(1, i);
			if (cur != pre) C[i] = c++;
			pre = cur;
		}

		for (int i = 2; i <= N; i++) {
			if (C[i] == -1) {
				int lo = 1, hi = i-1, j;
				while (lo <= hi) {
					int md = (lo + hi) >> 1;
					set<int> s;
					for (int k = i-1; k >= md; k--) s.insert(C[k]);
					int p = s.size(), q = query(md, i);
					if (p == q) {
						j = md, lo = md + 1;
					} else {
						hi = md - 1;
					}
				}
				C[i] = C[j];	
			}
		}
	}

	cout << "! ";
	for (int i = 1; i <= N; i++) {
		cout << C[i] << ' ';
	}
	cout << '\n';
}
