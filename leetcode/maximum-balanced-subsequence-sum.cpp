#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<long long> tree;

  long long max_query(const int p, const int l, const int r, const int i, const int j) {
    if (i > r || j < l) return LLONG_MIN;
    if (i <= l && r <= j) return tree[p];
    const int m = (l + r) / 2;
    return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
  }

  void update_max(const int p, const int l, const int r, const int i, const long long v) {
    if (l == r) {
      tree[p] = max(tree[p], v);
    } else {
      const int m = (l + r) / 2;
      if (i <= m)
        update_max(2 * p, l, m, i, v);
      else
        update_max(2 * p + 1, m + 1, r, i, v);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  long long maxBalancedSubsequenceSum(const vector<int>& nums) {
    const int n = nums.size();

    set<int> all_values;
    unordered_map<int, int> idx;
    for (int i = 0; i < n; i++) all_values.emplace(nums[i] - i);
    for (const int x : all_values) idx[x] = idx.size();

    const int tree_n = idx.size();
    tree.assign(4 * tree_n, LLONG_MIN);

    for (int i = n - 1; i >= 0; i--) {
      const int k = idx[nums[i] - i];
      const long long max_val = max_query(1, 0, tree_n - 1, k, tree_n - 1);

      if (max_val == LLONG_MIN) {
        update_max(1, 0, tree_n - 1, k, nums[i]);
      } else {
        update_max(1, 0, tree_n - 1, k, nums[i] + max_val);
      }
    }

    return max_query(1, 0, tree_n - 1, 0, tree_n - 1);
  }
};
