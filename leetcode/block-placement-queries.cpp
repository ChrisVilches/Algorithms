#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int max_n = 50'007;
  const int inf = INT_MAX;
  set<int> partitions;
  vector<int> tree;

  int max_query(const int p, const int L, const int R, const int i, const int j) const {
    if (R < i || j < L) return 0;
    if (i <= L && R <= j) return tree[p];
    return max(max_query(2 * p, L, (L + R) / 2, i, j),
               max_query(2 * p + 1, (L + R) / 2 + 1, R, i, j));
  }

  void update(const int p, const int L, const int R, const int pos, const int new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      const int m = (L + R) / 2;
      if (pos <= m)
        update(2 * p, L, m, pos, new_val);
      else
        update(2 * p + 1, m + 1, R, pos, new_val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

  void put_obstacle(const int x) {
    const int lo = *prev(partitions.lower_bound(x));
    const int hi = *partitions.lower_bound(x);

    if (hi != inf) update(1, 0, max_n - 1, hi - 1, hi - x);
    update(1, 0, max_n - 1, x - 1, x - lo);

    partitions.emplace(x);
  }

  bool query_block_possible(const int x, const int size) const {
    const int val1 = x - *prev(partitions.lower_bound(x));
    const int val2 = max_query(1, 0, max_n - 1, 0, x - 1);

    return size <= max(val1, val2);
  }

 public:
  vector<bool> getResults(const vector<vector<int>>& queries) {
    tree.assign(4 * max_n, 0);
    vector<bool> ans;

    partitions.emplace(0);
    partitions.emplace(inf);

    for (const vector<int>& q : queries) {
      if (q.front() == 1) {
        put_obstacle(q.back());
      } else {
        ans.emplace_back(query_block_possible(q[1], q[2]));
      }
    }

    return ans;
  }
};
