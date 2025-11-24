#include <bits/stdc++.h>
using namespace std;

class NumArray {
  const int n;
  vector<int> bit, vals;

  int sum(int r) const {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

 public:
  NumArray(const vector<int>& nums) : n(nums.size()), bit(n + 1, 0), vals(n, 0) {
    for (int i = 0; i < n; i++) {
      update(i, nums[i]);
    }
  }

  void update(int idx, const int new_value) {
    const int delta = new_value - vals[idx];
    vals[idx] = new_value;
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }

  int sumRange(const int l, const int r) const { return sum(r) - sum(l - 1); }
};
