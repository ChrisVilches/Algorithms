#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : A(n + 1, 0) {}

  void update(size_t i, const int v) {
    i++;
    for (; i < A.size(); i += i & -i) A[i] += v;
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
  vector<double> medianSlidingWindow(const vector<int>& nums, const int k) {
    const int n = nums.size();

    vector<pair<int, int>> all;
    for (size_t i = 0; i < nums.size(); i++) {
      all.emplace_back(nums[i], i);
    }
    sort(all.begin(), all.end());
    vector<int> idx(nums.size());
    for (size_t i = 0; i < nums.size(); i++) {
      idx[all[i].second] = i;
    }
    BIT bit(nums.size());
    for (int i = 0; i < k; i++) bit.update(idx[i], 1);

    vector<double> ans;

    const auto find = [&](const int count) {
      int lo = 0;
      int hi = nums.size();
      while (lo < hi) {
        const int mid = (lo + hi) / 2;
        if (bit.query(mid) < count) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }
      return all[lo].first;
    };

    for (int i = 0; i <= n - k; i++) {
      const double a = find(1 + (k / 2));

      if (k % 2 == 0) {
        const double b = find(k / 2);
        ans.emplace_back((a / 2) + (b / 2));
      } else {
        ans.emplace_back(a);
      }

      bit.update(idx[i], -1);
      if (i + k < n) bit.update(idx[i + k], 1);
    }

    return ans;
  }
};
