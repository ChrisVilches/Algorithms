#include <bits/stdc++.h>
using namespace std;

class Solution {
  int x_sum(const size_t x, const span<const int> nums) {
    unordered_map<int, int> freq;
    for (const int v : nums) freq[v]++;

    vector<pair<int, int>> ord{freq.begin(), freq.end()};
    sort(ord.begin(), ord.end(), [&](const auto& a, const auto& b) {
      if (a.second != b.second) return a.second > b.second;
      return a.first > b.first;
    });

    int res = 0;
    for (size_t i = 0; i < min(x, ord.size()); i++) {
      res += ord[i].first * ord[i].second;
    }
    return res;
  }

 public:
  vector<int> findXSum(const vector<int>& nums, const int k, const int x) {
    const int n = nums.size();

    vector<int> ans;

    for (int i = 0; i < n - k + 1; i++) {
      const auto s = span(nums).subspan(i, k);
      ans.emplace_back(x_sum(x, s));
    }

    return ans;
  }
};
