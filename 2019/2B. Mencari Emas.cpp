#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define trace(x) cerr << #x << ": " << x << endl;
#else
#define trace(x) 37
#endif

#define int long long

/*
 * f(x, y) = x + y (/)
 * g(x, y) = x - y (\)
 *
 * x + y = f
 * x - y = g
 * --------- +
 *     x = (f + g) / 2
 * <-> y = f - x
 */

int r, c, q;

int ask(int x, int y) {
	cout << "? " << x << ' ' << y << endl;
	cout << flush;
	int ret; cin >> ret; return ret;
}

bool inside(int x, int y) {
	return x > 0 && x <= r && y > 0 && y <= c;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> r >> c >> q;
	
	int flt = 1 + 1 + ask(1, 1);
	int frb = r + c - ask(r, c);
	int glb = r - 1 - ask(r, 1);
	int grt = 1 - c + ask(1, c);

	int xa, ya, xb, yb;

	xa = (flt + glb) >> 1;
	ya = flt - xa;
	xb = (frb + grt) >> 1;
	yb = frb - xb;

	if ((flt + glb) % 2 == 0 && inside(xa, ya)) {
		if (ask(xa, ya) == 0 && inside(xb, yb)) {
			// do nothing
		}
		else {
			xa = (flt + grt) >> 1;
			ya = flt - xa;
			xb = (frb + glb) >> 1;
			yb = frb - xb;
		}
	}
	else {
		xa = (flt + grt) >> 1;
		ya = flt - xa;
		xb = (frb + glb) >> 1;
		yb = frb - xb;
	}

	cout << "! " << xa << ' ' << ya << ' ' << xb << ' ' << yb << '\n';
}
