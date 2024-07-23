#include<bits/stdc++.h>

int N, P, Q, T, W, X, Y;
std::vector<int> one, two;

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> N >> P;
    for (int i = 0; i < P; i++) {
        std::cin >> T >> W;
        if (T==1) one.push_back(W);
        else two.push_back(W);
    }

    std::sort(one.begin(), one.end());
    std::sort(two.begin(), two.end());

    std::cin >> Q;
    while (Q--) {
        std::cin >> X >> Y;
        if (X < Y) std::swap(X, Y);
        int satu = (int) one.size() - (std::lower_bound(one.begin(), one.end(), X) - one.begin());
        int dua = std::upper_bound(two.begin(), two.end(), Y) - two.begin();
        std::cout << (satu + dua) % 2 << '\n';
    }
}
