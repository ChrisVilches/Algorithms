#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
    const int N = nums.size();

    multiset<int> m{nums.begin(), nums.begin() + min(N, indexDiff + 1)};

    for (int i = 0; i < N; i++) {
      m.erase(m.find(nums[i]));

      const auto it = m.lower_bound(nums[i] - valueDiff);

      if (it != m.end() && abs(nums[i] - *it) <= valueDiff) {
        return true;
      }

      if (i + indexDiff + 1 < N) m.emplace(nums[i + indexDiff + 1]);
    }

    return false;
  }
};
