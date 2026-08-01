#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  array<vector<ll>, 4 * 100'007> tree;
  vector<ll> psum;

  void build(const int v, const int l, const int r) {
    copy(psum.begin() + l, psum.begin() + r + 1, back_inserter(tree[v]));
    sort(tree[v].begin(), tree[v].end());

    if (l != r) {
      build(2 * v, l, (l + r) / 2);
      build(2 * v + 1, 1 + (l + r) / 2, r);
    }
  }

  int count(const vector<ll>& segment, const ll a, const ll b) {
    const auto it1 = lower_bound(segment.begin(), segment.end(), a);
    const auto it2 = upper_bound(segment.begin(), segment.end(), b);
    return it2 - it1;
  }

  int query(const int v, const int l, const int r, const int i, const int j, const ll a,
            const ll b) {
    if (i > r || j < l) return 0;
    if (i <= l && r <= j) return count(tree[v], a, b);
    const int m = (l + r) / 2;
    return query(2 * v, l, m, i, j, a, b) + query(2 * v + 1, m + 1, r, i, j, a, b);
  }

 public:
  int countRangeSum(const vector<int>& nums, const int lower, const int upper) {
    const int n = nums.size();

    for (const ll x : nums) {
      if (psum.empty()) {
        psum.emplace_back(x);
      } else {
        psum.emplace_back(x + psum.back());
      }
    }

    build(1, 0, n - 1);
    int ans = 0;
    ll left = 0;

    for (int i = 0; i < n; i++) {
      const ll l = lower + left;
      const ll r = upper + left;

      ans += query(1, 0, n - 1, i, n - 1, l, r);

      left += nums[i];
    }

    return ans;
  }
};
