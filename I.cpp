#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<int> a(n), freq(n + 1);
  set<int> st;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i <= n + 1; ++i) {
    st.insert(i);
  }
  array<int, 2> ans = {0, 0};
  int l = 0;
  for (int r = 0; r < n; ++r) {
    ++freq[a[r]];
    while (freq[a[r]] > 1) {
      --freq[a[l]];
      st.insert(a[l]);
      l += 1;
    }
    st.erase(a[r]);
    ans = max(ans, {*st.begin(), r - l + 1});
  }
  cout << ans[1];

  return 0;
}