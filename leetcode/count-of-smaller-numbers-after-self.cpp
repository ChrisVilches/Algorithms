#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums;
  vector<int> tree[4 * 100'007];

  void build(const int v, const int l, const int r) {
    copy(nums.begin() + l, nums.begin() + r + 1, back_inserter(tree[v]));

    if (l == r) return;

    sort(tree[v].begin(), tree[v].end());
    build(2 * v, l, (l + r) / 2);
    build(2 * v + 1, 1 + (l + r) / 2, r);
  }

  int query(const int v, const int l, const int r, const int i, const int j,
            const int k) {
    if (i > r || j < l) return 0;

    if (i <= l && r <= j) {
      const auto it = lower_bound(tree[v].begin(), tree[v].end(), k);
      return it - tree[v].begin();
    }

    const int result1 = query(2 * v, l, (l + r) / 2, i, j, k);
    const int result2 = query(2 * v + 1, 1 + (l + r) / 2, r, i, j, k);

    return result1 + result2;
  }

 public:
  vector<int> countSmaller(const vector<int>& nums) {
    this->nums = nums;
    const int n = nums.size();
    build(1, 0, n - 1);

    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
      ans[i] = query(1, 0, n - 1, i + 1, n - 1, nums[i]);
    }

    return ans;
  }
};
