#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, k;
  string s;
  cin >> n >> k >> s;
  vector<pair<string, int>> w(k);
  vector ok(n, vector<bool>(k));
  for (int i = 0; i < k; ++i) {
    cin >> w[i].first;
    w[i].second = i;
    for (int j = 0; j < n; ++j) {
      ok[j][i] = s.substr(j, w[i].first.size()) == w[i].first;
    }
  }
  sort(w.begin(), w.end());
  do {
    int j = 0;
    for (int i = 0; i < n && j < k; ++i) {
      if (ok[i][w[j].second]) {
        i += w[j].first.size() - 1;
        j += 1;
      }
    }
    if (j == k) {
      cout << "YES";
      return 0;
    }
  } while (next_permutation(w.begin(), w.end()));
  cout << "NO";

  return 0;
}