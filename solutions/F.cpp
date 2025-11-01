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
    int n;
    cin >> n;
    int64_t ans = 0;
    vector<int> odds(2);
    int odd = 0;
    for (int i = 0; i < n; ++i) {
      int a;
      cin >> a;
      odds[odd % 2] += 1;
      odd += a % 2;
      ans += odds[odd % 2];
    }
    cout << ans << "\n";
  }

  return 0;
}