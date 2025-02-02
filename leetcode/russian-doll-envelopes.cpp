#include <bits/stdc++.h>
using namespace std;

class Solution {
  static const int MAX = 100'007;
  array<int, 4 * MAX> tree;

  int max_query(const int p, const int l, const int r, const int i, const int j) {
    if (i > r || j < l) return INT_MIN;
    if (i <= l && r <= j) return tree[p];
    const int m = (l + r) / 2;
    return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
  }

  void update_max(const int p, const int l, const int r, const int pos, const int val) {
    if (l == r) {
      tree[p] = max(tree[p], val);
    } else {
      const int m = (l + r) / 2;
      if (pos <= m)
        update_max(2 * p, l, m, pos, val);
      else
        update_max(2 * p + 1, m + 1, r, pos, val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  int maxEnvelopes(const vector<vector<int>>& envelopes) {
    map<int, set<int>> pairs;

    for (const auto& vec : envelopes) {
      const int w = vec.front();
      const int h = vec.back();
      pairs[w].emplace(h);
    }

    fill(tree.begin(), tree.end(), 0);

    for (const auto& [_, heights] : pairs) {
      for (auto it = heights.rbegin(); it != heights.rend(); it++) {
        const int h = *it;

        const int fit = 1 + max_query(1, 0, MAX - 1, 0, h - 1);

        update_max(1, 0, MAX - 1, h, fit);
      }
    }

    return max_query(1, 0, MAX - 1, 0, MAX - 1);
  }
};
