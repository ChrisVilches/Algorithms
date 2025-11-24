#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
  BIT(const size_t n) : A(n + 1, 0) {}

  ll sum(const int l, const int r) { return sum(r) - sum(l - 1); }

  void update(size_t idx, const ll delta) {
    for (; idx < A.size(); idx = idx | (idx + 1)) A[idx] += delta;
  }

 private:
  vector<ll> A;

  ll sum(int r) {
    ll ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += A[r];
    return ret;
  }
};

class Solution {
 public:
  ll countOperationsToEmptyArray(const vector<int>& nums) {
    const int n = nums.size();

    vector<pair<int, int>> idx;

    for (int i = 0; i < n; i++) {
      idx.emplace_back(nums[i], i);
    }

    sort(idx.begin(), idx.end());

    BIT bit(nums.size());
    for (int i = 0; i < n; i++) bit.update(i, 1);

    int i = 0;
    ll ans = 0;

    for (const auto& [_, j] : idx) {
      if (i <= j) {
        ans += bit.sum(i, j);
      } else {
        ans += bit.sum(i, n - 1) + bit.sum(0, j);
      }
      bit.update(j, -1);
      i = j;
    }

    return ans;
  }
};
