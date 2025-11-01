#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int add(int a, int b) {
  return (a + b) % mod;
}
int mul(int a, int b) {
  return int64_t(a) * b % mod;
}
int fastpow(int v, int p) {
  int res = 1;
  while (p) {
    if (p % 2) {
      res = mul(res, v);
    }
    p /= 2;
    v = mul(v, v);
  }
  return res;
}
int modInv(int v) {
  return fastpow(v, mod - 2);
}

vector<int> fact, factInv;
void Inv(int N) {
  fact.resize(N + 1);
  factInv.resize(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; ++i) {
    fact[i] = mul(fact[i - 1], i);
  }
  factInv[N] = modInv(fact[N]);
  for (int i = N - 1; ~i; --i) {
    factInv[i] = mul(factInv[i + 1], (i + 1));
  }
}
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const int N = 5e5 + 5;
  Inv(N);

  vector<int> dp(N);
  dp[0] = 1;
  for (int i = 1; i < N; ++i) {
    for (int j = 1; j <= i; j *= 2) {
      dp[i] = add(dp[i], mul(mul(fact[i - 1], factInv[i - j]), dp[i - j]));
    }
  }

  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    cout << dp[n] << "\n";
  }

  return 0;
}