#include <bits/stdc++.h>
using namespace std;

class Solution {
  int n;
  array<vector<bool>, 2> tree;
  vector<int> nums;

  bool can_merge(const bool asc, const int L, const int R, const int i, const int j) {
    const int mid = (L + R) / 2;
    const int l = mid;
    const int r = mid + 1;
    return asc ? nums[l] <= nums[r] : nums[l] >= nums[r];
  }

  bool query(const bool asc, const int p, const int L, const int R, const int i,
             const int j) {
    if (j < L || i > R) return true;
    if (i <= L && R <= j) return tree[asc][p];

    const int m = (L + R) / 2;
    const bool l = query(asc, 2 * p, L, m, i, j);
    const bool r = query(asc, 2 * p + 1, m + 1, R, i, j);

    return l && r && can_merge(asc, L, R, i, j);
  }

  void build_tree(const bool asc, const int p, const int L, const int R) {
    if (L == R) {
      tree[asc][p] = true;
      return;
    }

    const int m = (L + R) / 2;
    build_tree(asc, 2 * p, L, m);
    build_tree(asc, 2 * p + 1, m + 1, R);

    tree[asc][p] = tree[asc][2 * p] && tree[asc][2 * p + 1] && can_merge(asc, L, R, L, R);
  }

  bool solve(const bool asc) {
    const int size = 2 + (rand() % 7365);
    for (int i = 0; i < n; i += size - 1) {
      const int j = min(i + size - 1, n - 1);
      if (!query(asc, 1, 0, n - 1, i, j)) return false;

      if (j == n - 1) break;
    }
    return true;
  }

 public:
  bool isMonotonic(const vector<int>& nums) {
    srand(time(NULL));
    this->nums = nums;
    n = nums.size();
    tree[0].resize(4 * n);
    tree[1].resize(4 * n);
    build_tree(false, 1, 0, n - 1);
    build_tree(true, 1, 0, n - 1);

    return solve(false) || solve(true);
  }
};
