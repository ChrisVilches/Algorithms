#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestSubarray(const vector<int>& nums, const int limit) {
    const int n = nums.size();
    deque<int> max_deque, min_deque;
    int ans = 1;

    for (int i = 0, j = 0; i < n; i++) {
      while (!max_deque.empty() && nums[max_deque.back()] <= nums[i])
        max_deque.pop_back();

      while (!min_deque.empty() && nums[min_deque.back()] >= nums[i])
        min_deque.pop_back();

      max_deque.push_back(i);
      min_deque.push_back(i);

      while (nums[max_deque.front()] - nums[min_deque.front()] > limit) {
        if (max_deque.front() == j) max_deque.pop_front();
        if (min_deque.front() == j) min_deque.pop_front();
        j++;
      }

      ans = max(ans, i - j + 1);
    }

    return ans;
  }
};
