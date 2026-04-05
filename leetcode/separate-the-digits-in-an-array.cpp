#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> separateDigits(const vector<int>& nums) {
    vector<int> ans;

    for (int x : views::reverse(nums)) {
      do {
        ans.emplace_back(x % 10);
        x /= 10;
      } while (x > 0);
    }

    reverse(ans.begin(), ans.end());

    return ans;
  }
};
