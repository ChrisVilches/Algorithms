#include <bits/stdc++.h>
using namespace std;

struct Segtree {
 private:
  vector<int> tree;
  const int n;

  int max_query(int p, int L, int R, int i, int j) {
    if (R < i || j < L) return INT_MIN;
    if (i <= L && R <= j) return tree[p];
    return max(max_query(2 * p, L, (L + R) / 2, i, j),
               max_query(2 * p + 1, (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
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

 public:
  Segtree(int n, int init = 0) : tree(vector<int>(4 * n, init)), n(n) {}
  int max_query(int i, int j) { return max_query(1, 0, n - 1, i, j); }
  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }
};

class Solution {
 public:
  bool canJump(vector<int>& nums) {
    Segtree dp(nums.size(), 0);

    dp.update(nums.size() - 1, 1);

    for (int i = nums.size() - 2; i >= 0; i--) {
      const int possible = dp.max_query(i, i + nums[i]);
      dp.update(i, possible);
    }

    return dp.max_query(0, 0);
  }
};
