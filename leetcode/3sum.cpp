#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    map<int, int> freq;
    for (const int x : nums) freq[x]++;
    nums.clear();

    for (const auto& [k, v] : freq) {
      for (int i = 1; i <= min(v, 3); i++) {
        nums.push_back(k);
      }
    }

    unordered_map<int, vector<pair<int, int>>> pairs;
    set<tuple<int, int, int>> ans;

    const int n = nums.size();

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        const int sum = nums[i] + nums[j];
        pairs[sum].emplace_back(i, j);
      }
    }

    array<int, 3> triple;

    for (int i = 0; i < n; i++) {
      for (const auto& [j, k] : pairs[-nums[i]]) {
        if (i == j || i == k) continue;

        triple[0] = nums[i];
        triple[1] = nums[j];
        triple[2] = nums[k];
        sort(triple.begin(), triple.end());
        ans.emplace(triple[0], triple[1], triple[2]);
      }
    }

    vector<vector<int>> result;

    for (const auto& [a, b, c] : ans) {
      result.emplace_back(vector<int>{a, b, c});
    }

    return result;
  }
};
