#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumCost(const vector<int>& nums) {
    vector<int> arr;
    arr.reserve(3);

    for (const int x : views::drop(nums, 1)) {
      arr.emplace_back(x);
      sort(arr.begin(), arr.end());
      if (arr.size() > 2) arr.pop_back();
    }

    return nums.front() + accumulate(arr.begin(), arr.end(), 0);
  }
};
