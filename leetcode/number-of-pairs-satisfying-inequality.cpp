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
  vector<pair<int, int>> make_sorted(const vector<int>& nums) {
    vector<pair<int, int>> res;
    for (size_t i = 0; i < nums.size(); i++) {
      res.emplace_back(nums[i], i);
    }
    sort(res.rbegin(), res.rend());
    return res;
  }

 public:
  long long numberOfPairs(const vector<int>& nums1, const vector<int>& nums2,
                          const int diff) {
    const int n = nums1.size();
    vector<int> nums;

    for (int i = 0; i < n; i++) {
      nums.emplace_back(nums1[i] - nums2[i]);
    }

    BIT bit(n);

    const vector<pair<int, int>> sorted = make_sorted(nums);
    vector<int> idx(n);

    for (int i = 0; i < n; i++) {
      idx[sorted[i].second] = i;
    }

    long long ans = 0;

    for (int i = n - 1; i >= 0; i--) {
      int lo = 0;
      int hi = n - 1;

      while (lo <= hi) {
        const int mid = (lo + hi) / 2;

        if (nums[i] - diff > sorted[mid].first) {
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }

      ans += bit.query(lo - 1);
      bit.update(idx[i], 1);
    }

    return ans;
  }
};
