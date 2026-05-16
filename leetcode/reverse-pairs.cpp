#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : A(n + 1, 0) {}

  void update(int i, const int v) {
    i++;
    for (; i < (int)A.size(); i += i & -i) A[i] += v;
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  vector<int> A;
};

class Solution {
 public:
  int reversePairs(const vector<int>& nums) {
    const int n = nums.size();
    BIT bit(n);

    vector<pair<int, int>> pairs;

    for (int i = 0; i < n; i++) {
      pairs.emplace_back(nums[i], i);
    }

    sort(pairs.begin(), pairs.end());

    vector<int> idx(nums.size());

    for (int i = 0; i < n; i++) idx[pairs[i].second] = i;

    int ans = 0;

    for (int i = n - 1; i >= 0; i--) {
      long long x = nums[i];
      x = (x + abs(x % 2)) / 2;

      const pair<int, int> search{x, -1};
      const auto it = lower_bound(pairs.begin(), pairs.end(), search);

      ans += bit.query(it - pairs.begin() - 1);
      bit.update(idx[i], 1);
    }

    return ans;
  }
};
