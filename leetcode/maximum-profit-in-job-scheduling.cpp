#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> tree;

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
  int jobScheduling(const vector<int>& start_time, const vector<int>& end_time,
                    const vector<int>& profit) {
    const int n = start_time.size();

    vector<tuple<int, int, int>> jobs;
    set<int> all_values;
    for (const int x : start_time) all_values.emplace(x);
    for (const int x : end_time) all_values.emplace(x);
    unordered_map<int, int> idx;
    for (const int x : all_values) {
      idx[x] = idx.size();
    }

    const int tree_n = idx.size();
    tree.assign(4 * tree_n, 0);

    for (int i = 0; i < n; i++) {
      jobs.emplace_back(start_time[i], end_time[i], profit[i]);
    }

    sort(jobs.rbegin(), jobs.rend());

    for (const auto& [start, end, profit] : jobs) {
      const int max_val = max_query(1, 0, tree_n - 1, idx[end], tree_n - 1);
      update_max(1, 0, tree_n - 1, idx[start], profit + max_val);
    }

    return max_query(1, 0, tree_n - 1, 0, tree_n - 1);
  }
};
