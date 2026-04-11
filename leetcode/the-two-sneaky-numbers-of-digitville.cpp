#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> getSneakyNumbers(const vector<int>& nums) {
    vector<int> ans;

    unordered_map<int, int> freq;

    for (const int x : nums) {
      freq[x]++;
      if (freq[x] == 2) ans.emplace_back(x);
    }

    return ans;
  }
};
