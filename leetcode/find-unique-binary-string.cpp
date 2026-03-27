#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string findDifferentBinaryString(const vector<string>& nums) {
    string ans;

    // https://en.wikipedia.org/wiki/Cantor%27s_diagonal_argument
    for (size_t i = 0; i < nums.size(); i++) {
      ans += nums[i][i] == '0' ? '1' : '0';
    }

    return ans;
  }
};
