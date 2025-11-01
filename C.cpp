#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  string s;
  cin >> n >> s;
  auto calc = [&](string w) {
    int res = 0;
    for (int i = 0; i < n; ++i) {
      res += s[i] != w[i % 3];
    }
    return res;
  };
  int mit = min({
    calc("mit"),
    calc("itm"),
    calc("tmi")
  });
  int mti = min({
    calc("mti"),
    calc("tim"),
    calc("imt")
  });
  if (mit == mti) {
    cout << "FAKE";
  } else if (mit < mti) {
    cout << "mit " << mit;
  } else {
    cout << "mti " << mti;
  }

  return 0;
}