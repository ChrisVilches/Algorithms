#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const size_t n) : A(n + 1, 0) {}

  void update(size_t i, const long long v) {
    i++;
    for (; i < A.size(); i += i & -i) A[i] += v;
  }

  long long query(size_t i) {
    i++;
    long long sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  vector<long long> A;
};

class Solution {
  vector<size_t> make_index_asc(const vector<int>& nums) {
    vector<size_t> res(nums.size());
    vector<pair<int, size_t>> sorted;
    for (size_t i = 0; i < nums.size(); i++) {
      sorted.emplace_back(nums[i], i);
    }
    sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < nums.size(); i++) {
      res[sorted[i].second] = i;
    }
    return res;
  }

 public:
  long long minimumCost(const vector<int>& nums, const int k, const size_t dist) {
    const size_t n = nums.size();
    BIT active(n), sum(n);
    const vector<size_t> idx = make_index_asc(nums);

    for (size_t i = 1; i <= 1 + dist; i++) {
      active.update(idx[i], 1);
      sum.update(idx[i], nums[i]);
    }

    long long ans = LONG_LONG_MAX;

    for (size_t i = 1; i < n - dist; i++) {
      size_t lo = 0;
      size_t hi = n - 1;

      while (lo < hi) {
        const size_t mid = (lo + hi) / 2;
        if (active.query(mid) < k - 1) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }

      ans = min(ans, sum.query(lo));

      if (i + dist + 1 >= n) break;

      active.update(idx[i], -1);
      sum.update(idx[i], -nums[i]);
      active.update(idx[i + dist + 1], 1);
      sum.update(idx[i + dist + 1], nums[i + dist + 1]);
    }

    return nums.front() + ans;
  }
};
