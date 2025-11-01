#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve() {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    ll cost = 0, L = 0, R = -1;
    int rep[26]{};
    auto calc_cost = [&](int l, int r) {
        while (R < r) {
            R++;
            int c = s[R] - 'a';
            rep[c]++;
            for (int i = c + 1; i < 26; i++) cost += rep[i];
        }
        while (L > l) {
            L--;
            int c = s[L] - 'a';
            rep[c]++;
            for (int i = 0; i < c; i++) cost += rep[i];
        }
        while (R > r) {
            int c = s[R] - 'a';
            rep[c]--;
            for (int i = c + 1; i < 26; i++) cost -= rep[i];
            R--;
        }
        while (L < l) {
            int c = s[L] - 'a';
            rep[c]--;
            for (int i = 0; i < c; i++) cost -= rep[i];
            L++;
        }
    };
    vector<ll> dp1(n + 1, 1e18), dp2(n + 1, 1e18);
    function<void(int, int, int, int)> dac = [&](int a, int b, int c, int d) {
        if (a > b) return;
        array<ll, 2> best = {(ll)1e18, -1};
        int mid = (a + b) / 2;
        for (int j = c; j <= min(d, mid - 1); j++) {
            calc_cost(j, mid - 1);
            ll curr = dp1[j] + cost;
            if (curr <= best[0]) {
                best[0] = curr;
                best[1] = j;
            }
        }
        dp2[mid] = best[0];
        int op = best[1];
        dac(a, mid - 1, c, op);
        dac(mid + 1, b, op, d);
    };
    dp1[0] = 0;
    for (int i = 0; i < k; i++) {
        dac(i + 1, n, i, n - 1);
        swap(dp1, dp2);
    }
    cout << dp1[n] << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
