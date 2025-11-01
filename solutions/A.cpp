#include <bits/stdc++.h>
using namespace std;

struct LCA {

  int n;
  vector<int> depth, node2idx, idx2node, lg{-1};
  vector <vector<int>> sp;

  LCA (vector<vector<int>>& adj) {
    n = adj.size();
    depth.resize(n);
    node2idx.resize(n);
    function<void(int, int)> dfs = [&] (int u, int p) {
      node2idx[u] = idx2node.size();
      idx2node.push_back(u);
      for (int v : adj[u]) {
        if (v ^ p) {
          depth[v] = depth[u] + 1;
          dfs(v, u);
          idx2node.push_back(u);
        }
      }
    };
    dfs(0, -1);
    int n = idx2node.size();
    for (int i = 1; i <= n; ++i) {
      lg.push_back(lg.back() + !(i & (i - 1)));
    }
    sp.resize(lg[n] + 1, vector<int>(n));
    iota(sp[0].begin(), sp[0].end(), 0);
    for (int i = 1; i < lg[n] + 1; ++i) {
      for (int j = 0; j < n - (1 << i) + 1; ++j) {
        int a = sp[i - 1][j];
        int b = sp[i - 1][j + (1 << i - 1)];
        sp[i][j] = depth[idx2node[a]] < depth[idx2node[b]] ? a : b;
      }
    }
  }

  int query (int a, int b) {
    int k = lg[b - a + 1];
    a = sp[k][a];
    b = sp[k][b - (1 << k) + 1];
    return depth[idx2node[a]] < depth[idx2node[b]] ? a : b;
  }

  int lca (int u, int v) {
    u = node2idx[u];
    v = node2idx[v];
    if (u > v) {
      swap(u, v);
    }
    return idx2node[query(u, v)];
  }
};

struct MEX {
  const static int N = 1e5 + 5;
  bitset<N> mex;
  vector<int> freq;

  MEX() : freq(N, 0) {
    mex.set();
  }

  void add(int x) {
    if (x >= N) {
      return;
    }
    freq[x]++;
    if (freq[x] == 1) {
      mex.reset(x);
    }
  }

  void remove(int x) {
    if (x >= N) {
      return;
    }
    freq[x]--;
    if (freq[x] == 0) {
      mex.set(x);
    }
  }

  int get_mex() {
    return mex._Find_first();
  }
};

MEX mex;

struct MO {
  vector<int> a;
  int n, BLOCK;
  MO (vector<int> &_a): a(_a), n(_a.size()), BLOCK(sqrt(_a.size())) {}

  struct query {
    int l, r, id, B, lca;
    pair<int, int> P () {
      return make_pair(l / B, ((l / B) & 1) ? -r : r);
    }
    bool operator< (query &q) {
      return P() < q.P();
    }
  };
  vector<query> qs;

  void query (int l, int r, int lca) {
    qs.push_back({l, r, (int)qs.size(), BLOCK, lca});
  }

  vector<int> state;
  void add (int x) {
    mex.add(x);
  }

  void rem (int x) {
    mex.remove(x);
  }

  void change(int ind) {
    if (state[ind] == 0) {
      add(a[ind]);
    } else {
      rem(a[ind]);
    }
    state[ind] ^= 1;
  }

  vector<long long> solve (vector<int> SE) {
    state.resize((int)a.size());
    sort(qs.begin(), qs.end());
    int q = qs.size();
    vector<long long> ans(q);
    int s = 1, e = 0;
    for (int i = 0; i < q; ++i) {
      while (e < qs[i].r) change(SE[++e]);
      while (s > qs[i].l) change(SE[--s]);
      while (s < qs[i].l) change(SE[s++]);
      while (e > qs[i].r) change(SE[e--]);
      add(a[qs[i].lca]);
      ans[qs[i].id] = mex.get_mex();
      rem(a[qs[i].lca]);
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

  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] = min(a[i] - 1, n + 2);
  }
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v, --u, --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  LCA bl(adj);
  vector<int> S(n), E(n), ord, SE(2 * n);
  int dfst = 0;
  auto dfs = [&](auto &&self, int u, int p) -> void {
    S[u] = dfst++;
    ord.push_back(a[u]);
    for (int v : adj[u]) {
      if (v != p) {
        self(self, v, u);
      }
    }
    E[u] = dfst++;
    ord.push_back(a[u]);
    SE[S[u]] = SE[E[u]] = S[u];
  };
  dfs(dfs, 0, -1);
  MO mo(ord);
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v, --u, --v;
    int lca = bl.lca(u, v);
    mo.query(u == lca ? S[u] + 1 : E[u], S[v], S[lca]);
  }
  auto ans = mo.solve(SE);
  for (int i : ans) {
    cout << i << "\n";
  }

  return 0;
}