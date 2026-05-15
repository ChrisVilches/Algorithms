#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countMatchingSubarrays(const vector<int>& nums, const vector<int>& pattern) {
    vector<int> seq;
    for (size_t i = 0; i < nums.size() - 1; i++) {
      const int a = nums[i];
      const int b = nums[i + 1];
      seq.emplace_back((a < b) - (a > b));
    }

    vector<int> lps(pattern.size());
    lps.front() = 0;
    for (size_t i = 1, len = 0; i < pattern.size(); i++) {
      while (len != 0 && pattern[i] != pattern[len]) len = lps[len - 1];
      if (pattern[i] == pattern[len]) len++;
      lps[i] = len;
    }

    int ans = 0;

    for (size_t i = 0, j = 0; i < seq.size(); i++) {
      while (j > 0 && seq[i] != pattern[j]) j = lps[j - 1];
      if (seq[i] == pattern[j]) j++;
      if (j == pattern.size()) {
        ans++;
        j = lps[j - 1];
      }
    }

    return ans;
  }
};
