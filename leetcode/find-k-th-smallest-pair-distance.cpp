#include <bits/stdc++.h>
using namespace std;

class Solution {
  int count_with_distance(const vector<int>& nums, const int dist) {
    int res = 0;
    for (auto it = nums.begin(); it < nums.end(); it++) {
      const auto found = upper_bound(it + 1, nums.end(), *it + dist);
      res += distance(it + 1, found);
    }
    return res;
  }

 public:
  int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());

    int lo = 0;
    int hi = 1e6 + 7;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      if (count_with_distance(nums, mid) < k) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo;
  }
};
