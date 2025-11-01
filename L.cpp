#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const int N = 1e7;
  vector<bool> ok(N + 1);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> suf(n);
  for (int i = n - 2; ~i; --i) {
    suf[i] = gcd(suf[i + 1], a[i + 1]);
  }
  int pref = 0;
  for (int i = 0; i < n; ++i) {
    ok[gcd(pref, suf[i])] = 1;
    pref = gcd(pref, a[i]);
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = i; j <= N; j += i) {
      if (ok[j]) {
        ok[i] = 1;
        break;
      }
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    if (n == 1) {
      cout << "YES\n";
    } else if (x > N) {
      cout << "NO\n";
    } else {
      cout << (ok[x] ? "YES\n" : "NO\n");
    }
  }

  return 0;
}