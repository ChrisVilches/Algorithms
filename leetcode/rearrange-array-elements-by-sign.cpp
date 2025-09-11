#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> rearrangeArray(const vector<int>& nums) {
    vector<int> pos, neg;
    for (const int x : nums) {
      if (x > 0) {
        pos.emplace_back(x);
      } else {
        neg.emplace_back(x);
      }
    }

    vector<int> ans;

    for (size_t i = 0; i < neg.size(); i++) {
      ans.emplace_back(pos[i]);
      ans.emplace_back(neg[i]);
    }

    return ans;
  }
};
