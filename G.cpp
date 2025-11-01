#include <bits/stdc++.h>
using namespace std;
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a, b, c;
  cin >> a >> b >> c;
  cout << a + b + c - max({a, b, c});

  return 0;
}