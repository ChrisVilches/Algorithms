#include <bits/stdc++.h>
using namespace std;

class Solution {
  static const int max_n = 1e5 + 7;
  array<int, max_n * 4> tree;
  vector<int> nums;

  void build(const int p, const int L, const int R) {
    if (L == R) {
      tree[p] = nums[L];
    } else {
      build(2 * p, L, (L + R) / 2);
      build(2 * p + 1, (L + R) / 2 + 1, R);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

  int query(int p, int L, int R, const int i, const int j, const int x) {
    if (i > R || j < L) return -1;
    if (i <= L && R <= j) {
      if (tree[p] <= x) return -1;

      while (L != R) {
        const int mid = (L + R) / 2;
        if (tree[p * 2] > x)
          p = p * 2, R = mid;
        else
          p = p * 2 + 1, L = mid + 1;
      }

      return L;
    }

    const int mid = (L + R) / 2;
    const int left = query(p * 2, L, mid, i, j, x);
    if (left != -1) return left;
    return query(p * 2 + 1, mid + 1, R, i, j, x);
  }

 public:
  vector<int> secondGreaterElement(const vector<int>& input) {
    this->nums = input;
    const int n = nums.size();
    build(1, 0, n - 1);

    vector<int> ans(n, -1);

    for (int i = 0; i < n; i++) {
      const int idx = query(1, 0, n - 1, i, n - 1, nums[i]);
      if (idx == -1) continue;

      const int idx2 = query(1, 0, n - 1, idx + 1, n - 1, nums[i]);

      if (idx2 != -1) {
        ans[i] = nums[idx2];
      }
    }

    return ans;
  }
};
