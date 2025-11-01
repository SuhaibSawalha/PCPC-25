#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, k;
  cin >> n >> m >> k;
  vector pref(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int a;
      cin >> a;
      pref[i][j] = (a > k ? 1 : -1) + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
  }
  int sz = -1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int t = sz + 1; i + t <= n && j + t <= m; ++t) {
        int cnt = pref[i + t][j + t] - pref[i - 1][j + t] - pref[i + t][j - 1] + pref[i - 1][j - 1];
        if (cnt <= 0) {
          sz = t;
        }
      }
    }
  }
  cout << (sz + 1) * (sz + 1);

  return 0;
}