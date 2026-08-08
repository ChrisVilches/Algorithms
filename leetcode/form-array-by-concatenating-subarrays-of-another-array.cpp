#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const vector<int>& nums, const vector<int>& pattern) {
  vector<int> lps(pattern.size());
  lps.front() = 0;
  for (size_t i = 1, len = 0; i < pattern.size(); i++) {
    while (len != 0 && pattern[i] != pattern[len]) len = lps[len - 1];
    if (pattern[i] == pattern[len]) len++;
    lps[i] = len;
  }
  vector<int> matches;
  for (size_t i = 0, j = 0; i < nums.size(); i++) {
    while (j != 0 && nums[i] != pattern[j]) j = lps[j - 1];
    if (nums[i] == pattern[j]) j++;
    if (j == pattern.size()) {
      matches.emplace_back(i - j + 1);
      j = lps[j - 1];
    }
  }
  return matches;
}

class Solution {
 public:
  bool canChoose(const vector<vector<int>>& groups, const vector<int>& nums) {
    vector<vector<int>> matches;
    for (const vector<int>& g : groups) {
      matches.emplace_back(kmp(nums, g));
    }

    for (size_t i = 0, curr = 0; i < groups.size(); i++) {
      const auto it = find_if(matches[i].begin(), matches[i].end(),
                              [&](const size_t m) { return m >= curr; });

      if (it == matches[i].end()) return false;

      curr = *it + groups[i].size();
    }

    return true;
  }
};
