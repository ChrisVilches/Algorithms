#include <bits/stdc++.h>
using namespace std;

class Solution {
  int tree[4 * 100'007];

  int max_query(const int p, const int l, const int r, const int i, const int j) {
    if (i > r || j < l) return INT_MIN;
    if (i <= l && r <= j) return tree[p];
    const int m = (l + r) / 2;
    return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
  }

  void update(const int p, const int l, const int r, const int pos, const int val) {
    if (l == r) {
      tree[p] = val;
    } else {
      const int m = (l + r) / 2;
      if (pos <= m)
        update(2 * p, l, m, pos, val);
      else
        update(2 * p + 1, m + 1, r, pos, val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
    const int n = obstacles.size();
    memset(tree, 0, sizeof tree);

    set<pair<int, int>> order;
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
      order.emplace(obstacles[i], i);
    }

    for (const auto& [_, idx] : order) {
      const int max_val = max_query(1, 0, n - 1, 0, idx);
      update(1, 0, n - 1, idx, 1 + max_val);
      ans[idx] = 1 + max_val;
    }

    return ans;
  }
};
