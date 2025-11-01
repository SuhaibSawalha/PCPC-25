#include <bits/stdc++.h>
using namespace std;

const int B = 29;
struct BitTrie {
  struct node {
    node *child[2] = {};
    int size = 0;
  };
  node *root = new node;
 
  void insert(int n) {
    node *cur = root;
    for (int bit = B; ~bit; --bit) {
      int index = n >> bit & 1;
      if (!cur->child[index]) {
        cur->child[index] = new node;
      }
      cur = cur->child[index];
      ++cur->size;
    }
  }

  void erase(int n) {
    node *cur = root;
    for (int bit = B; ~bit; --bit) {
      int index = n >> bit & 1;
      cur = cur->child[index];
      --cur->size;
    }
  }
 
  // number of elements b => (a ^ b) > k
  int countXor(int a, int k) {
    int ans = 0;
    node *cur = root;
    for (int bit = B; ~bit; --bit) {
      int index_a = a >> bit & 1;
      int index_k = k >> bit & 1;
      if (index_k) {
        cur = cur-> child[index_a ^ 1];
      } else {
        if (cur-> child[index_a ^ 1] && cur-> child[index_a ^ 1]->size) {
          ans += cur->child[index_a ^ 1]->size;
        }
        cur = cur->child[index_a];
      }
      if (!cur || cur->size == 0) {
        return ans;
      }
    }
    return ans;
  }
};
    
int main() {

  #ifndef ONLINE_JUDGE
    freopen("Satoru", "r", stdin);
  #endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  BitTrie bit;

  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), p(n), pos(n + 1);
    for (int i = 0; i < n; ++i) {
      cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    int64_t ans = ((n + 1) ^ a[0] ^ a[n - 1]) > k;
    for (int rep = 0; rep < 2; ++rep) {
      reverse(a.begin(), a.end());
      reverse(p.begin(), p.end());
      for (int i = 0; i < n; ++i) {
        pos[p[i]] = i;
      }
      vector<vector<array<int, 2>>> take(n + 1);
      int mn = pos[1], mx = pos[1];
      for (int i = 2; i <= n; ++i) {
        if (mx < pos[i]) {
          for (int p = mx; p < pos[i]; ++p) {
            take[mn].push_back({i, a[p]});
          }
        }
        mn = min(mn, pos[i]);
        mx = max(mx, pos[i]);
      }
      int found = 0;
      for (int i = 0; i < n; ++i) {
        bit.insert(a[i]);
        found |= p[i] == 1;
        if (!found) {
          ans += bit.countXor(a[i] ^ 1, k);
        }
        for (auto &[m, t] : take[i]) {
          ans += bit.countXor(m ^ t, k);
        }
      }
      for (int i = 0; i < n; ++i) {
        bit.erase(a[i]);
      }
    }
    cout << ans << "\n";
  }    

  return 0;
}