#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    int l = 1, r = 1e9;
    while (l < r) {
      int mid = (l + r) / 2;
      vector<int> die(n + 1);
      int alive = 0, ok = 1;
      for (int i = 0; i < n; ++i) {
        alive += 1;
        ok &= alive < k;
        die[min(n, i + (a[i] + mid - 1) / mid - 1)] += 1;
        alive -= die[i];
      }
      if (ok) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    cout << l << "\n";
  }

  return 0;
}