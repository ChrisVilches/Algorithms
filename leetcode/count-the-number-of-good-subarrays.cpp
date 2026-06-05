#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long countGood(const vector<int>& nums, const int k) {
    const size_t n = nums.size();

    long long ans = 0;
    long long pairs = 0;

    unordered_map<int, int> freq;

    for (size_t i = 0, j = 0; i < n; i++) {
      while (j < n && pairs < k) {
        pairs += freq[nums[j]];
        freq[nums[j]]++;
        j++;
      }

      if (pairs >= k) {
        ans += n - j + 1;
      }

      freq[nums[i]]--;
      pairs -= freq[nums[i]];
    }

    return ans;
  }
};
