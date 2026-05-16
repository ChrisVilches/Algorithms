#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  int memo[300][1007];

  bool can_connect(const vector<int>& a, const vector<int>& b) const {
    for (size_t i = 0; i < a.size(); i++) {
      if (a[i] == b[i]) return false;
    }

    return true;
  }

 public:
  int colorTheGrid(const int m, const int n) {
    memset(memo, -1, sizeof memo);
    vector<vector<int>> all;
    vector<int> curr;

    const function<void(int)> recur = [&](const int c) {
      if (!curr.empty() && curr.back() == c) return;
      curr.emplace_back(c);

      if (static_cast<int>(curr.size()) == m) {
        all.emplace_back(curr);
      } else {
        for (int i = 0; i < 3; i++) recur(i);
      }

      curr.pop_back();
    };

    for (int i = 0; i < 3; i++) recur(i);

    vector<vector<int>> graph(all.size() + 1);

    for (size_t i = 0; i < all.size(); i++) {
      graph[all.size()].emplace_back(i);

      for (size_t j = i + 1; j < all.size(); j++) {
        if (can_connect(all[i], all[j])) {
          graph[i].emplace_back(j);
          graph[j].emplace_back(i);
        }
      }
    }

    const function<long long(int, int)> dp = [&](const int u, const int rem) {
      if (rem == 0) return 1;
      if (~memo[u][rem]) return memo[u][rem];

      long long res = 0;

      for (const int v : graph[u]) {
        res = (res + dp(v, rem - 1)) % mod;
      }

      return memo[u][rem] = res;
    };

    return dp(all.size(), n);
  }
};
