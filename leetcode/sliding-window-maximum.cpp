#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    multiset<int> s;

    for (int i = 0; i < k; i++) {
      s.insert(nums[i]);
    }

    for (int i = 0;; i++) {
      result.push_back(*prev(s.end()));
      s.erase(s.find(nums[i]));

      if (i + k == (int)nums.size()) break;
      s.insert(nums[i + k]);
    }

    return result;
  }
};
